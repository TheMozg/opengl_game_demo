# opengl_game_demo
Simple 3D game based on OpenGL and [GLFW library](https://github.com/glfw/glfw) for window context.

## Setup
### Windows
1. Install [Visual Studio](https://www.visualstudio.com/) and add `MSBuild.exe` to `PATH`.
For example, for Visual Studio Community 2017 default location is
`C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\MSBuild\15.0\Bin`.

2. Install [CMake](https://cmake.org/) and add `cmake.exe` to `PATH`.
Default location is `C:\Program Files\CMake\bin`.

### Linux
1. Install [CMake](https://cmake.org/).
2. Install [XOrg](https://www.x.org/wiki/) development package. 
For example `xorg-dev` if you are using `Debian` or `Ubuntu`.

## Build
Simply run `make` (or `.\toolchain\make.exe` on Windows). `Makefile` is a simple wrapper for lunching `cmake` with predefined configuration.