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
              << "\t-d, --debug /path/to/output/file\tcreate debug output file\n"
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
    bool debugging = false;
    string debugPath = "";

    for (int i = 2; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "-h") || (arg == "--help")) {
            ShowUsage(argv[0]);
            return 0;
        } else if((arg == "-d") || (arg == "--debug")) {
            debugging = true;
            if (i + 1 < argc) {
                debugPath = argv[++i];
            } else {
                std::cerr << "--debug option requires one argument, which is the debug output file path." << std::endl;
                return 1;                 
            }            
        } else {
            cerr << "Unrecognized option " << arg << std::endl ;
            ShowUsage(argv[0]);
            return 1;
        }
    }    

    TextExtraction textExtraction;
    EStatusCode status;
    if(debugging) {
        status = textExtraction.DecryptPDFForDebugging(filePath, debugPath);
    } else {
        status = textExtraction.ExtractText(filePath);

        if(status != eSuccess) {
            cerr << "Error: " << textExtraction.LatestError.description.c_str() << endl;
        }
        TextExtractionWarningList::iterator it = textExtraction.LatestWarnings.begin();
        for(; it != textExtraction.LatestWarnings.end(); ++it) {
            cerr << "Warning: " << it->description.c_str() << endl;
        }    

    }


    return  status == eSuccess ? 0:1;
}