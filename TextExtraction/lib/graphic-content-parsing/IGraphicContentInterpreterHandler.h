#pragma once

#include "TextElement.h"
#include "Resources.h"

class IInterpreterContext;

class IGraphicContentInterpreterHandler 
{
public:

    // called for each text element on finish with the collected text element
    virtual bool onTextElementComplete(const TextElement& inTextElement) = 0;

    // gets called for and interprested page or an xobject that gets drawn during this page. will provide
    // chance for the handler to safely read resources and do some parsing in advance to support application 
    // requirements while getting graphic content later. In addition to just forwardig inContext from
    // the underlying PDFRecursiveInterpreter instance, the methdo also accepts inResources which are the resources
    // parsed by the GraphicContentInterpreter, to allow sharing. Specifically TextElements text states will contain fontRefs that
    // that are pointing to the same font objects held by inResources. This allows for a later matching to happen for 
    // any additional data per the underlying font object pointer.
    virtual bool onResourcesRead(const Resources& inResources, IInterpreterContext* inContext){return true;}

    // gets called when interpretation of the element (page for now) provided to GraphicContentInterpreter is finished, allow a respective state release
    virtual void onDone(){}

};