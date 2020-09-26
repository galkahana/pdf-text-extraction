#include "FontDecoder.h"

#include "PDFParser.h"
#include "PDFDictionary.h"
#include "ParsedPrimitiveHelper.h"
#include "PDFObject.h"
#include "RefCountPtr.h"
#include "PDFObjectCast.h"
#include "PDFStreamInput.h"
#include "PDFArray.h"
#include "Encoding.h"
#include "PDFName.h"
#include "UnicodeString.h"

#include "../interpreter/PDFInterpreter.h"
#include "../text-placements/Bytes.h"

using namespace std;
using namespace PDFHummus;

static const Encoding scEncoding;

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
        return &(scEncoding.MacExpertEncoding);

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
    
    /*

    // parse dimensions information
    if(self.isSimpleFont) {
        parseSimpleFontDimensions(self,pdfReader,font);
    }
    else {
        parseCIDFontDimensions(self, pdfReader, font);
    }

    */
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
            const ULongList& mapping = scEncoding.AdobeGlyphList.find(entryIt->second)->second;
            buffer.insert(buffer.end(), mapping.begin(), mapping.end());
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
        return {ToUnicodeEncoding(inAsBytes), eTranslationMethodToUnicode};
    }
    else if(hasSimpleEncoding) {
        return {ToSimpleEncoding(inAsBytes), eTranslationMethodSimpleEncoding};
    }
    else {
        return {ToDefaultEncoding(inAsBytes), eTranslationMethodDefault};
    }
}