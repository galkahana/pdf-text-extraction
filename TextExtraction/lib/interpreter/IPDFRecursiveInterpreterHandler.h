#pragma once

#include "ObjectsBasicTypes.h"

#include <vector>
#include <string>
#include <list>


class PDFObject;
class PDFStreamInput;
class PDFParser;
class PDFDictionary;
class PDFObjectParser;

typedef std::vector<PDFObject*> PDFObjectVector;
typedef std::list<std::string> StringList;

class IInterpreterContext {
    public:

    // Use GetParser, FindResourceCategory and FindResource Responsibly, only while in "onResourcesRead" and especially not while
    // the content stream is being intrepreted....otherwise the reading will be harmed.
    // that's why it'd be good practice to read what resources you might need for later interpretation...in advance.
    virtual PDFParser* GetParser() = 0;
    virtual PDFDictionary* FindResourceCategory(const std::string& inResourceCategory) = 0;
    virtual PDFObject* FindResource(const std::string& inResourceName, const std::string& inResourceCategory) = 0;

    // GetObjectParser fetches you the object parser the interpreter is using to read operators and operands.
    // You can use this guy  while interpretation. no worries. even read ahead...
    // this is good for cases where you want to read operators/operands in advance or even read ahead in the stream.
    // note that parser will become available only once intepretation starts!
    virtual PDFObjectParser* GetObjectParser() =0;
};


/**
 * This interpreter will recurse into forms contents on "Do" operations. 
 * The Do operation will still call to onOperation when starting the xobject operation.
 **/

class IPDFRecursiveInterpreterHandler 
{
public:

    // required!

    // return boolean marks whether to continue or not (true or false)
	virtual bool onOperation(const std::string& inOperation,  const PDFObjectVector& inOperands, IInterpreterContext* inContext) = 0;


    // Optional helpers

    // going to recurse into a form. allows to adapt current matrix n such if you are drawing,
    // as well as skip this form, if you already got cached result.
    // use result to tell it to skip this form. true for continue with this form recursion, false for skip this
    virtual bool onXObjectDoStart(
        const std::string& inXObjectRefName,
        ObjectIDType inXObjectObjectID,
        PDFStreamInput* inXObject,
        PDFParser* inParser) {return true;}

    // ended form recursion. this is a good place to cache the form reuslts if you want to reuse them
    // when the form objectid comes up next on start
    virtual void onXObjectDoEnd(
        const std::string& inXObjectRefName,
        ObjectIDType inXObjectObjectID,
        PDFStreamInput* inXObject,
        PDFParser* inParser) {}

    // prior to starting content parsing, use this chance to read resources
    // that are important to the task you're implementing.
    // onResourcesRead allows access to IInterpreterContext which in turn can FindResources.
    // this method is called both at top level and when recursing to forms.
    // you can use onEnd and onXObjectEnd to release any resources read for that level
    // bool allows you to stop interpretation, like onOperation return result
    virtual bool onResourcesRead(IInterpreterContext* inContext){return true;}

    // Inline images are not normal operator/operands sequance in a content stream.
    // implementing this method allows you to instruct the interpreter to skip them.
    // this should normally be the case unless you have the intention of reading them yourself
    virtual bool ShouldSkipInlineImage() {return true;}
};