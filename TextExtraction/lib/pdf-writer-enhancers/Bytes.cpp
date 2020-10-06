#include "Bytes.h"

#include "PDFObject.h"
#include "PDFLiteralString.h"
#include "PDFHexString.h"

using namespace std;

ByteList ToBytesList(PDFObject* inObject) {
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
        default: {
            // nothing
        }
    }

    return result;  
}