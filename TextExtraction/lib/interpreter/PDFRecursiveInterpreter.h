#pragma once
#include <list>

#include "IOBasicTypes.h"
#include "IPDFRecursiveInterpreterHandler.h"

typedef std::vector<ObjectIDType> ObjectIDTypeVector;

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
    struct PDFNestingContext {
        ObjectIDTypeVector nestedXObjects;
    };

    PDFNestingContext* mNestingContext;

    // internal method used by higher level interpreters to call lower level xobject interpreters with nesting context
    bool InterpretXObjectContents(
        PDFParser* inParser,
        PDFStreamInput* inXObject,
        IPDFRecursiveInterpreterHandler* inHandler,
        PDFNestingContext* inNestingContext);     

    // internal method for intrepreting xobjects
    bool InterpretXObjectContentsInternal(
        PDFParser* inParser,
        PDFStreamInput* inXObject,
        IPDFRecursiveInterpreterHandler* inHandler);       

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