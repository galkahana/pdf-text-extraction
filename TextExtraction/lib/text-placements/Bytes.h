#include "IOBasicTypes.h"

#include <list>

typedef std::list<IOBasicTypes::Byte> ByteList;
class PDFObject;


ByteList ToBytesList(PDFObject* inObject);