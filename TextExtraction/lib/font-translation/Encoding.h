#pragma once

#include "IOBasicTypes.h"

#include <string>
#include <list>
#include <map>

typedef std::map<IOBasicTypes::Byte, std::string> ByteToStringMap;
typedef std::list<unsigned long> ULongList;
typedef std::map<std::string, ULongList> StringToULongListMap;

class Encoding {
public:
    Encoding();

    ByteToStringMap MacExpertEncoding;
    ByteToStringMap MacRomanEncoding;
    ByteToStringMap StandardEncoding;
    ByteToStringMap SymbolEncoding;
    ByteToStringMap WinAnsiEncoding;

    StringToULongListMap AdobeGlyphList;
};

