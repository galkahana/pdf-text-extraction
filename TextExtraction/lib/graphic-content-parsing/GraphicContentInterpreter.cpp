#include "GraphicContentInterpreter.h"

#include "RefCountPtr.h"
#include "PDFObject.h"
#include "ParsedPrimitiveHelper.h"
#include "PDFObjectCast.h"
#include "PDFArray.h"
#include "PDFLiteralString.h"
#include "PDFHexString.h"
#include "PDFDictionary.h"
#include "PDFIndirectObjectReference.h"
#include "PDFParser.h"
#include "PDFStreamInput.h"


#include "../math/Transformations.h"
#include "../interpreter/PDFRecursiveInterpreter.h"
#include "../pdf-writer-enhancers/Bytes.h"

using namespace std;

GraphicContentInterpreter::GraphicContentInterpreter(void) {
    handler = NULL;
}

GraphicContentInterpreter::~GraphicContentInterpreter(void) {
    resetInterpretationState();
}

bool GraphicContentInterpreter::InterpretPageContents(
    PDFParser* inParser,
    PDFDictionary* inPage,
    IGraphicContentInterpreterHandler* inHandler) {
    
    if(!inHandler) // yeah im gonna require a handler here.
        return true;

    PDFRecursiveInterpreter interpreter;

    handler = inHandler;
    initInterpretationState();
    bool result = interpreter.InterpretPageContents(inParser, inPage, this); 
    handler->onDone();
    resetInterpretationState();
    return result;
}

void GraphicContentInterpreter::initInterpretationState() {
    graphicStateStack.push_back(ContentGraphicState());
}

void GraphicContentInterpreter::resetInterpretationState() {
    handler = NULL;

    resourcesStack.clear();
    graphicStateStack.clear();
    textGraphicStateStack.clear();
    isInTextElement = false;
    currentTextElementCommands.clear();
}


bool GraphicContentInterpreter::onOperation(const std::string& inOperation,  const PDFObjectVector& inOperands, IInterpreterContext* inContext) {
    if (inOperation == "q") {
        return qCommand();
    } else if(inOperation == "Q") {
        return QCommand();
    } else if(inOperation == "cm") {
        return cmCommand(inOperands);
    } else if(inOperation == "gs") {
        return gsCommand(inOperands);
    } else if(inOperation == "Tc") {
        return TcCommand(inOperands);
    } else if(inOperation == "Tw") {
        return TwCommand(inOperands);
    } else if(inOperation == "Tz") {
        return TzCommand(inOperands);
    } else if(inOperation == "TL") {
        return TLCommand(inOperands);
    } else if(inOperation == "Ts") {
        return TsCommand(inOperands);
    } else if(inOperation == "Tf") {
        return TfCommand(inOperands);
    } else if(inOperation == "BT") {
        return BTCommand();
    } else if(inOperation == "ET") {
        return ETCommand();
    } else if(inOperation == "Td") {
        return TdCommand(inOperands);
    } else if(inOperation == "TD") {
        return TDCommand(inOperands);
    } else if(inOperation == "Tm") {
        return TmCommand(inOperands);
    } else if(inOperation == "T*") {
        return TStarCommand();
    } else if(inOperation == "Tj") {
        return TjCommand(inOperands);
    } else if(inOperation == "\'") {
        return QuoteCommand(inOperands);
    } else if(inOperation == "\"") {
        return DoubleQuoteCommand(inOperands);
    } else if(inOperation == "TJ") {
        return TJCommand(inOperands);
    }

    return true;
}

void GraphicContentInterpreter::pushGraphicState() {
    graphicStateStack.push_back(ContentGraphicState(graphicStateStack.back()));
    if(isInTextElement)
        textGraphicStateStack.push_back(TextGraphicState(textGraphicStateStack.back()));    
}

bool GraphicContentInterpreter::qCommand() {
    pushGraphicState();
    return true;
}

void GraphicContentInterpreter::popGraphicState() {
    if(graphicStateStack.size() > 1)
        graphicStateStack.pop_back();
    if(isInTextElement && textGraphicStateStack.size() > 1)
        textGraphicStateStack.pop_back();
}


