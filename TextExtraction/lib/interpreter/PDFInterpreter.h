#pragma once

#include "IPDFInterpreterHandler.h"

class PDFParser;
class PDFDictionary;
class PDFStreamInput;
class PDFObjectParser;


class PDFInterpreter {
public:
    PDFInterpreter(void);
    virtual ~PDFInterpreter(void);

    // intepret page content
    void InterpretPageContents(
        PDFParser* inParser,
        PDFDictionary* inPage,
        IPDFInterpreterHandler* inHandler);

    // alias for InterpretStreamContents for xobjects content
    void InterpretXObjectContents(
        PDFParser* inParser,
        PDFStreamInput* inXObject,
        IPDFInterpreterHandler* inHandler);

    // general purpose stream. normally xobject, but can be used to parse any
    // input stream, as long as it used same operators and operands kinds as
    // PDF.
    void InterpretStreamContents(
        PDFParser* inParser,
        PDFStreamInput* inStream,
        IPDFInterpreterHandler* inHandler);

private:
    void InterpretContentStream(
        PDFObjectParser* inObjectParser,
        IPDFInterpreterHandler* inHandler
    );
};