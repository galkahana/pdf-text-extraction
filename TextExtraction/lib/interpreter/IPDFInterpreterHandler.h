#pragma once

#include <vector>
#include <string>

class PDFObject;

typedef std::vector<PDFObject*> PDFObjectVector; 


class IPDFInterpreterHandler 
{
public:

    // return boolean marks whether to continue or not (true or false)
	virtual bool onOperation(const std::string& inOperation,  const PDFObjectVector& inOperands) = 0;
};