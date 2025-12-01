#pragma once

#include "IOBasicTypes.h"

#include <string>
#include <list>
#include <map>

typedef std::map<IOBasicTypes::Byte, std::string> ByteToStringMap;
typedef std::vector<unsigned long> ULongVector;
typedef std::map<std::string, ULongVector> StringToULongVectorMap;

class Encoding {
public:
    Encoding();

    ByteToStringMap MacExpertEncoding;
    ByteToStringMap MacRomanEncoding;
    ByteToStringMap StandardEncoding;
    ByteToStringMap SymbolEncoding;
    ByteToStringMap WinAnsiEncoding;

    StringToULongVectorMap AdobeGlyphList;
};

