A CLI (command line interface) to Extract text from PDF files.
Use from your terminal to dump a PDF file text to the std output.
Options exists to output to file, choose pages range etc.

```bash
Usage: TextExtraction.exe filepath <option(s)>
filepath - pdf file path
Options:
        -s, --start <d>                 start text extraction from a page index. use negative numbers to subtract from pages count
        -e, --end <d>                   end text extraction upto page index. use negative numbers to subtract from pages count
        -b, --bidi <RTL|LTR>            use bidi algo to convert visual to logical. provide default direction per document writing direction.
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


# Building and Installing the project

Once you installed pre-reqs, you can now build the project.

## Create the project files

To build you project start by creating a project file in a "build" folder off of the cmake configuration, like this:

```bash
mkdir build
cd build
cmake ..
```

I won't go on about cmake here, you can check out their website. going forward i'll stick to describing the minimal set of commands
you can use for building and installing.


## Build and install

Once you got the project file, you can now build the project. If you created an IDE file, you can use the IDE file to build the project.
Alternatively you can do so from the command line, again using cmake. 

The following builds the project from its root folder:
```bash
cmake --build build --config release
```

This will build the project inside the build folder. You will be able to look up the result execultable per how you normally do when building with the relevant build environment. For example, for windows,  the TextExtraction/Release folder will have the result file.

If you want, you can use the "install" verb of cmake to install a built product. Use the prefix param to specify where you want the result to be installed to

```bash
cmake --install ./build/TextExtraction --prefix ./etc/install
```

This will install the TextExtraction executable in ./etc/install.

if you do not have `cmake --install` as option, you can use a regular build with install target instead, and specify the install target in configuration stage, like this:

```bash
cd build
cmake .. -DCMAKE_INSTALL_PREFIX="..\etc\install"
cd ..

cmake --build build/TextExtraction --config release --target install
```

# Running
The end result is an executable, so just run it from comman line (it's a regular cli).

The minimal run requires a file path to a PDF from which you would like read the text, say on windows:
```console
etc\install\bin\TextExtraction.exe sample.pdf
```

# Bidirectional text support
PDF files contain text as drawing instructions. As a result what's being parsed is per the _visual_ order of text.
This doesn't matter much if your text is latin, or wholly left to right. However when the PDF has right to left text, either by itself or combined with left-to-right text or even numbers, the parsed text will appear to be reversed, or otherwise disorganized.
To take care of this there is support for Bidi reversal algorithm. This algorithm is implemented in ICU library, and this executable will use it if instructed so, and if ICU library is available.

BIDI conversion is turned off by default, as it does carry some performance price, however you can unlock it by using the USE_BIDI configuration variable. When calling `cmake` for congiruation, add `-DUSE_BIDI=1`. like this:

```bash
# only if you didnt create build lib yet
mkdir build
# then...
cd build
cmake .. -DUSE_BIDI=1
```

the module code does not come with ICU library pre-bundled with the code, so it will attempt to install it and if succesful, BIDI conversion will be supported. You can tell that BIDI conversion is supported by checking the help text of `TextExtraction`. If it shows the `-b, --bidi <RTL|LTR>` option, then it is available.

ICU Library installation process will try the following:
1. On windows specifically, it will try to use the existing Win10 SDK natively installed ICU library
2. Either on windows or other platform it will then try to find a pre-installed pacakge. For example, your Mac might already have it installed. you can help with a good ol' `brew install icu4c`.
3. If didn't work, then it will try to download ICU67 from it's source, and compile it. on most envs it will use the ICU makefile config, and on windows it will use the msbuild (this attempts to follow the instructions from icu). i think mingw will not work here...but you can try...and you can tweak `./TextExtraction/CMakeLists.txt` to try and make it work. there are pointers there for info.


# Using the code

If you want to use the text extraction capabilities in your own software, skip the `extract-text-cli.cpp` and using `TextExtraction` class directly. you provide it with a file path in `ExtractText()` and later can pick up the results in `GetResultsAsText()`. Modify it to your needs if you have other forms of desired output. The internal structure `textPlacementsForPages` allows you to be more flexible as to what you do with the text, and you can use `GetResultsAsText` as a reference implementation.

You are also welcome to use the `PDFRecursiveInterpreter` directly for any content intrepretation needs you may have.

License is Apache2, and provided [here](./LICENSE)

# Features and implementation details
This implementation is based on hummus PDF library. It implements a `PDFRecursiveInterpreter` which helps when looking to interpret PDF content streams. This has value in many possible implementations including content detection, content extraction, rendering etc. The interpreter is named recursive because it seemlessly interprets forms content used in the content stream, so you don't have to deal with it. It does allow you to cache your results and so avoid recursing into forms - when you wish to.

This text extraction algorithm is based on a previous Javascript based implementation that was described here - https://pdfhummus.com/post/156548561656/extracting-text-from-pdf-files. Most limitations stated there are true to this implementation.

This implementation has a few enhancments on top of the original:
- Computed structure is equivalent to the Javascript one, however the public output is text, for the sake of convenience. The code includes some heuristics to determine the text from this structure. The implementaiton is equivalent to the only usage i had back then...and it turned out quite good for my needs. I extended it to support multiple text orientations.
- I put in some code to better treat inline images, and skip them, so as not to interfere with the general interpretation. This should take care of some missing texts i had back then.
- bidi support included via ICU

