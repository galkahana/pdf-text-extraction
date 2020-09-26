#include "PDFRecursiveInterpreter.h"
#include "PDFObjectCast.h"
#include "PDFDictionary.h"
#include "RefCountPtr.h"
#include "PDFObjectCast.h"
#include "PDFParser.h"
#include "PDFArray.h"
#include "PDFStreamInput.h"
#include "PDFSymbol.h"
#include "PDFIndirectObjectReference.h"

#include "IPDFRecursiveInterpreterHandler.h"

#include <string>

using namespace std;
using namespace PDFHummus;

static const string scContents = "Contents";
static const string scDo = "Do";

static void FreeObjectVector(PDFObjectVector& ioVector) {
	PDFObjectVector::iterator it = ioVector.begin();

	for(; it != ioVector.end(); ++it)
		(*it)->Release();  

    ioVector.clear();  
}

static PDFObject* FindInheritedResources(PDFParser* inParser,PDFDictionary* inDictionary) {
	if(inDictionary->Exists("Resources")) {
		return inParser->QueryDictionaryObject(inDictionary, "Resources");
	}
	else {
		PDFObjectCastPtr<PDFDictionary> parentDict(
			inDictionary->Exists("Parent") ? 
				inParser->QueryDictionaryObject(inDictionary, "Parent"): 
				NULL);
		if(!parentDict) {
			return NULL;
		}
		else {
			return FindInheritedResources(inParser,parentDict.GetPtr());
		}
		
	}
}

static ObjectIDType FindFormInResources(const string& inFormName,PDFParser* inParser,PDFDictionary* inDictionary) {
    PDFObjectCastPtr<PDFDictionary> resourcesDict(FindInheritedResources(inParser, inDictionary));

    if(!resourcesDict)
        return 0;

    PDFObjectCastPtr<PDFDictionary> xobjectsDictionary(inParser->QueryDictionaryObject(resourcesDict.GetPtr(), "XObject"));

    if(!xobjectsDictionary)
        return 0;

    PDFObjectCastPtr<PDFIndirectObjectReference> xobjectRef(xobjectsDictionary->QueryDirectObject(inFormName));

    if(!xobjectRef)
        return 0;

    return xobjectRef->mObjectID;
}

PDFRecursiveInterpreter::PDFRecursiveInterpreter(void) {

}

PDFRecursiveInterpreter::~PDFRecursiveInterpreter(void) {

}

bool PDFRecursiveInterpreter::InterpretContentStream(
    PDFParser* inParser,
    PDFDictionary* inContentParent,
    PDFObjectParser* inObjectParser,
    IPDFRecursiveInterpreterHandler* inHandler
) {
    PDFObjectVector operandsStack;
    bool shouldContinue = true;

    PDFObject* anObject = inObjectParser->ParseNewObject();

    while(!!anObject && shouldContinue) {
        if(anObject->GetType() == PDFObject::ePDFObjectSymbol) {
            PDFSymbol* anOperand = (PDFSymbol*)anObject;
            shouldContinue = inHandler->onOperation(anOperand->GetValue(), operandsStack);
            bool shouldResurseIntoForm = false;
            string formName;

            if(anOperand->GetValue() == scDo) {
                // should recurse into form. save name for now
                if(operandsStack.size() == 1 && operandsStack[0]->GetType() == PDFObject::ePDFObjectName) {
                    formName = ((PDFName*)operandsStack[0])->GetValue();
                    shouldResurseIntoForm = true;
                }
            }

            anOperand->Release();
            FreeObjectVector(operandsStack);

            if(!shouldContinue)
                break;

            if(shouldResurseIntoForm) {
                // k. user didn't cancel, let's dive into form
                LongFilePositionType currentPosition = inParser->GetParserStream()->GetCurrentPosition();
                ObjectIDType formObjectID = FindFormInResources(formName, inParser, inContentParent);
                PDFObjectCastPtr<PDFStreamInput> formObject(inParser->ParseNewObject(formObjectID));
                if(!!formObject) {
                    bool shouldRecurse = inHandler->onXObjectDoStart(formName, formObjectID, formObject.GetPtr(), inParser);
                    if(shouldRecurse) {
                        PDFRecursiveInterpreter subordinateInterpreter;
                        shouldContinue = subordinateInterpreter.InterpretXObjectContents(
                            inParser,
                            formObject.GetPtr(),
                            inHandler
                        );
                    }
                    inHandler->onXObjectDoEnd(formName, formObjectID, formObject.GetPtr(), inParser);
                }

                // restore stream position (hopefully this is enough to continue from where we were...)
                inParser->GetParserStream()->SetPosition(currentPosition);
            }
        }
        else {
            operandsStack.push_back(anObject);
        }
        anObject = inObjectParser->ParseNewObject();
    }

    FreeObjectVector(operandsStack);
    delete inObjectParser; // The passed object parser is owned by this method, so dispose when done

    return shouldContinue;
}


bool PDFRecursiveInterpreter::InterpretPageContents(
    PDFParser* inParser,
    PDFDictionary* inPage,
    IPDFRecursiveInterpreterHandler* inHandler) {

    
    RefCountPtr<PDFObject> contents(inParser->QueryDictionaryObject(inPage, scContents));
    if(!contents)
        return true;

    if(contents->GetType() == PDFObject::ePDFObjectArray) {
        return InterpretContentStream(inParser, inPage, inParser->StartReadingObjectsFromStreams((PDFArray*)contents.GetPtr()), inHandler);
    }
    else if(contents->GetType() == PDFObject::ePDFObjectStream) {
        return InterpretContentStream(inParser, inPage, inParser->StartReadingObjectsFromStream((PDFStreamInput*)contents.GetPtr()), inHandler);
    }

    return true;
}

bool PDFRecursiveInterpreter::InterpretXObjectContents(
    PDFParser* inParser,
    PDFStreamInput* inXObject,
    IPDFRecursiveInterpreterHandler* inHandler) {
    RefCountPtr<PDFDictionary> xobjectDict(inXObject->QueryStreamDictionary());

    return InterpretContentStream(inParser, xobjectDict.GetPtr(), inParser->StartReadingObjectsFromStream(inXObject), inHandler);
}