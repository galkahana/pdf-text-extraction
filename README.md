A CLI (command line interface) to Extract text from PDF files.
Use from your terminal to dump a PDF file text to the std output.
Options exists to output to file, choose pages range etc.

```bash
Usage: TextExtraction.exe filepath <option(s)>
filepath - pdf file path
Options:
        -s, --start <d>                         start text extraction from a page index. use negative numbers to subtract from pages count
        -e, --end <d>                           end text extraction upto page index. use negative numbers to subtract from pages count
        -b, --bidi <RTL|LTR>                    use bidi algo to convert visual to logical. provide default direction per document writing direction.
        -p, --spacing <BOTH|HOR|VER|NONE>       add spaces between pieces of text considering their relative positions. default is BOTH
        -t, --tables				extract tables instead of text. Each table is represented in CSV
        -o, --output /path/to/file              write result to output file (or files for tables export)
        -q, --quiet                             quiet run. only shows errors and warnings
        -h, --help                              Show this help message
        -d, --debug /path/to/file               create debug output file
```

**New** it is now also possible to use this CLI to **extract tables**. This is still experimental due to how tables
may be represented in many multiple ways, but with enough samples the code can be upgraded to be more able.
When asking for table extraction only tables are output as CSV. std output will show CSV content of the PDF tables. When outputting
to files each file will contain a single table. The output file name is the first table output file, where later tables file names will use
the file name as base file name along with an ordinal (starting from 1).

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
cmake --install ./build/TextExtraction --prefix ./etc/install --config release
```

This will install the TextExtraction executable in ./etc/install.

if you do not have `cmake --install` as option, you can use a regular build with install target instead, and specify the install target in configuration stage, like this:

```bash
cd build
cmake .. -DCMAKE_INSTALL_PREFIX="..\etc\install"
cd ..

