# First time install

This is a C++ Project using CMake as project builder.
You will need:

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

The following builds the project:
```bash
cd build
cmake --build . --config release
```

This will build the project inside the build folder. You will be able to look up the result execultable per how you normally do when building with the relevant build environment. For example, for windows,  the Imposition/Release folder will have the result file.

If you want, you can use the "install" target to specify where to install the result executable (and accompanying files).

Use this to specify and later build the install to occur in the `./etc/install` folder relative to the root:

```bash
cd build
cmake .. -DCMAKE_INSTALL_PREFIX="..\etc\install"

cmake --build ./TextExtraction --config release --target install
```

This will install the TextExtraction executable and assets in the install folder.
For developers - to instlal all projects (including pdfwriter libraries), use `.` instead of `./TextExtraction`

# Running
The end result is an executable, so just run it from comman line (it's a regular cli)