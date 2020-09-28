A CLI (command line interface) to Extract text from PDF files.
Use from your terminal to dump a PDF file text to the std output.
Options exists to output to file, choose pages range etc.

```bash
Usage: TextExtraction.exe filepath <option(s)>
filepath - pdf file path
Options:
        -s, --start <d>                 start text extraction from a page index. use negative numbers to subtract from pages count
        -e, --end <d>                   end text extraction upto page index. use negative numbers to subtract from pages count
        -o, --output /path/to/file      write result to output file
        -q, --quiet                     quiet run. only shows errors and warnings
        -h, --help                      Show this help message
        -d, --debug /path/to/file       create debug output file
```

# First time around

This is a C++ Project using CMake as project builder.
To build/develop You will need:

1. a compiler. for win you can use vs studio. choose community version - https://visualstudio.microsoft.com/
2. cmake - download from here - https://cmake.org/


# Building the project

Once you installed pre-reqs, you can now build the project.

## Create the project files

To build you project start by creating a project file in a "build" folder off of the cmake configuration, like this:

```bash
mkdir build
cd build
cmake ..
```

If you do this, this will generate a project file that can be used to build the project from.
The nature of the project file is dependent on the default generator selected for your environment.
For example, if you are on a PC and installed visual studio, it will generate a visual studio project. You can see the .sln file right there in the root of the build folder. you can even open it and use it for debugging. Same goes for OSX...although out of my experiance it's most chance that it'll build a plain makefile there. If you want to affect what generator gets chosen (so, for example, you can create an xcode project) use `cmake -g <GENERATOR NAME> ..` when running the cmake command. To know which generator names exist, run `cmake --help` and the "Generators" section.


## build and install

Once you got the project file, you can now build the project. If you created an IDE file, you can use the IDE file to build the project.
Alternatively you can do so from the command line, again using cmake. 

The following builds the project from its root folder:
```bash
cmake --build build --config release
```

This will build the project inside the build folder. You will be able to look up the result execultable per how you normally do when building with the relevant build environment. For example, for windows,  the TextExtraction/Release folder will have the result file.

If you want, you can use the "install", after an initial build as specified, target to specify where to install the result executable (and accompanying files).

Use this to specify and later build the install to occur in the `./etc/install` folder relative to the root:

```bash
cd build
cmake .. -DCMAKE_INSTALL_PREFIX="..\etc\install"
cd ..

cmake --build ./build/TextExtraction --config release --target install
```

This will install the TextExtraction executable.
For developers - to install all projects (including pdfwriter libraries), use `.` instead of `./TextExtraction`

# Running
The end result is an executable, so just run it from comman line (it's a regular cli).

The minimal run requires a file path to a PDF from which you would like read the text, say on windows:
```console
etc\install\bin\TextExtraction.exe sample.pdf
```

# Using the code

If you want to use the text extraction capabilities in your own software, skip the `extract-text-cli.cpp` and using `TextExtraction` class directly. you provide it with a file path in `ExtractText()` and later can pick up the results in `GetResultsAsText()`. Modify it to your needs if you have other forms of desired output. The internal structure `textPlacementsForPages` allows you to be more flexible as to what you do with the text, and you can use `GetResultsAsText` as a reference implementation.

You are also welcome to use the `PDFRecursiveInterpreter` directly for any content intrepretation needs you may have.

License is Apache2, and provided [here](./LICENSE)

# Features and implementation details
This implementaiton is based on hummus PDF library. Specifically it implements a `PDFRecursiveInterpreter` which helps when looking to interpret PDF content streams. This has value in many possible implementations including content detection, content extraction, rendering etc. The interpreter is named recursive because it seemlessly interprets forms content used in the content stream, so you don't have to deal with it. It does allow you to cache your results and so avoid recursing into forms - when you wish to.

This text extraction algorithm is based on a previous Javascript based implementation that was described here - https://pdfhummus.com/post/156548561656/extracting-text-from-pdf-files. Most limitations stated there are true to this implementation.

This implementation was extended in the following manners:
- Computed structure is equivalent to the Javascript one, however the public output is text, for the sake of convenience. The code includes some heuristics to determine the text from this structure. The implementaiton is equivalent to the only usage i had back then...and it turned out quite good for my needs. I extended it to support multiple text orientations.
- I put in some code to better treat inline images, and skip them, so as not to interfere with the general interpretation. This should take care of some missing texts i had back then.

I didn't deal with Bidi text implementation here. frankly creating a bidi cross platform with ICU bidi lib inclusion is an art im yet to master. im sure it should be simpler with what local implementation you have, and you can use the output text as input to that implementation, it being _prefectly logical_.