cmake --build build/TextExtraction --config release --target install
```

## testing

This project uses ctest for running tests. ctest is part of cmake and should be installed as part of cmake installation.
To run the project tests (after having created the project files in ./build) go:

```bash
ctest --test-dir build -C release
```

This should scan the folders for tests and run them.


## VSCode usage

If you are developing this project using vscode here's some suggestions to help you:  
- install vscode C++ extensions:
        - C/C++
        - C/C++ Extension Pack
        - C/C++ Themes
- install vscode cmake extensions:
        - Cmake
        - Cmake Tools
        - CMake Test Explorder

This should help you enable testing and debugging in vscode. Specifically you can debug the TextExtrction CLI with the `(lldb) launch` debug target, and the tests are debuggable as well.

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

# Internal table parsing
When parsing for tables the final output is CSV. CSVs can't handle split cells (normally found in the header, there'd be a single cell spanning multiple cells and then internally there'd be a split providing the individual columns headers names) so it's not important to parse internal columns/rows of a cell. However for the sake of excercise, and if anyone wants to output this to Excel/Google Sheets/Numbers where split cells are a reality, I did program internal cell parsing for table structure which would provide the relevant info. It's off by default, and you can use the SHOULD_PARSE_INTERNAL_TABLES configuratin variable to turn it on. This would mean the `CellInRow` struct might have a non null internalTable, that is - when one such exists. when calling cmake for configuration, add `-DSHOULD_PARSE_INTERNAL_TABLES=1` to get the parsing going.

# Using the code

If you want to use the text extraction capabilities in your own software, skip the `extract-text-cli.cpp` and using `TextExtraction` class directly. you provide it with a file path in `ExtractText()` and later can pick up the results in `GetResultsAsText()`. Modify it to your needs if you have other forms of desired output. The internal structure `textsForPages` allows you to be more flexible as to what you do with the text, and you can use `GetResultsAsText` as a reference implementation.

As for tables extraction, the class `TableExtraction` might be of use. It's `ExtractTables()` method  gets the same paraps as the text extraction `ExtractText()` and the results will be placed in `tablesForPages` data structure. To get CSV output you can either use `GetAllAsCSVText` which returns a single string of all tables CSV representaitons concatenated...or a more useful `GetTableAsCSVText` which
gets a single Table construct from `tablesForPages` and returns a CSV representation for it.

You are also welcome to use the `PDFRecursiveInterpreter` directly for any content intrepretation needs you may have.

License is Apache2, and provided [here](./LICENSE)

# Features and implementation details

This text extraction algorithm is based on a previous Javascript based implementation that was described here - https://pdfhummus.com/post/156548561656/extracting-text-from-pdf-files. Most limitations stated there are true to this implementation:

1. No support of vertical writing fonts. In calculating the text measures i’m assuming horizontal. 
2. No support for large fonts (CIDs) that don’t hold unicode map (that is, only got a predefined Cmap name).
The 2nd is a little cryptic. Thing is i wasn't 100% sure how to deal with those CID fonts texts and translate them properly. maybe some sample files of such cases can help me figure it out. i reckon there shouldn't be many of those in the wild cause i think most of them do have a unicode map.


This implementation has a few enhancments on top of the original:
- Computed structure is equivalent to the Javascript one, however the public output is text, for the sake of convenience. The code includes some heuristics to determine the text from this structure. The implementaiton is equivalent to the only usage i had back then...and it turned out quite good for my needs. I extended it to support multiple text orientations.
- I put in some code to better treat inline images, and skip them, so as not to interfere with the general interpretation. This should take care of some missing texts i had back then.
- bidi support included via ICU


Tables parsing is based on the very few samples I tried, so it's probably quite limited at this point. The tables parsing reuses the text intepretation of the base text extraction algorithm as well as attempting to locate vertical and horizontal lines to determine tables based on them. Vertical and horizontal lines are then grouped to tables based on whether they have intersection relationships (direct or indirect by instersecting with lines that in turn intersect etc.) accounting for lines that only split cells and are not 100% column/row lines. It then attempts to determine rows and cells in those rows. Then based on the text placements locations it posits them in their right cells.

# Solution Archiecture

This implementation is based on hummus PDF library. Specifically it uses the parsing capabilities of hummus to interpret the pages content and understand things like lines and texts.

Both `TextExtraction` and `TableExtraction` run through interpretation of pages content to extract relevant placeemnts - glyphs or glyphs and lines respectively. Then each one attempts to understand texts from glyphs and parsed font data. For tables lines are also inspected to determine horizontal and vertical lines that form tables.

The `PDFRecursiveInterpreter` is used for the very basic interpretation of PDF content. it is named recursive becasue it recurses into forms placed in what page content is fed for interpreation. The interpreter launches an event to its handler every time it comes up with a content drawing operator. It provides to the handler both the operator and operand. `PDFRecursiveInterpreter` can  be used as is in many possible implementations involving PDF content interpreation, such as extracting content (text, images etc.) or even rendering.

The operators and operands are fed to the `GraphicContentInterpreter`. This class understands specific operators and what they do. At this point it understands anything that has to do with paths and texts, to be able to support the relevant implementation for this code, but it can have more code added to it to understand much more...based on the desired implementation. In its form here it launches and event to its handler for every placed text elements and for every placed path.

The `TextInterpreter` code is used to convert the text placements provided by the interpreter to actual text. The text placements only contain glyph information and local graphic state, and the `TextInterpreter` adds font data to determine texts from the glyphs and their position in the page. Upon completing translating a text placement it launches its own text complete event to provide its handler with the translated and posited text element (there's a certain nuance here with respect to PDF text elements and actual text placements...which will skip in this description). 

The `TableComposer` code is used to build tables from collections of vertical and horizontal lines and text. Normally used at the page level it can figure out which lines map to which tables (in case there are multiple tables on the page) and which texts go into which cells. Its output is a list of tables each defining rows and cells and texts in those cells. There's quite a bit of heuristics in the whole table construction process...which is why it's a bit more at an experimental stage than the older text extraction part.

For tables there's also `TableCSVExport` which exports a single `Table` object build by the `TableComposer` to a CSV string.
