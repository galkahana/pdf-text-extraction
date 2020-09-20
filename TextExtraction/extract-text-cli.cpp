#include <iostream>
#include <string>

#include "EStatusCode.h"

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
            std::cerr << "Unrecognized option " << arg << std::endl;
            ShowUsage(argv[0]);
            return 1;
        }
    }    


    EStatusCode status = eSuccess;

    // execute code

    return  status == eSuccess ? 0:1;
}