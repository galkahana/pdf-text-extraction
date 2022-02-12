#include "FontDecoder.h"

#include "PDFParser.h"
#include "PDFDictionary.h"
#include "ParsedPrimitiveHelper.h"
#include "PDFObject.h"
#include "RefCountPtr.h"
#include "PDFObjectCast.h"
#include "PDFStreamInput.h"
#include "PDFArray.h"
#include "PDFName.h"
#include "UnicodeString.h"

#include "../interpreter/PDFInterpreter.h"
#include "../pdf-writer-enhancers/Bytes.h"

#include "StandardFontsDimensions.h"
#include "Encoding.h"


using namespace std;
using namespace PDFHummus;

static const Encoding scEncoding;
static const StandardFontsDimensions scStandardFontsDimensions;

static unsigned long beToNum(const ByteList& inBytes) {
    unsigned long result = 0;

    for(ByteList::const_iterator it = inBytes.begin(); it != inBytes.end();++it){
        result = result*256 + *it;
    }

    return result;

}

static ULongList besToUnicodes(const ByteList& inBytes) {
    ByteList::const_iterator it = inBytes.begin();
    ULongList unicodes;

    while(it != inBytes.end()) {
        ByteList buffer;
        buffer.push_back(*it);
        ++it;
        buffer.push_back(*it);
        ++it;
        unsigned long newOne = beToNum(buffer);
        if(0xD800 <= newOne && newOne <= 0xDBFF) {
            buffer.clear();
            buffer.push_back(*it);
            ++it;
            buffer.push_back(*it);
            ++it;
            // pfff. high surrogate. need to read another one
            unsigned long lowSurrogate = beToNum(buffer);
            unicodes.push_back(0x10000 + ((newOne - 0xD800) << 10) + (lowSurrogate - 0xDC00));
        } else {
            unicodes.push_back(newOne);
        }
    }

    return unicodes;
}

static const ByteToStringMap*  GetStandardEncodingMap(const string& inEncodingName) {
    // MacRomanEncoding, MacExpertEncoding, or WinAnsiEncoding
    if(inEncodingName == "WinAnsiEncoding") {
        return &(scEncoding.WinAnsiEncoding);
    }

    if(inEncodingName == "MacExpertEncoding")
        return &(scEncoding.MacExpertEncoding);

    if(inEncodingName == "MacRomanEncoding")
        return &(scEncoding.MacRomanEncoding);

    return NULL; 
}  


class UnicodeMapReader : public IPDFInterpreterHandler {
    public:

    UnicodeMapReader(ULongToULongListMap& inResult);

    virtual bool onOperation(const std::string& inOperation, const PDFObjectVector& inOperands);

    ULongToULongListMap& result;
};

UnicodeMapReader::UnicodeMapReader(ULongToULongListMap& inResult):result(inResult) {}

bool UnicodeMapReader::onOperation(const std::string& inOperation, const PDFObjectVector& inOperands) {
    if(inOperation == "endbfchar") {
        // Operands are pairs. always of the form <codeByte> <unicodes>
        for(unsigned long i=0;i<inOperands.size();i+=2) {
            ByteList byteCode = ToBytesList(inOperands[i]);
            ByteList unicodes = ToBytesList(inOperands[i+1]);

            result[beToNum(byteCode)] = besToUnicodes(unicodes);
        }
    } else if(inOperation == "endbfrange") {
        // Operands are 3. two codesBytes and then either a unicode start range or array of unicodes
        for(unsigned long i=0;i<inOperands.size();i+=3) {
            unsigned long startCode = beToNum(ToBytesList(inOperands[i]));
            unsigned long endCode = beToNum(ToBytesList(inOperands[i+1]));

            if(inOperands[i+2]->GetType() == PDFObject::ePDFObjectArray) {
                // specific codes
                PDFArray* unicodeArray = (PDFArray*)inOperands[i+2];
                for(unsigned long j=0;j<unicodeArray->GetLength();++j) {
                    result[startCode+j] = besToUnicodes(ToBytesList(unicodeArray->QueryObject(j)));
                }
            }
            else {
                // code range
                ULongList unicodes = besToUnicodes(ToBytesList(inOperands[i+2]));
                for(unsigned long j = startCode; j<=endCode;++j) {
                    result[j] = ULongList(unicodes);
                    ++unicodes.back();
                }
            }
        }
    }

    return true;
}


FontDecoder::FontDecoder(PDFParser* inParser, PDFDictionary* inFont) {

    ParseFontData(inParser, inFont);
}

void FontDecoder::ParseToUnicodeMap(PDFParser* inParser, PDFStreamInput* inUnicodeMapStream) {

    PDFInterpreter interpreter;
    UnicodeMapReader reader(toUnicodeMap);

    interpreter.InterpretStreamContents(inParser, inUnicodeMapStream, &reader);

}

