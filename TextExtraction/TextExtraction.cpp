#include "TextExtraction.h"
#include "InputFile.h"
#include "PDFParser.h"
#include "PDFIndirectObjectReference.h"
#include "PDFWriter.h"


#include "./lib/interpreter/PDFRecursiveInterpreter.h"
#include "./lib/text-placements/TextPlacementsCollector.h"
#include "./lib/text-placements/Transformations.h"
#include "./lib/font-translation/FontDecoder.h"

#include <algorithm>

using namespace std;
using namespace PDFHummus;

static const string scEmpty = "";

TextExtraction::TextExtraction() {

}
    
TextExtraction::~TextExtraction() {
    textsForPages.clear();
}

EStatusCode TextExtraction::ExtractTextPlacements(PDFParser* inParser) {
    EStatusCode status = eSuccess;

    for(unsigned long i=0;i<inParser->GetPagesCount();++i) {
        RefCountPtr<PDFDictionary> pageObject(inParser->ParsePage(i));
        PDFRecursiveInterpreter interpreter;
        TextPlacementsCollector collector;
        interpreter.InterpretPageContents(inParser, pageObject.GetPtr(), &collector);  
        TextElementList& texts = collector.onDone();

        textPlacementsForPages.push_back(TextElementList(texts));
    }    


    return status;
}

FontDecoder* TextExtraction::GetDecoderForCommand(PDFParser* inParser, PlacedTextCommand& inCommand) {
    if(!inCommand.textState.fontRef)
        return NULL;

    if(inCommand.textState.fontRef->GetType() == PDFObject::ePDFObjectDictionary) {
        RefCountPtr<PDFObject> fontDict = inCommand.textState.fontRef.GetPtr();
        // embedded, check cache first
        PDFObjectToFontDecoderMap::iterator it = embeddedFontDecoderCache.find(fontDict);
        if(it == embeddedFontDecoderCache.end()) {
            // ok. there's none, use this chance to create a new one
            it = embeddedFontDecoderCache.insert(PDFObjectToFontDecoderMap::value_type(fontDict, FontDecoder(inParser, (PDFDictionary*)fontDict.GetPtr()))).first;
        }
        return  &(it->second);
    }
    else if(inCommand.textState.fontRef->GetType() == PDFObject::ePDFObjectIndirectObjectReference) {
        ObjectIDType id = ((PDFIndirectObjectReference*)(inCommand.textState.fontRef.GetPtr()))->mObjectID;
        ObjectIDTypeToFontDecoderMap::iterator it = refrencedFontDecoderCache.find(id);
        if(it == refrencedFontDecoderCache.end()) {
            PDFObjectCastPtr<PDFDictionary> fontDict = inParser->ParseNewObject(id);
            if(!fontDict)
                return NULL;
            it = refrencedFontDecoderCache.insert(ObjectIDTypeToFontDecoderMap::value_type(id, FontDecoder(inParser, fontDict.GetPtr()))).first;
        }        
        return &(it->second);
    }
    return NULL;
}

EStatusCode TextExtraction::Translate(PDFParser* inParser) {
    TextElementListList::iterator pagesIt = textPlacementsForPages.begin();

    for(; pagesIt != textPlacementsForPages.end(); ++pagesIt) {
        TextElementList::iterator textElementsIt = pagesIt->begin();
        for(; textElementsIt != pagesIt->end(); ++textElementsIt) {
            PlacedTextCommandList::iterator commandIt = textElementsIt->texts.begin();
            for(; commandIt != textElementsIt->texts.end(); ++commandIt) {
                // Determine a decoder for the text font
                FontDecoder* decoder = GetDecoderForCommand(inParser, *commandIt);
                if(decoder) {
                    PlacedTextCommandArgumentList::iterator argumentIt = commandIt->text.begin();
                    for(;argumentIt != commandIt->text.end();++argumentIt) {
                        if(argumentIt->isText) {
                            // Translate the text
                            FontDecoderResult result = decoder->Translate(argumentIt->asBytes);
                            argumentIt->asText = result.asText;
                            argumentIt->translationMethod = result.translationMethod;

                            // Accumulate all args for a command
                            commandIt->allTextAsBytes.insert(commandIt->allTextAsBytes.end(), argumentIt->asBytes.begin(), argumentIt->asBytes.end());
                            commandIt->allTextAsText+= (result.asText.empty() ? string(" ") : result.asText);
                            commandIt->allTextTranslationMethod = result.translationMethod;
                        }
                    }
                }
            }
        }
    }

    return eSuccess;
}