bool GraphicContentInterpreter::QCommand() {
    popGraphicState();
    return true;
}

ContentGraphicState& GraphicContentInterpreter::currentGraphicState() {
    return graphicStateStack.back();
}

void GraphicContentInterpreter::cm(const double (&matrix)[6]) {
    double buffer[6];

    multiplyMatrix(matrix ,currentGraphicState().ctm, buffer);
    copyMatrix(buffer, currentGraphicState().ctm);
}

bool GraphicContentInterpreter::cmCommand(const PDFObjectVector& inOperands) {
    if(inOperands.size() < 6)
        return true; // too few params? ignore

    double matrix[6];
    for(int i=0;i<6;++i) {
            matrix[i] = ParsedPrimitiveHelper(inOperands[i]).GetAsDouble();
    }
    cm(matrix);
    return true;
}

TextGraphicState& GraphicContentInterpreter::currentTextState() {
    if(isInTextElement) {
        return textGraphicStateStack.back();
    }
    
    return graphicStateStack.back().textGraphicState;
}

bool GraphicContentInterpreter::gsCommand(const PDFObjectVector& inOperands) {
    if(inOperands.size() < 1)
        return true; // too few params? ignore

    string gsName = ParsedPrimitiveHelper(inOperands.back()).ToString();
    Resources& currentResources = resourcesStack.back();

    StringToGStateMap::iterator it = currentResources.gStates.find(gsName);
    if(it != currentResources.gStates.end()) {
        currentTextState().fontRef = it->second.fontRef;
        currentTextState().fontSize = it->second.fontSize;
    } // gstate will not be found if name is wrong, or that it didn't get collected cause didn't have interesting info for the task at hand
    return true;
}

void GraphicContentInterpreter::Tc(double inCharSpace) {
    currentTextState().charSpace = inCharSpace;
}

bool GraphicContentInterpreter::TcCommand(const PDFObjectVector& inOperands) {
    if(inOperands.size() < 1)
        return true; // too few params? ignore

    Tc(ParsedPrimitiveHelper(inOperands.back()).GetAsDouble());
    return true;
}

void GraphicContentInterpreter::Tw(double inWordSpace) {
    currentTextState().wordSpace = inWordSpace;
}

bool GraphicContentInterpreter::TwCommand(const PDFObjectVector& inOperands) {
    if(inOperands.size() < 1)
        return true; // too few params? ignore

    Tw(ParsedPrimitiveHelper(inOperands.back()).GetAsDouble());
    return true;
}

bool GraphicContentInterpreter::TzCommand(const PDFObjectVector& inOperands) {
    if(inOperands.size() < 1)
        return true; // too few params? ignore

    currentTextState().scale = ParsedPrimitiveHelper(inOperands.back()).GetAsDouble();
    return true;
}

void GraphicContentInterpreter::TL(double inLeading) {
    currentTextState().leading = inLeading;
}

bool GraphicContentInterpreter::TLCommand(const PDFObjectVector& inOperands) {
    if(inOperands.size() < 1)
        return true; // too few params? ignore

    TL(ParsedPrimitiveHelper(inOperands.back()).GetAsDouble());        
    return true;
}


bool GraphicContentInterpreter::TsCommand(const PDFObjectVector& inOperands) {
    if(inOperands.size() < 1)
        return true; // too few params? ignore

    currentTextState().rise = ParsedPrimitiveHelper(inOperands.back()).GetAsDouble();
    return true;
}

bool GraphicContentInterpreter::TfCommand(const PDFObjectVector& inOperands) {
    if(inOperands.size() < 1)
        return true; // too few params? ignore

    double size = ParsedPrimitiveHelper(inOperands.back()).GetAsDouble();
    if(inOperands.size() > 1) {
        string fontName = ParsedPrimitiveHelper(inOperands[inOperands.size()-2]).ToString();
        Resources& currentResources = resourcesStack.back();

        StringToFontMap::iterator it = currentResources.fonts.find(fontName);
        if(it != currentResources.fonts.end()) {
            currentTextState().fontRef = it->second.fontRef;
        } // should i have a default font policy here?! 80-20 gal, 80-20.
    }
    currentTextState().fontSize = size;
    return true;
}

