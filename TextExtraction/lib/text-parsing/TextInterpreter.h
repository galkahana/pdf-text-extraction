#pragma once

#include "../graphic-content-parsing/TextElement.h"
#include "../graphic-content-parsing/Resources.h"

#include "ITextInterpreterHandler.h"

#include "ObjectsBasicTypes.h"
#include "RefCountPtr.h"

class FontDecoder;
class PDFObject;

#include <map>

class IInterpreterContext;

struct LessRefCountPDFObject {
    bool operator()( const RefCountPtr<PDFObject>& lhs, const RefCountPtr<PDFObject>& rhs ) const {
        return lhs.GetPtr() < rhs.GetPtr();
    }
};  

typedef std::map<ObjectIDType, FontDecoder> ObjectIDTypeToFontDecoderMap;
typedef std::map<RefCountPtr<PDFObject>, FontDecoder,  LessRefCountPDFObject> PDFObjectToFontDecoderMap;

class TextInterpeter {
    public:
        TextInterpeter(void);
        TextInterpeter(ITextInterpreterHandler* inHandler);
        virtual ~TextInterpeter(void);


        void SetHandler(ITextInterpreterHandler* inHandler);

        // forwarded by external party implementing IGraphicContentInterpreterHandler
        // with only what's relevant to text
        bool OnTextElementComplete(const TextElement& inTextElement);
        bool OnResourcesRead(const Resources& inResources, IInterpreterContext* inContext);

        void ResetInterpretationState();
    private:
        ITextInterpreterHandler* handler;

        // font decoders parsed data
        ObjectIDTypeToFontDecoderMap refrencedFontDecoders;
        PDFObjectToFontDecoderMap embeddedFontDecoders;
        
        FontDecoder* GetDecoderForFont(PDFObject* inFontReference);     

};
