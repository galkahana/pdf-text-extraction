// Test for the reports of images: IGraphicContentInterpreterHandler::OnImagePainted and
// GraphicContentInterpreter::GetInlineImagesCount.
// image_xobjects.pdf draws the image XObject 5 0 R twice: on the page with the CTM
// [100 0 0 50 10 20], and in the form Fm1, drawn inside /Artifact marked content, with the CTM
// [20 0 0 30 300 400]. The page and the form each hold an inline image.

#include "PDFParser.h"
#include "InputFile.h"
#include "EStatusCode.h"
#include "RefCountPtr.h"
#include "PDFDictionary.h"

#include "lib/graphic-content-parsing/GraphicContentInterpreter.h"
#include "lib/graphic-content-parsing/IGraphicContentInterpreterHandler.h"

#include <iostream>
#include <vector>

using namespace std;
using namespace PDFHummus;

class ImageCollector : public IGraphicContentInterpreterHandler {
public:
    virtual bool OnTextElementComplete(const TextElement& inTextElement) {return true;}
    virtual bool OnPathPainted(const PathElement& inPathElement) {return true;}
    virtual bool OnImagePainted(const ImageElement& inImageElement) {
        images.push_back(inImageElement);
        return true;
    }

    vector<ImageElement> images;
};

static bool IsImageAt(const ImageElement& inImage, const double (&inCTM)[6], bool inArtifact) {
    if(inImage.objectID != 5 || !inImage.image || inImage.graphicState.artifact != inArtifact)
        return false;
    for(int i = 0; i < 6; ++i) {
        double difference = inImage.graphicState.ctm[i] - inCTM[i];
        if(difference > 0.001 || difference < -0.001)
            return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    if(argc < 2) {
        cout << "Usage: ImageReportTest image_xobjects.pdf" << endl;
        return 1;
    }

    InputFile pdfFile;
    PDFParser parser;
    if(pdfFile.OpenFile(argv[1]) != eSuccess || parser.StartPDFParsing(pdfFile.GetInputStream()) != eSuccess) {
        cout << "Failed to parse " << argv[1] << endl;
        return 1;
    }
    RefCountPtr<PDFDictionary> page(parser.ParsePage(0));
    if(!page) {
        cout << "Failed to parse page 0" << endl;
        return 1;
    }

    GraphicContentInterpreter interpreter;
    ImageCollector collector;
    interpreter.InterpretPageContents(&parser, page.GetPtr(), &collector);

    bool ok = true;
    const double pageCTM[6] = {100, 0, 0, 50, 10, 20};
    const double formCTM[6] = {20, 0, 0, 30, 300, 400};
    if(collector.images.size() != 2 ||
        !IsImageAt(collector.images[0], pageCTM, false) ||
        !IsImageAt(collector.images[1], formCTM, true)) {
        cout << "Unexpected image reports: " << collector.images.size() << ", expected the page's and the form's" << endl;
        ok = false;
    }
    if(interpreter.GetInlineImagesCount() != 2) {
        cout << interpreter.GetInlineImagesCount() << " inline images, expected 2" << endl;
        ok = false;
    }
    if(ok)
        cout << "Images reported" << endl;
    return ok ? 0 : 1;
}
