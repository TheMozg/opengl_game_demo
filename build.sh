#!bash
set -e
set -x

mkdir -p build
cd build

cmake ..

if uname | grep -q NT; then
    MSBuild.exe //nologo //verbosity:minimal game.vcxproj;
else
    make;
fi