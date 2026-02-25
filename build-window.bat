cls
@echo off

if not exist build mkdir build

rem generate cmake files
cmake -O . -B ./build -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=OFF

rem copy assets & .dll files to output dir
@REM robocopy "./Game/Assets"  "./build/Game/Debug/Assets" /E
@REM robocopy "./Vendors/bin/"  "./build/bin/Debug/" /E

rem compile project
cd build && cmake --build . 

echo compilation finished!