#pragma once

#include "IOBasicTypes.h"
#include "../text-placements/TextPlacement.h"

#include <string>
#include <list>
#include <map>

class PDFParser;
class PDFDictionary;
class PDFStreamInput;

typedef std::list<unsigned long> ULongList;

typedef std::map<unsigned long, ULongList> ULongToULongListMap;

typedef std::map<IOBasicTypes::Byte, std::string> ByteToStringMap;

struct FontDecoderResult {
    std::string asText;
    ETranslationMethod translationMethod;
};

class FontDecoder {

public:
    FontDecoder(PDFParser* inParser, PDFDictionary* inFont);

    FontDecoderResult Translate(const ByteList& inAsBytes);
private:
    bool isSimpleFont;
    bool hasToUnicode;
    bool hasSimpleEncoding;
    ULongToULongListMap toUnicodeMap;
    ByteToStringMap fromSimpleEncodingMap;

    void ParseFontData(PDFParser* inParser, PDFDictionary* inFont);
    void ParseToUnicodeMap(PDFParser* inParser, PDFStreamInput* inUnicodeMapStream);
    void ParseSimpleFontEncoding(PDFParser* inParser, PDFObject* inEncoding, PDFDictionary* inFont);
    void SetupDifferencesEncodingMap(PDFParser* inParser, PDFDictionary* inEncoding, PDFDictionary* inFont);

    // result is utf8 encoded!
    std::string ToUnicodeEncoding(const ByteList& inAsBytes);
    std::string ToSimpleEncoding(const ByteList& inAsBytes);
    std::string ToDefaultEncoding(const ByteList& inAsBytes);


};