void GraphicContentInterpreter::startTextElement() {
    isInTextElement = true;
    currentTextElementCommands.clear();
    textGraphicStateStack.clear();
    textGraphicStateStack.push_back(TextGraphicState(graphicStateStack.back().textGraphicState));
}


bool GraphicContentInterpreter::BTCommand() {
    startTextElement();
    return true;
}

bool GraphicContentInterpreter::endTextElement() {
    if(!isInTextElement) // ET without BT. ignore.
        return true;

    isInTextElement = false;

    // copy text graphic state from text element graphic state to main graphic state
    // for those operators that data is supposed to retain past text element boundaries
    TextGraphicState& source = textGraphicStateStack.back();
    TextGraphicState& target = graphicStateStack.back().textGraphicState;
    target.charSpace = source.charSpace;
    target.wordSpace = source.wordSpace;
    target.scale = source.scale;
    target.leading = source.leading;
    target.rise = source.rise;
    target.fontRef = source.fontRef;
    target.fontSize = source.fontSize;

    // prep result
    TextElement el = {PlacedTextCommandList(currentTextElementCommands)};

    // clear text element state
    currentTextElementCommands.clear();
    textGraphicStateStack.clear();

    // forward the new text element to the client
    return handler->onTextElementComplete(el);
}

bool GraphicContentInterpreter::ETCommand() {
    return endTextElement();
}

void GraphicContentInterpreter::setTm(const double (&matrix)[6]) {
    TextGraphicState& state = currentTextState();

    copyMatrix(matrix, state.tlm);
    copyMatrix(matrix, state.tm);
    state.tmDirty = true;
    state.tlmDirty = true;
}


void GraphicContentInterpreter::Td(double inX, double inY) {
    double result[6];

    double tMatrix[6] = {1,0,0,1,inX,inY};

    multiplyMatrix(tMatrix, currentTextState().tlm, result);
    setTm(result);
}

bool GraphicContentInterpreter::TdCommand(const PDFObjectVector& inOperands) {
    if(inOperands.size() < 2)
        return true; // too few params? ignore

    Td(ParsedPrimitiveHelper(inOperands[inOperands.size()-2]).GetAsDouble(), ParsedPrimitiveHelper(inOperands.back()).GetAsDouble());
    return true;
}

bool GraphicContentInterpreter::TDCommand(const PDFObjectVector& inOperands) {
    if(inOperands.size() < 2)
        return true; // too few params? ignore

    double param1 = ParsedPrimitiveHelper(inOperands[inOperands.size()-2]).GetAsDouble();
    double param2 =  ParsedPrimitiveHelper(inOperands.back()).GetAsDouble();
    TL(-param2);
    Td(param1, param2);
    return true;
}

bool GraphicContentInterpreter::TmCommand(const PDFObjectVector& inOperands) {
    if(inOperands.size() < 6)
        return true; // too few params? ignore

    double matrix[6];

    for(int i=0;i<6;++i) {
        matrix[i] = ParsedPrimitiveHelper(inOperands[i]).GetAsDouble();
    }  
    setTm(matrix);      
    return true;
}

void GraphicContentInterpreter::TStar() {
    // there's an error in the book explanation
    // but we know better. leading goes below,
    // not up. this is further explicated by
    // the TD explanation
    Td(0,-currentTextState().leading);    
}

bool GraphicContentInterpreter::TStarCommand() {
    TStar();
    return true;
}

void GraphicContentInterpreter::recordTextPlacement(const PlacedTextCommandArgument& inTextPlacementOperation) {
    PlacedTextCommandArgumentList placements;
    placements.push_back(inTextPlacementOperation);
    recordTextPlacement(placements);
}

