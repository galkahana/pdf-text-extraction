#include "Bytes.h"

#include "PDFObject.h"
#include "PDFLiteralString.h"
#include "PDFHexString.h"

using namespace std;

ByteList ToBytesList(PDFObject* inObject) {
    switch(inObject->GetType())
    {
        case PDFObject::ePDFObjectLiteralString: {
            return stringToByteList(((PDFLiteralString*)inObject)->GetValue());
            break;
        }
        case PDFObject::ePDFObjectHexString: {
            return stringToByteList(((PDFHexString*)inObject)->GetValue());
            break;
        }
        default: {
            // nothing
            return ByteList();
        }
    }

}