#include "TextPlacementsCollector.h"

#include "PDFObject.h"
#include "ParsedPrimitiveHelper.h"
#include "PDFLiteralString.h"
#include "PDFHexString.h"
#include "PDFObjectCast.h"
#include "PDFArray.h"
#include "PDFDictionary.h"
#include "PDFIndirectObjectReference.h"
#include "PDFObjectCast.h"
#include "PDFParser.h"

#include "Transformations.h"

using namespace std;

TextPlacementsCollector::TextPlacementsCollector() {

}

TextPlacementsCollector::~TextPlacementsCollector() {
}

void TextPlacementsCollector::Tc(double inCharSpace) {
    state.CurrentTextState().charSpace = inCharSpace;
}

void TextPlacementsCollector::Tw(double inWordSpace) {
    state.CurrentTextState().wordSpace = inWordSpace;
}

void TextPlacementsCollector::TL(double inLeading) {
    state.CurrentTextState().leading = inLeading;
}

void TextPlacementsCollector::setTm(const double (&matrix)[6]) {
    for(int i=0;i<6;++i) {
        state.CurrentTextState().tlm[i] = matrix[i];
        state.CurrentTextState().tm[i] = matrix[i];
    }
    state.CurrentTextState().tmDirty;
    state.CurrentTextState().tlmDirty;
}

void TextPlacementsCollector::Td(double inX, double inY) {
    double result[6];

    multiplyMatrix({1,0,0,1,inX,inY}, state.CurrentTextState().tlm, result);
    setTm(result);
}

void TextPlacementsCollector::TStar() {
    // there's an error in the book explanation
    // but we know better. leading goes below,
    // not up. this is further explicated by
    // the TD explanation
    Td(0,-state.CurrentTextState().leading);    
}

ByteList TextPlacementsCollector::ToBytesList(PDFObject* inObject) {
    ByteList result;
    
    switch(inObject->GetType())
    {
        case PDFObject::ePDFObjectLiteralString: {
            string str = ((PDFLiteralString*)inObject)->GetValue();
            for(string::iterator it = str.begin();it != str.end(); ++it)
                result.push_back((IOBasicTypes::Byte)(*it));
            break;
        }
        case PDFObject::ePDFObjectHexString: {
            string str = ((PDFHexString*)inObject)->GetValue();
            for(string::iterator it = str.begin();it != str.end(); ++it)
                result.push_back((IOBasicTypes::Byte)(*it));
            break;
        }
    }

    return result;  
}

void TextPlacementsCollector::textPlacement(const PlacedTextOperation& inTextPlacementOperation) {
    PlacedTextOperationList placements;
    placements.push_back(inTextPlacementOperation);
    textPlacement(placements);
    
}

void TextPlacementsCollector::textPlacement(const PlacedTextOperationList& inTextPlacementOperations) {
    state.PushPlacedTextOperations(inTextPlacementOperations);
  
}


void TextPlacementsCollector::Quote(PDFObject* inObject) {
    TStar();
    string asEncodedText = ParsedPrimitiveHelper(inObject).ToString();
    ByteList asBytes = ToBytesList(inObject);

    textPlacement({asEncodedText, asBytes});        
}

