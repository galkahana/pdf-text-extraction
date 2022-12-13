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
    ResetInterpretationState();
}

bool GraphicContentInterpreter::InterpretPageContents(
    PDFParser* inParser,
    PDFDictionary* inPage,
    IGraphicContentInterpreterHandler* inHandler) {
    
    if(!inHandler) // yeah im gonna require a handler here.
        return true;

    PDFRecursiveInterpreter interpreter;

    handler = inHandler;
    InitInterpretationState();
    bool result = interpreter.InterpretPageContents(inParser, inPage, this); 
    ResetInterpretationState();
    return result;
}

void GraphicContentInterpreter::InitInterpretationState() {
    graphicStateStack.push_back(ContentGraphicState());
}

void GraphicContentInterpreter::ClearCurrentPath() {
    currentPath.subPaths.clear();
}

void GraphicContentInterpreter::ResetInterpretationState() {
    handler = NULL;

    ClearCurrentPath();
    resourcesStack.clear();
    graphicStateStack.clear();
    textGraphicStateStack.clear();
    isInTextElement = false;
    currentTextElementCommands.clear();
}


bool GraphicContentInterpreter::OnOperation(const std::string& inOperation,  const PDFObjectVector& inOperands, IInterpreterContext* inContext) {
    if (inOperation == "q") {
        // graphic state operators
        return qCommand();
    } else if(inOperation == "Q") {
        return QCommand();
    } else if(inOperation == "cm") {
        return cmCommand(inOperands);
    } else if(inOperation == "w") {
        return wCommand(inOperands);
    } else if(inOperation == "gs") {
        return gsCommand(inOperands);
    } else if(inOperation == "Tc") {
        // text state operators
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
        // text positioining operators
        return TdCommand(inOperands);
    } else if(inOperation == "TD") {
        return TDCommand(inOperands);
    } else if(inOperation == "Tm") {
        return TmCommand(inOperands);
    } else if(inOperation == "T*") {
        return TStarCommand();
    } else if(inOperation == "Tj") {
        // text placement operators
        return TjCommand(inOperands);
    } else if(inOperation == "\'") {
        return QuoteCommand(inOperands);
    } else if(inOperation == "\"") {
        return DoubleQuoteCommand(inOperands);
    } else if(inOperation == "TJ") {
        return TJCommand(inOperands);
    } else if(inOperation == "m") {
        // path construction operators
        return mCommand(inOperands);
    } else if(inOperation == "l") {
        return lCommand(inOperands);
    } else if(inOperation == "c") {
        return cCommand(inOperands);
    } else if(inOperation == "v") {
        return vCommand(inOperands);
    } else if(inOperation == "y") {
        return yCommand(inOperands);
    } else if(inOperation == "h") {
        return hCommand(inOperands);
    } else if(inOperation == "re") {
        return reCommand(inOperands);
    } else if(inOperation == "S") {
        // path painting operators
        return SCommand(inOperands);
    } else if(inOperation == "s") {
        return sCommand(inOperands);
    } else if(inOperation == "f") {
        return fCommand(inOperands);
    } else if(inOperation == "F") {
        // used for compatibility...equivalent to "f"
        return fCommand(inOperands);
    } else if(inOperation == "f*") {
        return fStarCommand(inOperands);
    } else if(inOperation == "B") {
        return BCommand(inOperands);
    } else if(inOperation == "B*") {
        return BStarCommand(inOperands);
    } else if(inOperation == "b") {
        return bCommand(inOperands);
    } else if(inOperation == "b*") {
        return bStarCommand(inOperands);
    } else if(inOperation == "n") {
        return nCommand(inOperands);
    }

    return true;
}

void GraphicContentInterpreter::PushGraphicState() {
    graphicStateStack.push_back(ContentGraphicState(graphicStateStack.back()));
    if(isInTextElement)
        textGraphicStateStack.push_back(TextGraphicState(textGraphicStateStack.back()));    
}

