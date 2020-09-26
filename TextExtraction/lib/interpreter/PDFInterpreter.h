#pragma once

class PDFParser;
class PDFDictionary;
class PDFStreamInput;
class PDFObjectParser;

class IPDFInterpreterHandler;

class PDFInterpreter {
public:
    PDFInterpreter(void);
    virtual ~PDFInterpreter(void);

    void InterpretPageContents(
        PDFParser* inParser,
        PDFDictionary* inPage,
        IPDFInterpreterHandler* inHandler);

    void InterpretXObjectContents(
        PDFParser* inParser,
        PDFStreamInput* inXObject,
        IPDFInterpreterHandler* inHandler);

private:
    void InterpretContentStream(
        PDFObjectParser* inObjectParser,
        IPDFInterpreterHandler* inHandler
    );
};