bool TextPlacementsCollector::onOperation(
    const std::string& inOperation,  
    const PDFObjectVector& inOperands) {

    // Graphic State Operators
    if (inOperation == "q") {
        state.PushGraphicState();
    } else if(inOperation == "Q") {
        state.PopGraphicState();
    } else if(inOperation == "cm") {
        double matrix[6];
        double result[6];

        for(int i=0;i<6;++i) {
             matrix[i] = ParsedPrimitiveHelper(inOperands[i]).GetAsDouble();
        }
        multiplyMatrix(matrix ,state.CurrentGraphicState().ctm, result);
        for(int i=0;i<6;++i) {
            state.CurrentGraphicState().ctm[i] = result[i];
        }
    } else if(inOperation == "gs") {
        string gsName = ParsedPrimitiveHelper(inOperands.back()).ToString();
        Resources& currentResources = resourcesStack.back();

        StringToGStateMap::iterator it = currentResources.gStates.find(gsName);
        if(it != currentResources.gStates.end()) {
            state.CurrentTextState().fontRef = it->second.fontRef;
            state.CurrentTextState().fontSize = it->second.fontSize;
        } // gstate not found, or does not have a fount...so not included in the first place...

    // Text State Operators
    } else if(inOperation == "Tc") {
        Tc(ParsedPrimitiveHelper(inOperands.back()).GetAsDouble());
    } else if(inOperation == "Tw") {
        Tw(ParsedPrimitiveHelper(inOperands.back()).GetAsDouble());
    } else if(inOperation == "Tz") {
        state.CurrentTextState().scale = ParsedPrimitiveHelper(inOperands.back()).GetAsDouble();
    } else if(inOperation == "TL") {
        TL(ParsedPrimitiveHelper(inOperands.back()).GetAsDouble());        
    } else if(inOperation == "Ts") {
        state.CurrentTextState().rise = ParsedPrimitiveHelper(inOperands.back()).GetAsDouble();
    } else if(inOperation == "Tf") {
        double size = ParsedPrimitiveHelper(inOperands.back()).GetAsDouble();
        string fontName = ParsedPrimitiveHelper(inOperands[inOperands.size()-2]).ToString();
        Resources& currentResources = resourcesStack.back();

        StringToFontMap::iterator it = currentResources.fonts.find(fontName);
        if(it != currentResources.fonts.end()) {
            state.CurrentTextState().fontRef = it->second.fontRef;
        } // should i have a default font policy here?! 80-20 gal, 80-20.
        state.CurrentTextState().fontSize = size;
    } else if(inOperation == "BT") {
        state.StartTextElement();
    } else if(inOperation == "ET") {
        state.EndTextPlacement();
        // Text positioining operators
    } else if(inOperation == "Td") {
        Td(ParsedPrimitiveHelper(inOperands[inOperands.size()-2]).GetAsDouble(), ParsedPrimitiveHelper(inOperands.back()).GetAsDouble());
    } else if(inOperation == "TD") {
        double param1 = ParsedPrimitiveHelper(inOperands[inOperands.size()-2]).GetAsDouble();
        double param2 =  ParsedPrimitiveHelper(inOperands.back()).GetAsDouble();
        TL(-param2);
        Td(param1, param2);
    } else if(inOperation == "Tm") {
        double matrix[6];

        for(int i=0;i<6;++i) {
             matrix[i] = ParsedPrimitiveHelper(inOperands[i]).GetAsDouble();
        }  
        setTm(matrix);      
    } else if(inOperation == "T*") {
        TStar();
    // Text placement operators
    } else if(inOperation == "Tj") {
        string asEncodedText = ParsedPrimitiveHelper(inOperands.back()).ToString();
        ByteList asBytes = ToBytesList(inOperands.back());

        textPlacement({asEncodedText, asBytes});
    } else if(inOperation == "\'") {
        Quote(inOperands.back());
    } else if(inOperation == "\"") {
        Tw(ParsedPrimitiveHelper(inOperands[inOperands.size()-3]).GetAsDouble());
        Tc(ParsedPrimitiveHelper(inOperands[inOperands.size()-2]).GetAsDouble());
        Quote(inOperands.back());

    } else if(inOperation == "TJ") {
        PlacedTextOperationList placements;
        PDFObjectCastPtr<PDFArray> arg;

        arg = inOperands.back();
        if(!!arg) {
            SingleValueContainerIterator<PDFObjectVector> it = arg->GetIterator();
            while(it.MoveNext()) {
                PDFObject* item = it.GetItem();
                if(item->GetType() == PDFObject::ePDFObjectLiteralString || item->GetType() == PDFObject::ePDFObjectHexString) {
                    string asEncodedText = ParsedPrimitiveHelper(item).ToString();
                    ByteList asBytes = ToBytesList(item);
                    placements.push_back({asEncodedText, asBytes});
                }
                else {
                    placements.push_back({ParsedPrimitiveHelper(item).GetAsDouble()});
                }
            }

            textPlacement(placements);
        }
    }

    return true;

}


bool TextPlacementsCollector::onResourcesRead(IInterpreterContext* inContext) {
    resourcesStack.push_back(Resources());

    Resources& currentResources = resourcesStack.back();

    // read extgstates for font references
    RefCountPtr<PDFDictionary> gstateCategoryDict = inContext->FindResourceCategory("ExtGState");
    if(!!gstateCategoryDict) {
        MapIterator<PDFNameToPDFObjectMap> it = gstateCategoryDict->GetIterator();

        while(it.MoveNext()) {
            PDFObject* gsInCat = it.GetValue();

            PDFDictionary* gsAsDict;
            if(gsInCat->GetType() == PDFObject::ePDFObjectIndirectObjectReference) {
                PDFObjectCastPtr<PDFDictionary> gsAsDictQ = inContext->GetParser()->ParseNewObject(((PDFIndirectObjectReference*)gsInCat)->mObjectID);
                gsAsDict = gsAsDictQ.GetPtr();
                gsAsDictQ->AddRef();
            }
            else if(gsInCat->GetType() == PDFObject::ePDFObjectDictionary) {
                gsAsDict = (PDFDictionary*)gsInCat;
            }

            if(gsAsDict) {
                // all i care about are font entries, so store it so i dont have to parse later (will cause trouble with interpretation)
                PDFObjectCastPtr<PDFArray> fontDesc = inContext->GetParser()->QueryDictionaryObject(gsAsDict, "Font");
                if(!!fontDesc) {
                    RefCountPtr<PDFObject> fontRef = fontDesc->QueryObject(0);
                    RefCountPtr<PDFObject> size = fontDesc->QueryObject(1);
                    double fontSize = ParsedPrimitiveHelper(size.GetPtr()).GetAsDouble();


                    currentResources.gStates.insert(StringToGStateMap::value_type(it.GetKey()->GetValue(), GSState(fontRef, fontSize)));
                }
                gsAsDict->Release();
            }
        }
    }

    // read font references
    RefCountPtr<PDFDictionary> fontCategoryDict = inContext->FindResourceCategory("Font");
    if(!!fontCategoryDict) {
        MapIterator<PDFNameToPDFObjectMap> it = fontCategoryDict->GetIterator();

        while(it.MoveNext()) {
            RefCountPtr<PDFObject> fontRef;
            fontRef = it.GetValue();

            currentResources.fonts.insert(StringToFontMap::value_type(it.GetKey()->GetValue(), Font(fontRef)));
        }
    }    

    return true;
}

void TextPlacementsCollector::onXObjectDoEnd(
    const std::string& inXObjectRefName,
    ObjectIDType inXObjectObjectID,
    PDFStreamInput* inXObject,
    PDFParser* inParser) {
    // im only use it to pop one level off the resources stack
    resourcesStack.pop_back();        
}

PlacedTextOperationWithEnvList& TextPlacementsCollector::onDone() {
    resourcesStack.clear();

    return state.texts;
}