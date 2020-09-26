#include "PDFInterpreter.h"
#include "PDFObjectCast.h"
#include "PDFDictionary.h"
#include "RefCountPtr.h"
#include "PDFObjectCast.h"
#include "PDFParser.h"
#include "PDFArray.h"
#include "PDFStreamInput.h"
#include "PDFSymbol.h"

#include "IPDFInterpreterHandler.h"

#include <string>

using namespace std;
using namespace PDFHummus;

static const string scContents = "Contents";

static void FreeObjectVector(PDFObjectVector& ioVector) {
	PDFObjectVector::iterator it = ioVector.begin();

	for(; it != ioVector.end(); ++it)
		(*it)->Release();  

    ioVector.clear();  
}

PDFInterpreter::PDFInterpreter(void) {

}

PDFInterpreter::~PDFInterpreter(void) {

}

void PDFInterpreter::InterpretContentStream(
    PDFObjectParser* inObjectParser,
    IPDFInterpreterHandler* inHandler
) {
    PDFObjectVector operandsStack;

    PDFObject* anObject = inObjectParser->ParseNewObject();

    while(!!anObject) {
        if(anObject->GetType() == PDFObject::ePDFObjectSymbol) {
            PDFSymbol* anOperand = (PDFSymbol*)anObject;
            bool shouldContinue = inHandler->onOperation(anOperand->GetValue(), operandsStack);

            anOperand->Release();
            FreeObjectVector(operandsStack);

            if(!shouldContinue)
                break;
        }
        else {
            operandsStack.push_back(anObject);
        }
        anObject = inObjectParser->ParseNewObject();
    }

    FreeObjectVector(operandsStack);
    delete inObjectParser; // The passed object parser is owned by this method, so dispose when done
}


void PDFInterpreter::InterpretPageContents(
    PDFParser* inParser,
    PDFDictionary* inPage,
    IPDFInterpreterHandler* inHandler) {

    
    RefCountPtr<PDFObject> contents(inParser->QueryDictionaryObject(inPage, scContents));
    if(!contents)
        return;

    if(contents->GetType() == PDFObject::ePDFObjectArray) {
        InterpretContentStream(inParser->StartReadingObjectsFromStreams((PDFArray*)contents.GetPtr()), inHandler);
    }
    else if(contents->GetType() == PDFObject::ePDFObjectStream) {
        InterpretContentStream(inParser->StartReadingObjectsFromStream((PDFStreamInput*)contents.GetPtr()), inHandler);
    }
}

void PDFInterpreter::InterpretXObjectContents(
    PDFParser* inParser,
    PDFStreamInput* inXObject,
    IPDFInterpreterHandler* inHandler) {
    InterpretStreamContents(inParser, inXObject, inHandler);
}

void PDFInterpreter::InterpretStreamContents(
    PDFParser* inParser,
    PDFStreamInput* inStream,
    IPDFInterpreterHandler* inHandler) {
    InterpretContentStream(inParser->StartReadingObjectsFromStream(inStream), inHandler);

}