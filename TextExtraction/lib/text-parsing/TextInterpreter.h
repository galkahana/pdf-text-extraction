#pragma once

#include "../graphic-content-parsing/IGraphicContentInterpreterHandler.h"
#include "ITextInterpreterHandler.h"

#include "ObjectsBasicTypes.h"
#include "RefCountPtr.h"

class FontDecoder;
class PDFObject;

#include <map>

struct LessRefCountPDFObject {
    bool operator()( const RefCountPtr<PDFObject>& lhs, const RefCountPtr<PDFObject>& rhs ) const {
        return lhs.GetPtr() < rhs.GetPtr();
    }
};  

typedef std::map<ObjectIDType, FontDecoder> ObjectIDTypeToFontDecoderMap;
typedef std::map<RefCountPtr<PDFObject>, FontDecoder,  LessRefCountPDFObject> PDFObjectToFontDecoderMap;

class TextInterpeter: public IGraphicContentInterpreterHandler {
    public:
        TextInterpeter(void);
        TextInterpeter(ITextInterpreterHandler* inHandler);
        virtual ~TextInterpeter(void);


        void setHandler(ITextInterpreterHandler* inHandler);

        // IGraphicContentInterpreterHandler implementation
        virtual bool onTextElementComplete(const TextElement& inTextElement);
        virtual bool onResourcesRead(const Resources& inResources, IInterpreterContext* inContext);

    private:
        ITextInterpreterHandler* handler;

        // font decoders parsed data
        ObjectIDTypeToFontDecoderMap refrencedFontDecoders;
        PDFObjectToFontDecoderMap embeddedFontDecoders;
        
        FontDecoder* getDecoderForFont(PDFObject* inFontReference);     
        void resetInterpretationState();

};