bool GraphicContentInterpreter::qCommand() {
    PushGraphicState();
    return true;
}

void GraphicContentInterpreter::PopGraphicState() {
    if(graphicStateStack.size() > 1)
        graphicStateStack.pop_back();
    if(isInTextElement && textGraphicStateStack.size() > 1)
        textGraphicStateStack.pop_back();
}


bool GraphicContentInterpreter::QCommand() {
    PopGraphicState();
    return true;
}

ContentGraphicState& GraphicContentInterpreter::CurrentGraphicState() {
    return graphicStateStack.back();
}

void GraphicContentInterpreter::cm(const double (&matrix)[6]) {
    double buffer[6];

    MultiplyMatrix(matrix ,CurrentGraphicState().ctm, buffer);
    CopyMatrix(buffer, CurrentGraphicState().ctm);
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

bool GraphicContentInterpreter::wCommand(const PDFObjectVector& inOperands) {
    if(inOperands.size() < 1)
        return true; // too few params? ignore

    CurrentGraphicState().lineWidth = ParsedPrimitiveHelper(inOperands.back()).GetAsDouble();
    return true;
}

TextGraphicState& GraphicContentInterpreter::CurrentTextState() {
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
        if(it->second.hasFont) {
            CurrentTextState().fontRef = it->second.fontRef;
            CurrentTextState().fontSize = it->second.fontSize;
        }

        if(it->second.hasLineWidth) {
            CurrentGraphicState().lineWidth = it->second.lineWidth;
        }
    } // gstate will not be found if name is wrong, or that it didn't get collected cause didn't have interesting info for the task at hand
    return true;
}

void GraphicContentInterpreter::Tc(double inCharSpace) {
    CurrentTextState().charSpace = inCharSpace;
}

bool GraphicContentInterpreter::TcCommand(const PDFObjectVector& inOperands) {
    if(inOperands.size() < 1)
        return true; // too few params? ignore

    Tc(ParsedPrimitiveHelper(inOperands.back()).GetAsDouble());
    return true;
}

void GraphicContentInterpreter::Tw(double inWordSpace) {
    CurrentTextState().wordSpace = inWordSpace;
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

    CurrentTextState().scale = ParsedPrimitiveHelper(inOperands.back()).GetAsDouble();
    return true;
}

void GraphicContentInterpreter::TL(double inLeading) {
    CurrentTextState().leading = inLeading;
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

    CurrentTextState().rise = ParsedPrimitiveHelper(inOperands.back()).GetAsDouble();
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
            CurrentTextState().fontRef = it->second.fontRef;
        } // should i have a default font policy here?! 80-20 gal, 80-20.
    }
    CurrentTextState().fontSize = size;
    return true;
}

void GraphicContentInterpreter::StartTextElement() {
    isInTextElement = true;
    currentTextElementCommands.clear();
    textGraphicStateStack.clear();
    textGraphicStateStack.push_back(TextGraphicState(graphicStateStack.back().textGraphicState));
}


bool GraphicContentInterpreter::BTCommand() {
    StartTextElement();
    return true;
}

bool GraphicContentInterpreter::EndTextElement() {
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
    return handler->OnTextElementComplete(el);
}

bool GraphicContentInterpreter::ETCommand() {
    return EndTextElement();
}

void GraphicContentInterpreter::setTm(const double (&matrix)[6]) {
    TextGraphicState& state = CurrentTextState();

    CopyMatrix(matrix, state.tlm);
    CopyMatrix(matrix, state.tm);
    state.tmDirty = true;
    state.tlmDirty = true;
}


void GraphicContentInterpreter::Td(double inX, double inY) {
    double result[6];

    double tMatrix[6] = {1,0,0,1,inX,inY};

    MultiplyMatrix(tMatrix, CurrentTextState().tlm, result);
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
    Td(0,-CurrentTextState().leading);    
}

bool GraphicContentInterpreter::TStarCommand() {
    TStar();
    return true;
}

