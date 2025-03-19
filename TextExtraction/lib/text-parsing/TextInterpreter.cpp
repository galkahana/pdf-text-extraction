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

static const string scSpace = " ";

TextInterpeter::TextInterpeter(void) {
    SetHandler(NULL);
}

TextInterpeter::TextInterpeter(ITextInterpreterHandler* inHandler) {
    SetHandler(inHandler);
}


TextInterpeter::~TextInterpeter(void) {
    ResetInterpretationState();
}

void TextInterpeter::ResetInterpretationState() {
    refrencedFontDecoders.clear();
    embeddedFontDecoders.clear();
}

FontDecoder* TextInterpeter::GetDecoderForFont(PDFObject* inFontReference) {
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

bool TextInterpeter::OnTextElementComplete(const TextElement& inTextElement) {
    if(!handler)
        return true;

    bool shouldContinue = true;
    PlacedTextCommandList::const_iterator commandIt = inTextElement.texts.begin();
    double matrixBuffer[6];
    

    bool hasDefaultTm = false;
    double nextPlacementDefaultTm[6] = {1,0,0,1,0,0}; // variable used to store a default matrix accounting for glyph dispositions
    for(; commandIt != inTextElement.texts.end() && shouldContinue; ++commandIt) {
        const PlacedTextCommand& item = *commandIt;

        // local matrix for this item. will be used to determine global box out of item local dimensions
        double itemTextStateTm[6];

        // choose the matrix affecting this item placement. If matrix changing operators were used in the state then it will be the state matrix,
        // otherwise the new items matrix is just what was accumulated by accounting for glyph dispositions
        if(!item.textState.tmDirty && hasDefaultTm)
            CopyMatrix(nextPlacementDefaultTm, itemTextStateTm);
        else
            CopyMatrix(item.textState.tm, itemTextStateTm);

        // Determine a decoder for the text font
        FontDecoder* decoder = GetDecoderForFont(item.textState.fontRef.GetPtr());
        if(!decoder)
            continue;

        CopyMatrix(itemTextStateTm, nextPlacementDefaultTm);
        hasDefaultTm = true;
        double descentPlacement = (decoder->descent + item.textState.rise)*item.textState.fontSize/1000;
        double ascentPlacement = (decoder->ascent + item.textState.rise)*item.textState.fontSize/1000;
        double spaceWidth = (decoder->spaceWidth*item.textState.fontSize + item.textState.charSpace + item.textState.wordSpace)*item.textState.scale/100; 

        PlacedTextCommandArgumentList::const_iterator argumentIt = item.text.begin();
        for(;argumentIt != item.text.end() && shouldContinue;++argumentIt) {
            if(argumentIt->isText) {
                // compute text argument
                double accumulatedDisplacement = 0;
                double minPlacement = 0;
                double maxPlacement = 0;

                // Translate the text and accumulate
                FontDecoderResult result = decoder->Translate(argumentIt->bytes);


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
                    MultiplyMatrix(txMatrix, nextPlacementDefaultTm, matrixBuffer);
                    CopyMatrix(matrixBuffer,nextPlacementDefaultTm);
                }

                // prepare and report this text as text placement
                double localBBox[4] = {minPlacement, descentPlacement, maxPlacement, ascentPlacement};
                double globalBBox[4];
                double globalWidthVector[2];
                double widthVector[2] = {spaceWidth,0};
                double zeroVector[2] = {0,0};
                double transformedWidthVector[2];
                double transformedZeroVector[2];
                
                MultiplyMatrix(itemTextStateTm,item.graphicState.ctm, matrixBuffer);
                TransformBox(localBBox, matrixBuffer, globalBBox);

                TransformVector(widthVector, matrixBuffer, transformedWidthVector);
                TransformVector(zeroVector, matrixBuffer, transformedZeroVector);
                globalWidthVector[0] = abs(transformedWidthVector[0] - transformedZeroVector[0]);
                globalWidthVector[1] = abs(transformedWidthVector[1] - transformedZeroVector[1]);


                ParsedTextPlacement placement(
                        result.asText,
                        matrixBuffer,
                        localBBox,
                        globalBBox,
                        spaceWidth,
                        globalWidthVector

                );

                shouldContinue = handler->OnParsedTextPlacementComplete(placement);
            } else {
                // compute displacements argument effect on position/matrix
                double tx = ((-argumentIt->pos/1000)*item.textState.fontSize)*item.textState.scale/100;
                double txMatrix[6] = {1,0,0,1,tx,0};  
                MultiplyMatrix(txMatrix, nextPlacementDefaultTm, matrixBuffer);
                CopyMatrix(matrixBuffer,nextPlacementDefaultTm);
            }

            // for next placements within this item, the new matrix is the accumulated disposition matrix
            CopyMatrix(nextPlacementDefaultTm, itemTextStateTm);
        }
    }

    return shouldContinue;

}



bool TextInterpeter::OnResourcesRead(const Resources& inResources, IInterpreterContext* inContext) {
    // this is used to parse font references in advance and convert them to "Decoders". decoders are later
    // used to both translate and compute dimensions of texts, as the text gets intepreted
    StringToFontMap::const_iterator it = inResources.fonts.begin();
    for(; it != inResources.fonts.end(); ++it) {
        // 

        if(it->second.fontRef.GetPtr()->GetType() == PDFObject::ePDFObjectDictionary) {
            RefCountPtr<PDFObject> fontDict = it->second.fontRef.GetPtr();
            // embedded, check cache first
            PDFObjectToFontDecoderMap::const_iterator itFont = embeddedFontDecoders.find(fontDict);
            if(itFont == embeddedFontDecoders.end()) {
                // ok. there's none, use this chance to create a new one
                embeddedFontDecoders.insert(PDFObjectToFontDecoderMap::value_type(fontDict, FontDecoder(inContext->GetParser(), (PDFDictionary*)fontDict.GetPtr())));
            }
        }
        else if(it->second.fontRef.GetPtr()->GetType() == PDFObject::ePDFObjectIndirectObjectReference) {
            ObjectIDType id = ((PDFIndirectObjectReference*)(it->second.fontRef.GetPtr()))->mObjectID;
            ObjectIDTypeToFontDecoderMap::const_iterator itFont = refrencedFontDecoders.find(id);
            if(itFont == refrencedFontDecoders.end()) {
                PDFObjectCastPtr<PDFDictionary> fontDict = inContext->GetParser()->ParseNewObject(id);
                if(!fontDict)
                    continue; // ignore
                refrencedFontDecoders.insert(ObjectIDTypeToFontDecoderMap::value_type(id, FontDecoder(inContext->GetParser(), fontDict.GetPtr())));
            }        
        }
    }

    return true;
}


void TextInterpeter::SetHandler(ITextInterpreterHandler* inHandler) {
    handler = inHandler;
}