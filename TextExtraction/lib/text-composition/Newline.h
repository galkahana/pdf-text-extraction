#pragma once

namespace Newline {

inline const char* Native() {
#ifdef _WIN32
    return "\r\n";
#else
    return "\n";
#endif
}

inline const char* LF() {
    return "\n";
}

inline const char* CRLF() {
    // RFC 4180 uses CRLF for CSV record separators.
    return "\r\n";
}

}