void GraphicContentInterpreter::RecordTextPlacement(const PlacedTextCommandArgument& inTextPlacementOperation) {
    PlacedTextCommandArgumentList placements;
    placements.push_back(inTextPlacementOperation);
    RecordTextPlacement(placements);
}

void GraphicContentInterpreter::RecordTextPlacement(const PlacedTextCommandArgumentList& inTextPlacementOperations) {
    PlacedTextCommand el = {
        inTextPlacementOperations,
        ContentGraphicState(CurrentGraphicState()),
        TextGraphicState(CurrentTextState())
    };
    currentTextElementCommands.push_back(el);
}

bool GraphicContentInterpreter::TjCommand(const PDFObjectVector& inOperands) {
    if(inOperands.size() < 1)
        return true; // too few params? ignore

    RecordTextPlacement(PlacedTextCommandArgument(ToBytesList(inOperands.back())));
    return true;
}

void GraphicContentInterpreter::Quote(PDFObject* inObject) {
    TStar();
    RecordTextPlacement(PlacedTextCommandArgument(ToBytesList(inObject)));        
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

    RecordTextPlacement(placements);
    return true;
}

void GraphicContentInterpreter::StartNewSubpathWithPoint(const PathPoint& inPoint) {
    SubPath newSubPath;

    newSubPath.components.push_back(PathComponent(inPoint));
    currentPath.subPaths.push_back(newSubPath);
}

bool GraphicContentInterpreter::mCommand(const PDFObjectVector& inOperands) {
    if(inOperands.size() < 2)
        return true; // too few params? ignore

    double x = ParsedPrimitiveHelper(inOperands[inOperands.size()-2]).GetAsDouble();
    double y =  ParsedPrimitiveHelper(inOperands.back()).GetAsDouble();

    StartNewSubpathWithPoint(PathPoint(x,y));

    return true;
}

bool GraphicContentInterpreter::NoCurrentPoint() {
    return currentPath.subPaths.size() == 0 || currentPath.subPaths.back().components.size() == 0;
}

bool GraphicContentInterpreter::AppendComponentToCurrentPath(const PathComponent& inComponent) {
    if(NoCurrentPoint())
        return true; // no current point, so cant append.

    // now it's only a question if the current subpath is closed, in which case we should start a new
    // subpath using the current point as first point and then add the new path component...or if it's
    // open in which case we can just append the new component to the current subpath

    SubPath& currentSubPath = currentPath.subPaths.back();

    if(currentSubPath.isClosed) {
        StartNewSubpathWithPoint(currentSubPath.components.back().to);
    }

    currentPath.subPaths.back().components.push_back(inComponent);

    return true;
 }

bool GraphicContentInterpreter::lCommand(const PDFObjectVector& inOperands) {
    if(inOperands.size() < 2)
        return true; // too few params? ignore

    double x = ParsedPrimitiveHelper(inOperands[inOperands.size()-2]).GetAsDouble();
    double y =  ParsedPrimitiveHelper(inOperands.back()).GetAsDouble();

    return AppendComponentToCurrentPath(PathComponent(PathPoint(x,y)));
}

bool GraphicContentInterpreter::cCommand(const PDFObjectVector& inOperands) {
    if(inOperands.size() < 6)
        return true; // too few params? ignore

    PathPoint control1(ParsedPrimitiveHelper(inOperands[0]).GetAsDouble(), ParsedPrimitiveHelper(inOperands[1]).GetAsDouble());
    PathPoint control2(ParsedPrimitiveHelper(inOperands[2]).GetAsDouble(), ParsedPrimitiveHelper(inOperands[3]).GetAsDouble());
    PathPoint to(ParsedPrimitiveHelper(inOperands[4]).GetAsDouble(), ParsedPrimitiveHelper(inOperands[5]).GetAsDouble());

    return AppendComponentToCurrentPath(PathComponent(to, control1, control2));
}

