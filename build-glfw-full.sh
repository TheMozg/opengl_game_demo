#!bash
set -e
set -x

mkdir -p build_glfw_full
cd build_glfw_full

cmake ../glfw-3.2.1

if uname | grep -q NT; then
    MSBuild.exe //nologo //verbosity:minimal GLFW.sln;
else
    make;
fi