EStatusCode TextExtraction::ComputeDimensions(PDFParser* inParser) {
    double buffer[6];

    // iterate the placements computing bounding boxes
    TextElementListList::iterator pagesIt = textPlacementsForPages.begin();

    for(; pagesIt != textPlacementsForPages.end(); ++pagesIt) {
        // this is a BT..ET sequance (some would call it - at text element....)
        TextElementList::iterator textElementsIt = pagesIt->begin();
        for(; textElementsIt != pagesIt->end(); ++textElementsIt) {
            bool hasDefaultTm = false;
            double nextPlacementDefaultTm[6] = {1,0,0,1,0,0};
            PlacedTextCommandList::iterator commandIt = textElementsIt->texts.begin();
            for(; commandIt != textElementsIt->texts.end(); ++commandIt) {
                PlacedTextCommand& item = *commandIt;
                // if matrix is not dirty (no matrix changing operators were running betwee items), replace with computed matrix of the previous round.
                if(!item.textState.tmDirty && hasDefaultTm)
                    copyMatrix(nextPlacementDefaultTm, item.textState.tm);

                // Compute matrix and placement after this text
                FontDecoder* decoder = GetDecoderForCommand(inParser, *commandIt);
                if(decoder) {
                    double accumulatedDisplacement = 0;
                    double minPlacement = 0;
                    double maxPlacement = 0;
                    copyMatrix(item.textState.tm, nextPlacementDefaultTm);
                    hasDefaultTm = true;

                    PlacedTextCommandArgumentList::iterator argumentIt = commandIt->text.begin();
                    for(;argumentIt != commandIt->text.end();++argumentIt) {
                        if(argumentIt->isText) {
                            DispositionResultList dispositions = decoder->ComputeDisplacements(argumentIt->asBytes);
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
                                multiplyMatrix({1,0,0,1,tx,0}, nextPlacementDefaultTm, buffer);
                                copyMatrix(buffer,nextPlacementDefaultTm);
                            }
                        }
                        else {
                            double tx = ((-argumentIt->pos/1000)*item.textState.fontSize)*item.textState.scale/100;
                            accumulatedDisplacement+=tx;
                            if(accumulatedDisplacement<minPlacement)
                                minPlacement = accumulatedDisplacement;
                            if(accumulatedDisplacement>maxPlacement)
                                maxPlacement = accumulatedDisplacement;
                            multiplyMatrix({1,0,0,1,tx,0}, nextPlacementDefaultTm, buffer);
                            copyMatrix(buffer,nextPlacementDefaultTm);
                        }
                    }    

                    double descentPlacement = (decoder->descent + item.textState.rise)*item.textState.fontSize/1000;
                    double ascentPlacement = (decoder->ascent + item.textState.rise)*item.textState.fontSize/1000;
                    item.localBBox[0] = minPlacement;
                    item.localBBox[1] = descentPlacement;
                    item.localBBox[2] = maxPlacement;
                    item.localBBox[3] = ascentPlacement;
                }
            }
        }
    }

    return eSuccess;
}

EStatusCode TextExtraction::ComputeResultPlacements() {
    // there's flattening of the text element level, no longer required
    // and computing of final constructs, so that each page will only have
    // a list of text per text commands, and each command is represented by a single ResultTextCommand
    double mtxBuffer[6];
    double boxBuffer[4];

    TextElementListList::iterator pagesIt = textPlacementsForPages.begin();

    for(; pagesIt != textPlacementsForPages.end(); ++pagesIt) {
        textsForPages.push_back(ResultTextCommandList());
        TextElementList::iterator textElementsIt = pagesIt->begin();
        for(; textElementsIt != pagesIt->end(); ++textElementsIt) {
            PlacedTextCommandList::iterator commandIt = textElementsIt->texts.begin();
            for(; commandIt != textElementsIt->texts.end(); ++commandIt) {
                ResultTextCommandList& pageResults = textsForPages.back();
                PlacedTextCommand& textPlacement = *commandIt;
                
                multiplyMatrix(textPlacement.textState.tm,textPlacement.ctm, mtxBuffer);
                transformBox(textPlacement.localBBox, mtxBuffer, boxBuffer);
                pageResults.push_back({
                    textPlacement.allTextAsText,
                    mtxBuffer,
                    textPlacement.localBBox,
                    boxBuffer
                });
            }
        }
    }

    return eSuccess;
}


EStatusCode TextExtraction::ExtractText(const std::string& inFilePath) {
    EStatusCode status = eSuccess;
    InputFile sourceFile;

    LatestWarnings.clear();
    LatestError.code = ETextExtractionError::eErrorNone;
    LatestError.description = scEmpty;

    textPlacementsForPages.clear();
    refrencedFontDecoderCache.clear();
    embeddedFontDecoderCache.clear();
    textsForPages.clear();

    do {
        status = sourceFile.OpenFile(inFilePath);
        if (status != eSuccess) {
            LatestError.code = ETextExtractionError::eErrorFileNotReadable;
            LatestError.description = string("Cannot read template file ") + inFilePath;
            break;
        }


        PDFParser parser;
        status = parser.StartPDFParsing(sourceFile.GetInputStream());
        if(status != eSuccess)
        {
            LatestError.code = ETextExtractionError::eErrorInternalPDFWriter;
            LatestError.description = string("Failed to parse template file");
            break;
        }

        // 1st phase - extract text placements
        status = ExtractTextPlacements(&parser);
        if(status != eSuccess)
            break;

        // 2nd phase - translate encoded bytes to text strings.
        status = Translate(&parser);
        if(status != eSuccess)
            break;

        // 3rd phase - compute dimensions
        status = ComputeDimensions(&parser);

        // 4th phase - flatten page placments, and simplify constructs
        status = ComputeResultPlacements();

        // 5th phase - cleanup interim structs
        textPlacementsForPages.clear();
        refrencedFontDecoderCache.clear();
        embeddedFontDecoderCache.clear();

    } while(false);

    return status;
}

