#include <iostream>
#include <string>

#include "EStatusCode.h"

#include "TextExtraction.h"

using namespace std;
using namespace PDFHummus;

static void ShowUsage(const string& name)
{
    cerr << "Usage: " << name << " filepath <option(s)>\n"
              << "filepath - pdf file path\n"
              << "Options:\n"
              << "\t-h, --help\t\t\t\tShow this help message"
              << endl;
}


int main(int argc, char* argv[])
{
    if(argc < 2) {
        ShowUsage(argv[0]);
        return 1;        
    }

    string filePath = argv[1];

    for (int i = 2; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "-h") || (arg == "--help")) {
            ShowUsage(argv[0]);
            return 0;
        } else {
            cerr << "Unrecognized option " << arg << std::endl;
            ShowUsage(argv[0]);
            return 1;
        }
    }    

    TextExtraction textExtraction;
    EStatusCode status;

    // execute code
    status = textExtraction.ExtractText(filePath);

    if(status != eSuccess) {
        cerr << "Error: " << textExtraction.LatestError.description.c_str() << endl;
    }
    TextExtractionWarningList::iterator it = textExtraction.LatestWarnings.begin();
    for(; it != textExtraction.LatestWarnings.end(); ++it) {
        cerr << "Warning: " << it->description.c_str() << endl;
    }    

    return  status == eSuccess ? 0:1;
}