void GraphicContentInterpreter::recordTextPlacement(const PlacedTextCommandArgumentList& inTextPlacementOperations) {
    PlacedTextCommand el = {
        inTextPlacementOperations,
        ContentGraphicState(currentGraphicState()),
        TextGraphicState(currentTextState())
    };
    currentTextElementCommands.push_back(el);
}

bool GraphicContentInterpreter::TjCommand(const PDFObjectVector& inOperands) {
    if(inOperands.size() < 1)
        return true; // too few params? ignore

    recordTextPlacement(PlacedTextCommandArgument(ToBytesList(inOperands.back())));
    return true;
}

void GraphicContentInterpreter::Quote(PDFObject* inObject) {
    TStar();
    recordTextPlacement(PlacedTextCommandArgument(ToBytesList(inObject)));        
}

bool GraphicContentInterpreter::QuoteCommand(const PDFObjectVector& inOperands) {
    if(inOperands.size() < 1)
        return true; // too few params? ignore

    Quote(inOperands.back());
    return true;
}

bool GraphicContentInterpreter::DoubleQuoteCommand(const PDFObjectVector& inOperands) {
    if(inOperands.size() < 3)
        return true; // too few params? ignore

    Tw(ParsedPrimitiveHelper(inOperands[inOperands.size()-3]).GetAsDouble());
    Tc(ParsedPrimitiveHelper(inOperands[inOperands.size()-2]).GetAsDouble());
    Quote(inOperands.back());
    return true;
}

bool GraphicContentInterpreter::TJCommand(const PDFObjectVector& inOperands) {
    if(inOperands.size() < 1)
        return true; // too few params? ignore
    
    PlacedTextCommandArgumentList placements;
    PDFObjectCastPtr<PDFArray> arg;

    arg = inOperands.back();
    if(!arg)
        return true;
    SingleValueContainerIterator<PDFObjectVector> it = arg->GetIterator();
    while(it.MoveNext()) {
        PDFObject* item = it.GetItem();
        if(item->GetType() == PDFObject::ePDFObjectLiteralString || item->GetType() == PDFObject::ePDFObjectHexString) {
            string asEncodedText = ParsedPrimitiveHelper(item).ToString();
            ByteList asBytes = ToBytesList(item);
            placements.push_back(PlacedTextCommandArgument(asBytes));
        }
        else {
            placements.push_back(PlacedTextCommandArgument(ParsedPrimitiveHelper(item).GetAsDouble()));
        }
    }

    recordTextPlacement(placements);
    return true;
}

bool GraphicContentInterpreter::onResourcesRead(IInterpreterContext* inContext) {
    resourcesStack.push_back(Resources()); // pushs on page start, and also on any drawn xobject start

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

    return handler->onResourcesRead(currentResources, inContext);
}

bool GraphicContentInterpreter::onXObjectDoStart(
        const std::string& inXObjectRefName,
        ObjectIDType inXObjectObjectID,
        PDFStreamInput* inXObject,
        PDFParser* inParser) {
    // the equivalent of q, so any internal transformations do not effect the outside. specifically what im gonna
    // do now to emulate form placement matrix changes
    pushGraphicState();

    // apply form matrix
    RefCountPtr<PDFDictionary> formDict = inXObject->QueryStreamDictionary();
    PDFObjectCastPtr<PDFArray> formMatrix = inParser->QueryDictionaryObject(formDict.GetPtr(), "Matrix");
    if(!formMatrix || formMatrix->GetLength() < 6)
        return true;

    double matrix[6];
    for(int i=0;i<6;++i) {
        RefCountPtr<PDFObject> item = formMatrix->QueryObject(i);
        matrix[i] = ParsedPrimitiveHelper(item.GetPtr()).GetAsDouble();
    }
    cm(matrix);

    return true;
}

void GraphicContentInterpreter::onXObjectDoEnd(
    const std::string& inXObjectRefName,
    ObjectIDType inXObjectObjectID,
    PDFStreamInput* inXObject,
    PDFParser* inParser) {

    // pop resources stack (was placed on resources read, which comes right when you start reading the form)
    resourcesStack.pop_back();        

    // the equivalent of Q removing all artifacts of the form state changes
    popGraphicState();

}