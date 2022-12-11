#include "TextInterpreter.h"

#include "../graphic-content-parsing/Resources.h"
#include "../interpreter/IPDFRecursiveInterpreterHandler.h"
#include "../font-translation/FontDecoder.h"

#include "PDFObject.h"
#include "RefCountPtr.h"
#include "PDFDictionary.h"
#include "PDFIndirectObjectReference.h"
#include "PDFObjectCast.h"
#include "PDFParser.h"


#include <sstream>

using namespace std;

TextInterpeter::TextInterpeter(void) {
    setHandler(NULL);
}

TextInterpeter::TextInterpeter(ITextInterpreterHandler* inHandler) {
    setHandler(inHandler);
}


TextInterpeter::~TextInterpeter(void) {
    resetInterpretationState();
}

void TextInterpeter::resetInterpretationState() {
    refrencedFontDecoders.clear();
    embeddedFontDecoders.clear();
}

FontDecoder* TextInterpeter::getDecoderForFont(PDFObject* inFontReference) {
    if(!inFontReference)
        return NULL;

    // This should normally end up with a proper decoder, otherwise there wouldn't be a ref at all.
    // so the "null returns" below should imply an earlier failure to parse a certain font
    if(inFontReference->GetType() == PDFObject::ePDFObjectDictionary) {
        PDFObjectToFontDecoderMap::iterator it = embeddedFontDecoders.find(inFontReference);
        return it == embeddedFontDecoders.end() ? NULL : &(it->second);
    }
    else if(inFontReference->GetType() == PDFObject::ePDFObjectIndirectObjectReference) {
        ObjectIDType id = ((PDFIndirectObjectReference*)(inFontReference))->mObjectID;
        ObjectIDTypeToFontDecoderMap::iterator it = refrencedFontDecoders.find(id);
        return it == refrencedFontDecoders.end() ? NULL : &(it->second);
    }
    return NULL;
}

bool TextInterpeter::onTextElementComplete(const TextElement& inTextElement) {
    if(!handler)
        return true;

    bool shouldContinue = true;
    PlacedTextCommandList::const_iterator commandIt = inTextElement.texts.begin();
    double matrixBuffer[6];
    

    bool hasDefaultTm = false;
    double nextPlacementDefaultTm[6] = {1,0,0,1,0,0};
    for(; commandIt != inTextElement.texts.end() && shouldContinue; ++commandIt) {
        stringstream textBuffer;
        const PlacedTextCommand& item = *commandIt;
    
        // Determine a decoder for the text font
        FontDecoder* decoder = getDecoderForFont(item.textState.fontRef.GetPtr());
        if(!decoder)
            continue;

        double accumulatedDisplacement = 0;
        double minPlacement = 0;
        double maxPlacement = 0;
        copyMatrix(item.textState.tm, nextPlacementDefaultTm);
        hasDefaultTm = true;


        PlacedTextCommandArgumentList::const_iterator argumentIt = item.text.begin();
        for(;argumentIt != item.text.end() && shouldContinue;++argumentIt) {
            if(argumentIt->isText) {
                // compute text argument

                // Translate the text and accumulate
                FontDecoderResult result = decoder->Translate(argumentIt->bytes);
                textBuffer<<(result.asText.empty() ? string(" ") : result.asText);


                // Compute the text dimensions and position/matrix
                DispositionResultList dispositions = decoder->ComputeDisplacements(argumentIt->bytes);
                DispositionResultList::iterator itDispositions = dispositions.begin();
                for(; itDispositions != dispositions.end(); ++itDispositions) {
                    double displacement = itDispositions->width;
                    unsigned long charCode = itDispositions->code;
                    double tx = (displacement*item.textState.fontSize + item.textState.charSpace + (charCode == 32 ? item.textState.wordSpace:0))*item.textState.scale/100; 
                    accumulatedDisplacement+=tx;
                    if(accumulatedDisplacement<minPlacement)
                        minPlacement = accumulatedDisplacement;
                    if(accumulatedDisplacement>maxPlacement)
                        maxPlacement = accumulatedDisplacement;
                    double txMatrix[6] = {1,0,0,1,tx,0};  
                    multiplyMatrix(txMatrix, nextPlacementDefaultTm, matrixBuffer);
                    copyMatrix(matrixBuffer,nextPlacementDefaultTm);
                }

            } else {
                // compute displacements argument effect on position/matrix

                double tx = ((-argumentIt->pos/1000)*item.textState.fontSize)*item.textState.scale/100;
                accumulatedDisplacement+=tx;
                if(accumulatedDisplacement<minPlacement)
                    minPlacement = accumulatedDisplacement;
                if(accumulatedDisplacement>maxPlacement)
                    maxPlacement = accumulatedDisplacement;
                double txMatrix[6] = {1,0,0,1,tx,0};  
                multiplyMatrix(txMatrix, nextPlacementDefaultTm, matrixBuffer);
                copyMatrix(matrixBuffer,nextPlacementDefaultTm);
            }
        }

        double descentPlacement = (decoder->descent + item.textState.rise)*item.textState.fontSize/1000;
        double ascentPlacement = (decoder->ascent + item.textState.rise)*item.textState.fontSize/1000;
        double localBBox[4] = {minPlacement, descentPlacement, maxPlacement, ascentPlacement};
        double spaceWidth = decoder->spaceWidth*item.textState.fontSize*item.textState.scale/100;
        string text = textBuffer.str();
        double globalBBox[4];
        
        multiplyMatrix(item.textState.tm,item.graphicState.ctm, matrixBuffer);
        transformBox(localBBox, matrixBuffer, globalBBox);

        ParsedTextPlacement placement(
                text,
                matrixBuffer,
                localBBox,
                globalBBox,
                spaceWidth

        );

        shouldContinue = handler->onParsedTextPlacementComplete(placement);
    }

    return shouldContinue;

}



