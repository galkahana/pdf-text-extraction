#include <iostream>
#include <string>

#include "EStatusCode.h"
#include "BoxingBase.h"
#include "OutputFile.h"
#include "InputStringStream.h"
#include "OutputStreamTraits.h"
#include "IByteReaderWithPosition.h"

#include "TextExtraction.h"

using namespace std;
using namespace PDFHummus;

static void ShowUsage(const string& name)
{
    cerr << "Usage: " << name << " filepath <option(s)>\n"
              << "filepath - pdf file path\n"
              << "Options:\n"
              << "\t-s, --start <d>\t\t\tstart text extraction from a page index. use negative numbers to subtract from pages count\n"
              << "\t-e, --end <d>\t\t\tend text extraction upto page index. use negative numbers to subtract from pages count\n"
              << "\t-o, --output /path/to/file\twrite result to output file\n"
              << "\t-h, --help\t\t\tShow this help message\n"
              << "\t-d, --debug /path/to/file\tcreate debug output file\n"
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
    bool writeToOutputFile = false;
    string outputFilePath = "";
    long startPage = 0;
    long endPage = -1;

    for (int i = 2; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "-h") || (arg == "--help")) {
            ShowUsage(argv[0]);
            return 0;
        } else if ((arg == "-s") || (arg == "--start")) {
            if (i + 1 < argc) {
                startPage = Long(argv[++i]);
            } else {
                std::cerr << "--start option requires one argument, which is the page to start." << std::endl;
                return 1;                 
            }            
        } else if ((arg == "-e") || (arg == "--end")) {
            if (i + 1 < argc) {
                endPage = Long(argv[++i]);
            } else {
                std::cerr << "--end option requires one argument, which is the page to end." << std::endl;
                return 1;                 
            }            
        } else if((arg == "-d") || (arg == "--debug")) {
            debugging = true;
            if (i + 1 < argc) {
                debugPath = argv[++i];
            } else {
                std::cerr << "--debug option requires one argument, which is the debug output file path." << std::endl;
                return 1;                 
            }            
        } else if((arg == "-o") || (arg == "--output")) {
            writeToOutputFile = true;
            if (i + 1 < argc) {
                outputFilePath = argv[++i];
            } else {
                std::cerr << "--output option requires one argument, which is the debug output file path." << std::endl;
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
        status = textExtraction.ExtractText(filePath, startPage, endPage);

        if(status != eSuccess) {
            cerr << "Error: " << textExtraction.LatestError.description.c_str() << endl;
        }
        TextExtractionWarningList::iterator it = textExtraction.LatestWarnings.begin();
        for(; it != textExtraction.LatestWarnings.end(); ++it) {
            cerr << "Warning: " << it->description.c_str() << endl;
        }    

        if(status == eSuccess) {

            if(writeToOutputFile) {
                OutputFile outputFile;
                status = outputFile.OpenFile(outputFilePath);
                if (status != eSuccess) {
                    cerr << "Error: Cannot open target file path for writing in" << outputFilePath.c_str() << endl;
                }
                else {
                    string result = textExtraction.GetResultsAsText();
                    InputStringStream textStream(result);		
                    OutputStreamTraits streamCopier((IByteWriter*)outputFile.GetOutputStream());
		            status = streamCopier.CopyToOutputStream(&textStream);
                }

            }
            else {
                cout<<textExtraction.GetResultsAsText().c_str();
            }
        }

    }


    return  status == eSuccess ? 0:1;
}