void FontDecoder::SetupDifferencesEncodingMap(PDFParser* inParser, PDFDictionary* inEncoding, PDFDictionary* inFont) {
    PDFObjectCastPtr<PDFName> baseEncoding = inParser->QueryDictionaryObject(inEncoding, "BaseEncoding");
    bool initialized = false;
    // determine base encoding. either found in font, or decide a good default
    if(!!baseEncoding) {
        const ByteToStringMap* standardMap = GetStandardEncodingMap(baseEncoding->GetValue());
        if(!!standardMap)
            fromSimpleEncodingMap = *standardMap;

    }

    if(!initialized) {
        // no base encoding. use standard or symbol. i'm gonna use either standard encoding or symbol encoding.
        // i know the right thing is to check first the font native encoding...but that's too much of a hassle
        // so i'll take the shortcut and rely on font flags. if it is ever a problem - improve
        PDFObjectCastPtr<PDFDictionary> fontDescriptor = inParser->QueryDictionaryObject(inFont, "FontDescriptor");
        if(!!fontDescriptor) {
            // check font descriptor to determine whether this is a symbolic font. if so, use symbol encoding. otherwise - standard
            RefCountPtr<PDFObject> flagsObject =  inParser->QueryDictionaryObject(fontDescriptor.GetPtr(), "Flags");
            long long flags = ParsedPrimitiveHelper(flagsObject.GetPtr()).GetAsInteger();
            if(flags & (1<<2)) {
                fromSimpleEncodingMap = scEncoding.SymbolEncoding;
            }
            else {
                fromSimpleEncodingMap = scEncoding.StandardEncoding;
            }            
        }
        else {
            fromSimpleEncodingMap = scEncoding.StandardEncoding;
        }
    }

    PDFObjectCastPtr<PDFArray> differences = inParser->QueryDictionaryObject(inEncoding, "Differences");

    SingleValueContainerIterator<PDFObjectVector> it = differences->GetIterator();
    it.MoveNext();
    while(!it.IsFinished()) {
        long long firstIndex = ParsedPrimitiveHelper(it.GetItem()).GetAsInteger();
        it.MoveNext();
        // now come names, one for each index
        while(!it.IsFinished() && it.GetItem()->GetType() == PDFObject::ePDFObjectName) {
            fromSimpleEncodingMap[(Byte)firstIndex] = ParsedPrimitiveHelper(it.GetItem()).ToString();
            it.MoveNext();
            ++firstIndex;
        }
    }
}

void FontDecoder::ParseSimpleFontEncoding(PDFParser* inParser, PDFObject* inEncoding, PDFDictionary* inFont) {
    if(inEncoding->GetType() == PDFObject::ePDFObjectName) {
        fromSimpleEncodingMap = *(GetStandardEncodingMap(((PDFName*)inEncoding)->GetValue()));
        hasSimpleEncoding = true;
    } else if(inEncoding->GetType() == PDFObject::ePDFObjectDictionary) {
        SetupDifferencesEncodingMap(inParser, (PDFDictionary*)inEncoding, inFont);
        hasSimpleEncoding = true;
    }
}

void FontDecoder::ParseFontDescriptor(PDFParser* inParser, PDFDictionary* inFont) {
    PDFObjectCastPtr<PDFDictionary> fontDescriptor = inParser->QueryDictionaryObject(inFont,"FontDescriptor");
    if(!!fontDescriptor) {
        // complete info with font descriptor
        RefCountPtr<PDFObject> descentObject = inParser->QueryDictionaryObject(fontDescriptor.GetPtr(),"Descent");
        RefCountPtr<PDFObject> ascentObject = inParser->QueryDictionaryObject(fontDescriptor.GetPtr(),"Ascent"); 
        RefCountPtr<PDFObject> missingWidthObject = inParser->QueryDictionaryObject(fontDescriptor.GetPtr(),"MissingWidth"); 
        if(!!descentObject)
            descent = ParsedPrimitiveHelper(descentObject.GetPtr()).GetAsDouble();
        if(!!ascentObject)
            ascent = ParsedPrimitiveHelper(ascentObject.GetPtr()).GetAsDouble(); 
        if(!!missingWidthObject) {
            defaultWidth = ParsedPrimitiveHelper(missingWidthObject.GetPtr()).GetAsDouble(); 
        }
        else {
            defaultWidth = 0;
        }
    }
}

