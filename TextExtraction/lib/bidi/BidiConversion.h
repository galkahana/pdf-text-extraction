#pragma once

#include "EStatusCode.h"

#include <string>


class BidiConversion {
    public:
        BidiConversion();
        ~BidiConversion();

        PDFHummus::EStatusCode ConvertVisualToLogical(const std::string& inVisualString, int inDirection, std::string& outResult);

        static const int scDirectionLTR;
        static const int scDirectionRTL;

};