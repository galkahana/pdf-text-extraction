#pragma once
#include "IPDFRecursiveInterpreterHandler.h"

class PDFParser;
class PDFDictionary;
class PDFStreamInput;
class PDFObjectParser;
class InterpreterContext;

class PDFRecursiveInterpreter {
public:
    PDFRecursiveInterpreter(void);
    virtual ~PDFRecursiveInterpreter(void);

    bool InterpretPageContents(
        PDFParser* inParser,
        PDFDictionary* inPage,
        IPDFRecursiveInterpreterHandler* inHandler);

    bool InterpretXObjectContents(
        PDFParser* inParser,
        PDFStreamInput* inXObject,
        IPDFRecursiveInterpreterHandler* inHandler); 

private:
    bool InterpretContentStream(
        PDFParser* inParser,
        PDFDictionary* inContentParent,
        PDFObjectParser* inObjectParser,
        InterpreterContext* inContext,
        IPDFRecursiveInterpreterHandler* inHandler
    );
    void SkipInlinImageTillEI(
        PDFObjectParser* inObjectParser
    );
};