bool GraphicContentInterpreter::vCommand(const PDFObjectVector& inOperands) {
    if(inOperands.size() < 4)
        return true; // too few params? ignore

    if(NoCurrentPoint())
        return true; // no current point, and its supposed to be used as a control point

    PathPoint control1(currentPath.subPaths.back().components.back().to);
    PathPoint control2(ParsedPrimitiveHelper(inOperands[0]).GetAsDouble(), ParsedPrimitiveHelper(inOperands[1]).GetAsDouble());
    PathPoint to(ParsedPrimitiveHelper(inOperands[2]).GetAsDouble(), ParsedPrimitiveHelper(inOperands[3]).GetAsDouble());

    return AppendComponentToCurrentPath(PathComponent(to, control1, control2));
}

bool GraphicContentInterpreter::yCommand(const PDFObjectVector& inOperands) {
    if(inOperands.size() < 4)
        return true; // too few params? ignore

    PathPoint control1(ParsedPrimitiveHelper(inOperands[0]).GetAsDouble(), ParsedPrimitiveHelper(inOperands[1]).GetAsDouble());
    PathPoint control2(ParsedPrimitiveHelper(inOperands[2]).GetAsDouble(), ParsedPrimitiveHelper(inOperands[3]).GetAsDouble());
    PathPoint to(control2);

    return AppendComponentToCurrentPath(PathComponent(to, control1, control2));
}

bool GraphicContentInterpreter::CloseCurrentPath() {
    if(NoCurrentPoint())
        return true; // no points in current subpath, so nothing to tie back to, skip

    SubPath& currentSubPath = currentPath.subPaths.back();

    if(currentSubPath.isClosed)
        return true; // subpath already closed...so nothing more to do here

    // explictly push the first point as last point and mark path as closed.
    currentSubPath.components.push_back(PathComponent(*currentSubPath.components.begin()));
    currentSubPath.isClosed = true;

    return true;
}

void GraphicContentInterpreter::CloseAllSubPaths() {
    SubPathList::iterator it = currentPath.subPaths.begin();

    for(; it != currentPath.subPaths.end(); ++it) {
        SubPath& currentSubPath = *it;

        if(currentSubPath.isClosed)
            continue; // subpath already closed...so nothing more to do here

        // explictly push the first point as last point and mark path as closed.
        currentSubPath.components.push_back(PathComponent(*currentSubPath.components.begin()));
        currentSubPath.isClosed = true;

    }
} 

bool GraphicContentInterpreter::hCommand(const PDFObjectVector& inOperands) {
    return CloseCurrentPath();
}

bool GraphicContentInterpreter::reCommand(const PDFObjectVector& inOperands) {
    if(inOperands.size() < 4)
        return true; // too few params? ignore

    double x = ParsedPrimitiveHelper(inOperands[0]).GetAsDouble();
    double y =  ParsedPrimitiveHelper(inOperands[1]).GetAsDouble();
    double width = ParsedPrimitiveHelper(inOperands[2]).GetAsDouble();
    double height =  ParsedPrimitiveHelper(inOperands[3]).GetAsDouble();

    SubPath newSubPath;

    newSubPath.components.push_back(PathComponent(PathPoint(x,y))); // x y m
    newSubPath.components.push_back(PathComponent(PathPoint(x+width,y))); // (x+width) y l
    newSubPath.components.push_back(PathComponent(PathPoint(x+width,y+height))); // (x+width) (y+height) l
    newSubPath.components.push_back(PathComponent(PathPoint(x,y+height))); // x (y+height) l
    // h
    newSubPath.components.push_back(PathComponent(PathPoint(x,y)));
    newSubPath.isClosed = true;

    currentPath.subPaths.push_back(newSubPath);

    return true;
}

bool GraphicContentInterpreter::PaintCurrentPath(bool inShouldStroke, bool inShouldFill, EFillMethod inFillMethod) {
     if(NoCurrentPoint()) // no path, ignore
        return true;

    PathElement pathElement = {
        Path(currentPath),
        ContentGraphicState(CurrentGraphicState()),
        inShouldStroke,
        inShouldFill,
        inFillMethod
    };

    ClearCurrentPath();

    return handler->OnPathPainted(pathElement);   
}

