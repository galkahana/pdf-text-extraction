#pragma once

#include "ObjectsBasicTypes.h"

#include <vector>
#include <string>


class PDFObject;
class PDFStreamInput;
class PDFParser;

typedef std::vector<PDFObject*> PDFObjectVector; 


/**
 * This interpreter will recurse into forms contents on "Do" operations. 
 * The Do operation will still call to onOperation when starting the xobject operation.
 **/

class IPDFRecursiveInterpreterHandler 
{
public:

    // return boolean marks whether to continue or not (true or false)
	virtual bool onOperation(const std::string& inOperation,  const PDFObjectVector& inOperands) = 0;

    // recursion to xobject start (optional)
    virtual bool onXObjectDoStart(
        const std::string& inXObjectRefName,
        ObjectIDType inXObjectObjectID,
        PDFStreamInput* inXObject,
        PDFParser* inParser) {return true;}

    // recursion to xobject end (optional)
    virtual void onXObjectDoEnd(
        const std::string& inXObjectRefName,
        ObjectIDType inXObjectObjectID,
        PDFStreamInput* inXObject,
        PDFParser* inParser) {}

};