void FontDecoder::ParseSimpleFontDimensions(PDFParser* inParser, PDFDictionary* inFont) {
    RefCountPtr<PDFObject> firstCharObject = inParser->QueryDictionaryObject(inFont,"FirstChar");
    RefCountPtr<PDFObject> lastCharObject = inParser->QueryDictionaryObject(inFont,"LastChar"); 
    PDFObjectCastPtr<PDFArray> widthsArray = inParser->QueryDictionaryObject(inFont,"Widths");

    if(!!firstCharObject && !!lastCharObject && !!widthsArray) {
        unsigned long firstChar = (unsigned long)ParsedPrimitiveHelper(firstCharObject.GetPtr()).GetAsInteger();
        unsigned long lastChar = (unsigned long)ParsedPrimitiveHelper(lastCharObject.GetPtr()).GetAsInteger();
        for(unsigned long i = firstChar; i<=lastChar && (i-firstChar) < widthsArray->GetLength();++i) {
            widths[i] = ParsedPrimitiveHelper(inParser->QueryArrayObject(widthsArray.GetPtr(), i - firstChar)).GetAsDouble();
        }
    } else {
        // wtf. probably one of the standard fonts. aha! [will also take care of ascent descent]
        PDFObjectCastPtr<PDFName> baseFontObject = inParser->QueryDictionaryObject(inFont,"BaseFont");
        if(!!baseFontObject) {
            const FontWidthDescriptor* descriptor = scStandardFontsDimensions.FindStandardFont(baseFontObject->GetValue());
            if(descriptor) {
                ascent = descriptor->ascent;
                descent = descriptor->descent;
                isMonospaced = descriptor->isMonospaced;
                monospaceWidth = descriptor->monospaceWidth;
                widths = descriptor->widths;
            }
        }
    }

    ParseFontDescriptor(inParser, inFont);
}

void FontDecoder::ParseCIDFontDimensions(PDFParser* inParser, PDFDictionary* inFont) {
    // get the descendents font
    PDFObjectCastPtr<PDFArray> descendentFonts = inParser->QueryDictionaryObject(inFont, "DescendantFonts");
    PDFObjectCastPtr<PDFDictionary> descendentFont = inParser->QueryArrayObject(descendentFonts.GetPtr(), 0);
    // default width is easily accessible directly via DW
    RefCountPtr<PDFObject> defaultWidthObject = inParser->QueryDictionaryObject(descendentFont.GetPtr(), "DW");
    defaultWidth = !!defaultWidthObject ? ParsedPrimitiveHelper(defaultWidthObject.GetPtr()).GetAsDouble() : 1000;

    PDFObjectCastPtr<PDFArray> widthsArray = inParser->QueryDictionaryObject(descendentFont.GetPtr(), "W");
    if(!!widthsArray) {
        SingleValueContainerIterator<PDFObjectVector> it = widthsArray->GetIterator();
        it.MoveNext();
        while(!it.IsFinished()) {
            unsigned long cFirst = (unsigned long)ParsedPrimitiveHelper(it.GetItem()).GetAsInteger();
            it.MoveNext();
            if(it.GetItem()->GetType() == PDFObject::ePDFObjectArray) {
                // specified widths
                PDFArray* asArray = (PDFArray*)it.GetItem();
                it.MoveNext();
                
                SingleValueContainerIterator<PDFObjectVector> itArray = widthsArray->GetIterator();
                unsigned long j=0;
                while(itArray.MoveNext()) {
                    widths[cFirst + j] = ParsedPrimitiveHelper(itArray.GetItem()).GetAsDouble();
                    ++j;
                }
            } else {
                // same width for range
                unsigned long cLast = (unsigned long)ParsedPrimitiveHelper(it.GetItem()).GetAsInteger();
                it.MoveNext();
                double width = ParsedPrimitiveHelper(it.GetItem()).GetAsDouble();
                it.MoveNext();
                for(unsigned long j=cFirst;j<=cLast;++j) {
                    widths[j] = width;
                }
            }
        }
    }

    ParseFontDescriptor(inParser, descendentFont.GetPtr());
}

void FontDecoder::ParseFontData(PDFParser* inParser, PDFDictionary* inFont) {

    RefCountPtr<PDFObject> subType = inFont->QueryDirectObject("Subtype");
    isSimpleFont = ParsedPrimitiveHelper(subType.GetPtr()).ToString() != "Type0";

    hasToUnicode = false;
    hasSimpleEncoding = false;
    PDFObjectCastPtr<PDFStreamInput> toUnicode = inParser->QueryDictionaryObject(inFont, "ToUnicode");
    if(!!toUnicode) {
        hasToUnicode = true;
        ParseToUnicodeMap(inParser, toUnicode.GetPtr());
    } else if(isSimpleFont) {
        // simple font encoding
        RefCountPtr<PDFObject> encoding = inParser->QueryDictionaryObject(inFont, "Encoding");
        if(!!encoding)
            ParseSimpleFontEncoding(inParser, encoding.GetPtr(), inFont);

    } 

    widths.clear();
    ascent = 0;
    descent = 0;
    isMonospaced = false;
    monospaceWidth = 0;
    defaultWidth = 0;

    if(isSimpleFont) {
        ParseSimpleFontDimensions(inParser, inFont);
    }
    else {
        ParseCIDFontDimensions(inParser, inFont);
    }
}

