#include "BidiConversion.h"
#include "UnicodeString.h"
#include "ICUInclude.h"

using namespace std;
using namespace PDFHummus;



BidiConversion::BidiConversion() {

}

BidiConversion::~BidiConversion() {
    
}


#if (SUPPORT_ICU_BIDI==1)

static const int scDirectionLTR = UBIDI_DEFAULT_LTR;
static const int scDirectionRTL = UBIDI_DEFAULT_RTL;

EStatusCode BidiConversion::ConvertVisualToLogical(const string& inVisualString, int inDirection, string& result) {
    result = inVisualString;

    if(inVisualString.size() == 0)
        return eSuccess; // let's not waste time on those


    // create bidi
    UBiDi* bidi = ubidi_open();

    // mark conversion intent to be visual to logical (as this is what we're looking at here)
    ubidi_setInverse(bidi, true);

    // set paragraph with input from visual string. use the existing method of the pdfwriter UnicodeString to handle the utf8 input string...
    // it was used to generate it...so naturally it understands how to convert "back".
    UnicodeString helper;
    helper.FromUTF8(inVisualString);
    UErrorCode errorCode = U_ZERO_ERROR;
    unsigned long sourceSize = helper.GetUnicodeList().size();
    UChar* sourceText = new UChar[sourceSize+1];
    ULongList::iterator it= helper.GetUnicodeList().begin();
    unsigned long i=0;
    for(;it != helper.GetUnicodeList().end();++it, ++i)
        sourceText[i] = (UChar)*it;
    sourceText[sourceSize]=0;

    UChar* destText = NULL;
    do {
        ubidi_setPara(bidi, sourceText, sourceSize,
                        inDirection,
                        NULL, &errorCode);
        if(errorCode != U_ZERO_ERROR)
            break;

        // setup output buffer. should be same as
        unsigned long targetSize = ubidi_getProcessedLength(bidi);
        destText = new UChar[targetSize+1]; // +1 to allow bidi to place a final 0

        ubidi_writeReordered(bidi, destText, targetSize+1, UBIDI_DO_MIRRORING, &errorCode);

        if(errorCode != U_ZERO_ERROR)
            break;

        // now back to string (wait i want to see how it works...)
        ULongList targetList;
        for(unsigned long j=0;j<targetSize;++j)
            targetList.push_back((unsigned long)destText[j]);
        helper = targetList;
        result = helper.ToUTF8().second;
    } while(false);

    delete[] sourceText;
    if(destText)
        delete[] destText;

    return errorCode == U_ZERO_ERROR ? eSuccess: eFailure;
}
#else // SUPPORT_ICU_BIDI

static const int scDirectionLTR = 0;
static const int scDirectionRTL = 1;

EStatusCode BidiConversion::ConvertVisualToLogical(const std::string& inVisualString, int inDirection, string& result) {
    result = inVisualString;
    return eSuccess;
}

#endif