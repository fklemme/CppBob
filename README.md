# CppBob


[![pipeline status](https://gitlab.kruecke.net/fklemme/CppBob/badges/master/pipeline.svg)](https://gitlab.kruecke.net/fklemme/CppBob/-/pipelines?ref=master)

Learn algorithmic thinking in C++

# Installation on Linux

    # apt install libsfml-dev # (optional)
    $ cmake -S . -B build
    $ cmake --build build
    $ ./build/cppbob

# Installation on Windows

Use [CMake](https://cmake.org/download/) to generate the Visual Studio solution in a `build` subfolder.

## Debug options

For the assets to be found, change "CppBob (right-click) -> Properties -> Debugging -> Working Directory" to "$(SolutionDir)..".
