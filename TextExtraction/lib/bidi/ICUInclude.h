#if (SUPPORT_ICU_BIDI==1)

    // win 10 sdk native suport
    #ifdef INCLUDE_ICUCOMMON
        #include <icucommon.h>
        #include <icui18n.h>
    #elif INCLUDE_ICU
        #include <icu.h>
    #elif INCLUDE_UBIDI
        #include "unicode/ubidi.h"
    #endif

#endif