const double LINE_HEIGHT_THRESHOLD = 5;

int GetOrientationCode(const ResultTextCommand& a) {
    // a very symplistic heuristics to try and logically group different text orientations in a way that makes sense

    // 1 0 0 1
    if(a.matrix[0] > 0 && a.matrix[3] > 0)
        return 0;

    // 0 1 -1 0
    if(a.matrix[1] > 0 && a.matrix[2] < 0)
        return 1;

    // -1 0 0 -1
    if(a.matrix[0] < 0 && a.matrix[3] < 0)
        return 2;

    // 0 -1 1 0 or other
    return 3;
}

bool CompareForOrientation(const ResultTextCommand& a, const ResultTextCommand& b, int code) {
    if(code == 0) {
        if(abs(a.globalBbox[1] - b.globalBbox[1]) > LINE_HEIGHT_THRESHOLD)
            return b.globalBbox[1] < a.globalBbox[1];
        else
            return a.globalBbox[0] < b.globalBbox[0];    

    } else if(code == 1) {
        if(abs(a.globalBbox[0] - b.globalBbox[0]) > LINE_HEIGHT_THRESHOLD)
            return a.globalBbox[0] <  b.globalBbox[0];
        else
            return a.globalBbox[1] < b.globalBbox[1];    

    } else if(code == 2) {
        if(abs(a.globalBbox[1] - b.globalBbox[1]) > LINE_HEIGHT_THRESHOLD)
            return a.globalBbox[1] < b.globalBbox[1];
        else
            return b.globalBbox[0] < a.globalBbox[0];    
           
    } else {
        // code 3
        if(abs(a.globalBbox[0] - b.globalBbox[0]) > LINE_HEIGHT_THRESHOLD)
            return b.globalBbox[0] < a.globalBbox[0];
        else
            return b.globalBbox[1] < a.globalBbox[1];    
    }
    
}

bool CompareResultTextCommand(const ResultTextCommand& a, const ResultTextCommand& b) {
    int codeA = GetOrientationCode(a);
    int codeB = GetOrientationCode(b);

    if(codeA == codeB) {
        return CompareForOrientation(a,b,codeA);
    }
    
    return codeA < codeB;
}

static const string scCRLN = "\r\n";

typedef std::vector<ResultTextCommand> ResultTextCommandVector;

bool AreSameLine(const ResultTextCommand& a, const ResultTextCommand& b) {
    int codeA = GetOrientationCode(a);
    int codeB = GetOrientationCode(b);

    if(codeA != codeB)
        return false;

    if(codeA == 0 || codeA == 2) {
        return abs(a.globalBbox[1] - b.globalBbox[1]) <= LINE_HEIGHT_THRESHOLD;
    } else {
        return abs(a.globalBbox[0] - b.globalBbox[0]) <= LINE_HEIGHT_THRESHOLD;
    }
}

std::string TextExtraction::GetResultsAsText() {
    stringstream result;
    ResultTextCommandListList::iterator itPages = textsForPages.begin();
    for(; itPages != textsForPages.end();++itPages) {
        ResultTextCommandVector sortedPageTextCommands(itPages->begin(), itPages->end());
        sort(sortedPageTextCommands.begin(), sortedPageTextCommands.end(), CompareResultTextCommand);

        ResultTextCommandVector::iterator itCommands = sortedPageTextCommands.begin();
        if(itCommands != sortedPageTextCommands.end()) {
            // k. got some text, let's build it
            stringstream lineResult;
            ResultTextCommand& latestItem = *itCommands;
            lineResult<<latestItem.text;
            ++itCommands;
            for(; itCommands != sortedPageTextCommands.end();++itCommands) {
                if(AreSameLine(latestItem, *itCommands)) {
                    lineResult<<itCommands->text;
                } else {
                    result<<lineResult.str()<<scCRLN;
                    lineResult.str(itCommands->text);
                }
                latestItem = *itCommands;
            }
            result<<lineResult.str()<<scCRLN;
        }     
    }

    return result.str();
}


EStatusCode TextExtraction::DecryptPDFForDebugging(
    const string& inTemplateFilePath,
    const string& inTargetOutputFilePath
) {
    return PDFWriter::RecryptPDF(  
		inTemplateFilePath,
		"",
		inTargetOutputFilePath,
		LogConfiguration::DefaultLogConfiguration(),
		PDFCreationSettings(false, true)
    );
}