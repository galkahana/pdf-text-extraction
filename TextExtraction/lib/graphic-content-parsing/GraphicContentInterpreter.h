#pragma once

#include "../interpreter/IPDFRecursiveInterpreterHandler.h"

#include "IGraphicContentInterpreterHandler.h"
#include "ContentGraphicState.h"
#include "TextGraphicState.h"
#include "Resources.h"
#include "TextElement.h"
#include "Path.h"
#include "PathElement.h"

#include <list>
#include <map>

typedef std::list<TextGraphicState> TextGraphicStateList;
typedef std::list<ContentGraphicState> GraphicStateList;
typedef std::list<Resources> ResourcesList;


class GraphicContentInterpreter: public IPDFRecursiveInterpreterHandler {
public:
    GraphicContentInterpreter(void);
    virtual ~GraphicContentInterpreter(void);

    // interpret 
    bool InterpretPageContents(
        PDFParser* inParser,
        PDFDictionary* inPage,
        IGraphicContentInterpreterHandler* inHandler);


    // IPDFRecursiveInterpreterHandler implementation
    virtual bool OnOperation(const std::string& inOperation,  const PDFObjectVector& inOperands, IInterpreterContext* inContext);

    virtual bool OnResourcesRead(IInterpreterContext* inContext);
    virtual bool OnXObjectDoStart(
        const std::string& inXObjectRefName,
        ObjectIDType inXObjectObjectID,
        PDFStreamInput* inXObject,
        PDFParser* inParser);

    virtual void OnXObjectDoEnd(
        const std::string& inXObjectRefName,
        ObjectIDType inXObjectObjectID,
        PDFStreamInput* inXObject,
        PDFParser* inParser);        

private:
    ResourcesList resourcesStack;
    GraphicStateList graphicStateStack;
    TextGraphicStateList textGraphicStateStack;
    Path currentPath;

    bool isInTextElement;
    PlacedTextCommandList currentTextElementCommands;

    IGraphicContentInterpreterHandler* handler;

    void InitInterpretationState();
    void ResetInterpretationState();


    // interpreted commands
    bool qCommand();
    bool QCommand();
    bool cmCommand(const PDFObjectVector& inOperands);
    bool wCommand(const PDFObjectVector& inOperands);
    bool gsCommand(const PDFObjectVector& inOperands);
    bool TcCommand(const PDFObjectVector& inOperands);
    bool TwCommand(const PDFObjectVector& inOperands);
    bool TzCommand(const PDFObjectVector& inOperands);
    bool TLCommand(const PDFObjectVector& inOperands);
    bool TsCommand(const PDFObjectVector& inOperands);
    bool TfCommand(const PDFObjectVector& inOperands);
    bool BTCommand();
    bool ETCommand();
    bool TdCommand(const PDFObjectVector& inOperands);
    bool TDCommand(const PDFObjectVector& inOperands);
    bool TmCommand(const PDFObjectVector& inOperands);
    bool TStarCommand();
    bool TjCommand(const PDFObjectVector& inOperands);
    bool QuoteCommand(const PDFObjectVector& inOperands);
    bool DoubleQuoteCommand(const PDFObjectVector& inOperands);
    bool TJCommand(const PDFObjectVector& inOperands);
    bool mCommand(const PDFObjectVector& inOperands);
    bool lCommand(const PDFObjectVector& inOperands);
    bool cCommand(const PDFObjectVector& inOperands);
    bool vCommand(const PDFObjectVector& inOperands);
    bool yCommand(const PDFObjectVector& inOperands);
    bool hCommand(const PDFObjectVector& inOperands);
    bool reCommand(const PDFObjectVector& inOperands);
    bool SCommand(const PDFObjectVector& inOperands);
    bool sCommand(const PDFObjectVector& inOperands);
    bool fCommand(const PDFObjectVector& inOperands);
    bool fStarCommand(const PDFObjectVector& inOperands);
    bool BCommand(const PDFObjectVector& inOperands);
    bool BStarCommand(const PDFObjectVector& inOperands);
    bool bCommand(const PDFObjectVector& inOperands);
    bool bStarCommand(const PDFObjectVector& inOperands);
    bool nCommand(const PDFObjectVector& inOperands);

    void PushGraphicState();
    void PopGraphicState();
    ContentGraphicState& CurrentGraphicState();

    TextGraphicState& CurrentTextState();

    void ClearCurrentPath();
    void StartNewSubpathWithPoint(const PathPoint& inPoint);
    bool AppendComponentToCurrentPath(const PathComponent& inComponent);
    bool CloseCurrentPath();
    bool NoCurrentPoint();
    void CloseAllSubPaths();

    void cm(const double (&matrix)[6]);
    void Tc(double inCharSpace);
    void Tw(double inWordSpace);
    void TL(double inLeading);
    void Td(double inX, double inY);
    void setTm(const double (&matrix)[6]);
    void TStar();
    void Quote(PDFObject* inObject);

    void StartTextElement();
    bool EndTextElement();

    void RecordTextPlacement(const PlacedTextCommandArgument& inTextPlacementOperation);
    void RecordTextPlacement(const PlacedTextCommandArgumentVector& inTextPlacementOperations);

    bool PaintCurrentPath(bool inShouldStroke, bool inShouldFill, EFillMethod inFillMethod);
};