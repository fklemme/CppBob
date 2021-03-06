# CppBob


[![pipeline status](https://gitlab.kruecke.net/fklemme/CppBob/badges/master/pipeline.svg)](https://gitlab.kruecke.net/fklemme/CppBob/-/pipelines?ref=master)

Learn algorithmic thinking in C++

# Installation on Linux

    # apt install libsfml-dev # (optional)
    $ cmake -S . -B build
    $ cmake --build build
    $ ./build/cppbob

# Installation on Windows

Use the [CMake](https://cmake.org/download/) GUI to generate the Visual Studio solution files (e.g., in a `build` sub-folder).
After opening the solution, right-click `cppbob` in solution explorer and select "Set as Startup Project".
Press "F5" or click the green play-button at the top to run the application.