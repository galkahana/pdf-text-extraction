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
static const string scID = "ID";
static const string scEI = "EI";

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

// internal class implementation for interpreter context
class InterpreterContext: public IInterpreterContext {
    public:
        InterpreterContext(PDFParser* inParser, PDFDictionary* inContentParent);
    
        virtual PDFDictionary* FindResourceCategory(const string& inResourceCategory);
        virtual PDFObject* FindResource(const string& inResourceName, const string& inResourceCategory);
        virtual PDFParser* GetParser();
        virtual PDFObjectParser* GetObjectParser();

        void SetObjectParser(PDFObjectParser* inObjectParser);
    private:
        PDFParser* parser;
        PDFDictionary* contentParent;
        PDFObjectParser* objectParser;

};

InterpreterContext::InterpreterContext(PDFParser* inParser, PDFDictionary* inContentParent) {
    parser = inParser;
    contentParent = inContentParent;
    objectParser = NULL;
}

void InterpreterContext::SetObjectParser(PDFObjectParser* inObjectParser) {
    objectParser = inObjectParser;    
}

PDFDictionary* InterpreterContext::FindResourceCategory(const string& inResourceCategory) {
    PDFObjectCastPtr<PDFDictionary> resourcesDict(FindInheritedResources(parser, contentParent));

    if(!resourcesDict)
        return NULL;

    PDFObjectCastPtr<PDFDictionary> categoryDictionary(parser->QueryDictionaryObject(resourcesDict.GetPtr(), inResourceCategory));

    if(!categoryDictionary)
        return NULL;

    categoryDictionary->AddRef(); // wanted the objectcastptr to also verify for dict...so make sure to keep this object alive here...
    return categoryDictionary.GetPtr();
}

PDFObject* InterpreterContext::FindResource(const string& inResourceName, const string& inResourceCategory) {
    RefCountPtr<PDFDictionary> categoryDict = FindResourceCategory(inResourceCategory);

    return categoryDict->QueryDirectObject(inResourceName);
}

PDFParser* InterpreterContext::GetParser() {
    return parser;
}

PDFObjectParser* InterpreterContext::GetObjectParser() {
    return objectParser;
}



PDFRecursiveInterpreter::PDFRecursiveInterpreter(void) {

}

PDFRecursiveInterpreter::~PDFRecursiveInterpreter(void) {

}

static const Byte scEISample[2] = {'E','I'};
static const Byte scWhiteSpaces[6] = {0,0x9,0xA,0xC,0xD,0x20};

static const bool IsEIFinishSample(Byte (&buffer)[3]) {
    // check that last 2 are EI
    if(buffer[2] != scEISample[1])
        return false;
    if(buffer[1] != scEISample[0])
        return false;
    // first buffer should be some PDF space buffer
    return (
        buffer[0] == scWhiteSpaces[0] ||
        buffer[0] == scWhiteSpaces[1] ||
        buffer[0] == scWhiteSpaces[2] ||
        buffer[0] == scWhiteSpaces[3] ||
        buffer[0] == scWhiteSpaces[4] ||
        buffer[0] == scWhiteSpaces[5]
    );
}

void PDFRecursiveInterpreter::SkipInlinImageTillEI(PDFObjectParser* inObjectParser) {
    /*
        So, what we're gonna do is this.
        now we're at DI...need to get to EI.
        it's a bit hard to tell how we'll know, but fairly safe to assume
        that there'll be a PDF space char/line char and then EI. samples
        seem to show an extra > prior...but i'm not seeing any evidences in the spec, so ignore.
        wish specs had better explanation on how to skip them...which does not seem to mean to actually
        decode the image data.
    */
   IByteReader* reader = inObjectParser->StartExternalRead();
   Byte buffer[3];

    do {
        // read first 3 bytes
        if(reader->Read(buffer,3) != 3)
            break;

        // read next chars, 1 at a time till finiding EI after a space/el
        while(!IsEIFinishSample(buffer)) {
            buffer[0] = buffer[1];
            buffer[1] = buffer[2];
            if(reader->Read(buffer+2,1) != 1)
                break;
        }


    } while(false);

   inObjectParser->EndExternalRead();
}

static const string scForm = "Form";