string FontDecoder::ToUnicodeEncoding(const ByteList& inAsBytes) {
    ULongList buffer;
    ByteList::const_iterator it = inAsBytes.begin();

    while(it != inAsBytes.end()) {
        unsigned long value = *it;
        ++it;
        while(it != inAsBytes.end()) {
            if(toUnicodeMap.find(value) != toUnicodeMap.end()) {
                // could be our guy, make sure next one not good too
                if(toUnicodeMap.find(value*256 + *it) == toUnicodeMap.end())
                    break;
                // next one is good too, continue
            }
            value = value*256 + *it;
            ++it;
        }
        ULongToULongListMap::const_iterator itEntry = toUnicodeMap.find(value);
        if(itEntry != toUnicodeMap.end()) {
            buffer.insert(buffer.end(), itEntry->second.begin(), itEntry->second.end());
        }
    }

    return UnicodeString(buffer).ToUTF8().second;
}

string FontDecoder::ToSimpleEncoding(const ByteList& inAsBytes) {
    ULongList buffer;
    ByteList::const_iterator it = inAsBytes.begin();

    for(; it!= inAsBytes.end();++it) {
        ByteToStringMap::iterator entryIt = fromSimpleEncodingMap.find(*it);
        if(entryIt != fromSimpleEncodingMap.end()) {
            StringToULongListMap::const_iterator aglIt = scEncoding.AdobeGlyphList.find(entryIt->second);
            if(aglIt != scEncoding.AdobeGlyphList.end()) {
                const ULongList& mapping = scEncoding.AdobeGlyphList.find(entryIt->second)->second;
                buffer.insert(buffer.end(), mapping.begin(), mapping.end());
            }
        }
    }

    return UnicodeString(buffer).ToUTF8().second;
}

string FontDecoder::ToDefaultEncoding(const ByteList& inAsBytes) {
    ULongList buffer(inAsBytes.begin(), inAsBytes.end());

    return UnicodeString(buffer).ToUTF8().second;
}

FontDecoderResult FontDecoder::Translate(const ByteList& inAsBytes) {
    if(hasToUnicode) {
        FontDecoderResult res = {ToUnicodeEncoding(inAsBytes), eTranslationMethodToUnicode};
        return res;
    }
    else if(hasSimpleEncoding) {
        FontDecoderResult res = {ToSimpleEncoding(inAsBytes), eTranslationMethodSimpleEncoding};
        return res;
    }
    else {
        FontDecoderResult res = {ToDefaultEncoding(inAsBytes), eTranslationMethodDefault};
        return res;
    }
}

double FontDecoder::GetCodeWidth(unsigned long inCode) {
    ULongToDoubleMap::iterator it = widths.find(inCode);
    if(it == widths.end())
        return defaultWidth;
    else
        return it->second;
}

DispositionResultList FontDecoder::ComputeDisplacements(const ByteList& inAsBytes) {
    DispositionResultList result;
    ByteList::const_iterator it = inAsBytes.begin();

    if(isSimpleFont) {
        // one code per cells
        for(; it!= inAsBytes.end();++it) {
            DispositionResult item = {
                (isMonospaced ? monospaceWidth : GetCodeWidth(*it)) / 1000.00
                ,
                *it
            };
            result.push_back(item);
        }
    } else if (hasToUnicode) {
        // determine code per toUnicode (should be cmap, but i aint parsing it now, so toUnicode will do).
        // assuming horizontal writing mode
        while(it != inAsBytes.end()) {
            unsigned long value = *it;
            ++it;
            while(it != inAsBytes.end()) {
                if(toUnicodeMap.find(value) != toUnicodeMap.end()) {
                    // could be our guy, make sure next one not good too
                    if(toUnicodeMap.find(value*256 + *it) == toUnicodeMap.end())
                        break;
                    // next one is good too, continue
                }
                value = value*256 + *it;
                ++it;
            }

            DispositionResult item = {
                (isMonospaced ? monospaceWidth : GetCodeWidth(value)) / 1000.00
                ,
                value
            };

            result.push_back(item);
        }        
    } else {
        // default to 2 bytes. though i shuld be reading the cmap. and so also get the writing mode
        for(; it!= inAsBytes.end();++it) {
            unsigned long value = *it;
            ++it;
            value = value*256 + *it;
            DispositionResult item = {
                (isMonospaced ? monospaceWidth : GetCodeWidth(value)) / 1000.00
                ,
                value
            };
            result.push_back(item);
        }        
    }
    return result;
}