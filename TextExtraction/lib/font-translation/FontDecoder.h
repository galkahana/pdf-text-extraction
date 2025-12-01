#pragma once

#include "IOBasicTypes.h"
#include "Translation.h"
#include "../pdf-writer-enhancers/Bytes.h"
#include "../graphs/Result.h"

#include <string>
#include <list>
#include <map>

class PDFParser;
class PDFDictionary;
class PDFStreamInput;

typedef std::vector<unsigned long> ULongVector;
typedef std::map<unsigned long, ULongVector> ULongToULongVectorMap;
typedef std::map<IOBasicTypes::Byte, std::string> ByteToStringMap;
typedef std::map<unsigned long,double> ULongToDoubleMap;

struct DispositionResult {
    double width;
    unsigned long code;
};

typedef std::vector<DispositionResult> DispositionResultList;

struct FontDecoderResult {
    std::string asText;
    ETranslationMethod translationMethod;
};

class FontDecoder {

public:
    FontDecoder(PDFParser* inParser, PDFDictionary* inFont);

    FontDecoderResult Translate(const ByteList& inAsBytes);
    DispositionResultList ComputeDisplacements(const ByteList& inAsBytes);

    double ascent;
    double descent;
    double spaceWidth;
private:
    bool isSimpleFont;
    bool hasToUnicode;
    bool hasSimpleEncoding;
    ULongToULongVectorMap toUnicodeMap;
    ByteToStringMap fromSimpleEncodingMap;

    bool isMonospaced;
    double monospaceWidth;
    ULongToDoubleMap widths;
    double defaultWidth;

    void ParseFontData(PDFParser* inParser, PDFDictionary* inFont);
    void ParseToUnicodeMap(PDFParser* inParser, PDFStreamInput* inUnicodeMapStream);
    void ParseSimpleFontEncoding(PDFParser* inParser, PDFObject* inEncoding, PDFDictionary* inFont);
    void SetupDifferencesEncodingMap(PDFParser* inParser, PDFDictionary* inEncoding, PDFDictionary* inFont);
    void ParseSimpleFontDimensions(PDFParser* inParser, PDFDictionary* inFont);
    void ParseCIDFontDimensions(PDFParser* inParser, PDFDictionary* inFont);
    void ParseFontDescriptor(PDFParser* inParser, PDFDictionary* inFont);
    double GetCodeWidth(unsigned long inCode);

    // result is utf8 encoded!
    std::string ToUnicodeEncoding(const ByteList& inAsBytes);
    std::string ToSimpleEncoding(const ByteList& inAsBytes);
    std::string ToDefaultEncoding(const ByteList& inAsBytes);

    Result<unsigned long> FindSpaceCharGlyphCode();


};