static bool IsForm(PDFStreamInput* formCandidate) {
    // check its subtype...don't wanna get into an image....
    RefCountPtr<PDFDictionary> formDict = formCandidate->QueryStreamDictionary();
    if(!formCandidate)
        return false;
    PDFObjectCastPtr<PDFName> formSubtype = formDict->QueryDirectObject("Subtype"); 
    return formSubtype->GetValue() == scForm;
}

bool PDFRecursiveInterpreter::InterpretContentStream(
    PDFParser* inParser,
    PDFDictionary* inContentParent,
    PDFObjectParser* inObjectParser,
    InterpreterContext* inContext,
    IPDFRecursiveInterpreterHandler* inHandler
) {
    if(inObjectParser == NULL) // hmmm. something didn't work with creating an object parser. possibly an uknown
                               // filter?
        return true;

    inContext->SetObjectParser(inObjectParser);

    PDFObjectVector operandsStack;
    bool shouldContinue = true;

    PDFObject* anObject = inObjectParser->ParseNewObject();

    while(!!anObject && shouldContinue) {
        if(anObject->GetType() == PDFObject::ePDFObjectSymbol) {
            PDFSymbol* anOperand = (PDFSymbol*)anObject;
            // Call handler for operation event
            shouldContinue = inHandler->onOperation(anOperand->GetValue(), operandsStack, inContext);
            
            bool shouldRecurseIntoForm = false;
            bool shouldSkipInlineImage = false;
            string formName;

            // Some control decisions for the interpreter on special kinds of operations
            if(anOperand->GetValue() == scDo) {
                // should recurse into form. save name for now
                if(operandsStack.size() == 1 && operandsStack[0]->GetType() == PDFObject::ePDFObjectName) {
                    formName = ((PDFName*)operandsStack[0])->GetValue();
                    shouldRecurseIntoForm = true;
                }
            }

            if(anOperand->GetValue() == scID && inHandler->ShouldSkipInlineImage()) {
                // mark for skipping the content of this image
                shouldSkipInlineImage = true;
            }

            // release operations and operands
            anOperand->Release();
            FreeObjectVector(operandsStack);

            if(!shouldContinue)
                break;

            // now for implementing the special operations

            if(shouldRecurseIntoForm) {
                // k. user didn't cancel, let's dive into form
                LongFilePositionType currentPosition = inParser->GetParserStream()->GetCurrentPosition();
                PDFObjectCastPtr<PDFIndirectObjectReference> xobjectRef = inContext->FindResource(formName, "XObject");
                ObjectIDType formObjectID = !xobjectRef ? 0 : xobjectRef->mObjectID;
                PDFObjectCastPtr<PDFStreamInput> formObject(inParser->ParseNewObject(formObjectID));
                if(!!formObject && IsForm(formObject.GetPtr())) {  
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
            } else if(shouldSkipInlineImage) {
                SkipInlinImageTillEI(inObjectParser);
                // for completion, have onOperation for EI
                shouldContinue = inHandler->onOperation(scEI, PDFObjectVector(), inContext);
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
        
    InterpreterContext context(inParser, inPage);
    inHandler->onResourcesRead(&context);

    if(contents->GetType() == PDFObject::ePDFObjectArray) {
        return InterpretContentStream(inParser, inPage, inParser->StartReadingObjectsFromStreams((PDFArray*)contents.GetPtr()),&context, inHandler);
    }
    else if(contents->GetType() == PDFObject::ePDFObjectStream) {
        return InterpretContentStream(inParser, inPage, inParser->StartReadingObjectsFromStream((PDFStreamInput*)contents.GetPtr()),&context , inHandler);
    }

    return true;
}

bool PDFRecursiveInterpreter::InterpretXObjectContents(
    PDFParser* inParser,
    PDFStreamInput* inXObject,
    IPDFRecursiveInterpreterHandler* inHandler) {
    RefCountPtr<PDFDictionary> xobjectDict(inXObject->QueryStreamDictionary());
    
    InterpreterContext context(inParser, xobjectDict.GetPtr());
    inHandler->onResourcesRead(&context);

    return InterpretContentStream(inParser, xobjectDict.GetPtr(), inParser->StartReadingObjectsFromStream(inXObject),&context, inHandler);
}