bool TextInterpeter::onResourcesRead(const Resources& inResources, IInterpreterContext* inContext) {
    // this is used to parse font references in advance and convert them to "Decoders". decoders are later
    // used to both translate and compute dimensions of texts, as the text gets intepreted
    StringToFontMap::const_iterator it = inResources.fonts.begin();
    for(; it != inResources.fonts.end(); ++it) {
        // 

        if(it->second.fontRef.GetPtr()->GetType() == PDFObject::ePDFObjectDictionary) {
            RefCountPtr<PDFObject> fontDict = it->second.fontRef.GetPtr();
            // embedded, check cache first
            PDFObjectToFontDecoderMap::iterator it = embeddedFontDecoders.find(fontDict);
            if(it == embeddedFontDecoders.end()) {
                // ok. there's none, use this chance to create a new one
                embeddedFontDecoders.insert(PDFObjectToFontDecoderMap::value_type(fontDict, FontDecoder(inContext->GetParser(), (PDFDictionary*)fontDict.GetPtr())));
            }
        }
        else if(it->second.fontRef.GetPtr()->GetType() == PDFObject::ePDFObjectIndirectObjectReference) {
            ObjectIDType id = ((PDFIndirectObjectReference*)(it->second.fontRef.GetPtr()))->mObjectID;
            ObjectIDTypeToFontDecoderMap::iterator it = refrencedFontDecoders.find(id);
            if(it == refrencedFontDecoders.end()) {
                PDFObjectCastPtr<PDFDictionary> fontDict = inContext->GetParser()->ParseNewObject(id);
                if(!fontDict)
                    continue; // ignore
                refrencedFontDecoders.insert(ObjectIDTypeToFontDecoderMap::value_type(id, FontDecoder(inContext->GetParser(), fontDict.GetPtr())));
            }        
        }
    }

    return true;
}


void TextInterpeter::setHandler(ITextInterpreterHandler* inHandler) {
    handler = inHandler;
}