bool GraphicContentInterpreter::SCommand(const PDFObjectVector& inOperands) {
    return PaintCurrentPath(
        true,
        false,
        eFillMethodNonZeroWindingNumberRule // just a dummy
    );
}

bool GraphicContentInterpreter::sCommand(const PDFObjectVector& inOperands) {
    return CloseCurrentPath() && SCommand(inOperands);
}

bool GraphicContentInterpreter::fCommand(const PDFObjectVector& inOperands) {
    CloseAllSubPaths();

    return PaintCurrentPath(
        false,
        true,
        eFillMethodNonZeroWindingNumberRule
    );
}

bool GraphicContentInterpreter::fStarCommand(const PDFObjectVector& inOperands) {
    return PaintCurrentPath(
        false,
        true,
        eFillMethodEventOddRule
    );
}

bool GraphicContentInterpreter::BCommand(const PDFObjectVector& inOperands) {
    CloseAllSubPaths();

    return PaintCurrentPath(
        true,
        true,
        eFillMethodNonZeroWindingNumberRule
    );
}

bool GraphicContentInterpreter::BStarCommand(const PDFObjectVector& inOperands) {
    return PaintCurrentPath(
        true,
        true,
        eFillMethodEventOddRule
    );
}

bool GraphicContentInterpreter::bCommand(const PDFObjectVector& inOperands) {
    return CloseCurrentPath() && BCommand(inOperands);
}

bool GraphicContentInterpreter::bStarCommand(const PDFObjectVector& inOperands) {
    return CloseCurrentPath() && BStarCommand(inOperands);
}

bool GraphicContentInterpreter::nCommand(const PDFObjectVector& inOperands) {
    ClearCurrentPath();
    return true;
}

bool GraphicContentInterpreter::OnResourcesRead(IInterpreterContext* inContext) {
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
                RefCountPtr<PDFObject> lineWidthDesc = inContext->GetParser()->QueryDictionaryObject(gsAsDict, "LW");

                if(!!fontDesc || !!lineWidthDesc) {
                    GSState gState;

                    if(!!fontDesc) {
                        RefCountPtr<PDFObject> fontRef = fontDesc->QueryObject(0);
                        RefCountPtr<PDFObject> size = fontDesc->QueryObject(1);
                        double fontSize = ParsedPrimitiveHelper(size.GetPtr()).GetAsDouble();
                        gState.fontRef = fontRef;
                        gState.fontSize = fontSize;
                        gState.hasFont = true;
                    }

                    if(!!lineWidthDesc) {
                        double lineWidth = ParsedPrimitiveHelper(lineWidthDesc.GetPtr()).GetAsDouble();
                        gState.lineWidth = lineWidth;
                        gState.hasLineWidth = true;
                    }

                    currentResources.gStates.insert(StringToGStateMap::value_type(it.GetKey()->GetValue(), gState));
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

    return handler->OnResourcesRead(currentResources, inContext);
}

bool GraphicContentInterpreter::OnXObjectDoStart(
        const std::string& inXObjectRefName,
        ObjectIDType inXObjectObjectID,
        PDFStreamInput* inXObject,
        PDFParser* inParser) {
    // the equivalent of q, so any internal transformations do not effect the outside. specifically what im gonna
    // do now to emulate form placement matrix changes
    PushGraphicState();

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

void GraphicContentInterpreter::OnXObjectDoEnd(
    const std::string& inXObjectRefName,
    ObjectIDType inXObjectObjectID,
    PDFStreamInput* inXObject,
    PDFParser* inParser) {

    // pop resources stack (was placed on resources read, which comes right when you start reading the form)
    resourcesStack.pop_back();        

    // the equivalent of Q removing all artifacts of the form state changes
    PopGraphicState();

}