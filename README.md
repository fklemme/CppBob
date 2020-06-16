# CppBob

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/972aed00d55c4215bbc821ac247bef6d)](https://app.codacy.com/manual/fklemme/CppBob?utm_source=github.com&utm_medium=referral&utm_content=fklemme/CppBob&utm_campaign=Badge_Grade_Dashboard)

Learn algorithmic thinking in C++

# Installation on Linux

    # apt install libsfml-dev
    $ make
    $ ./bin/cppbob

# Installation on Windows

Download and install SFML from project website: https://www.sfml-dev.org. If you're using Visual Studio 2017, you can try using the `download_sfml.ps1` script instead.

Prepared project files for Visual Studio are located in the `vs_projects` folder.

## Debug options

For the assets to be found, change "CppBob (right-click) -> Properties -> Debugging -> Working Directory" to "$(SolutionDir)..".
