cls
@echo off

set BUILD_TYPE=%1
set ARCH=%2
set PROJECT_NAME=%3

if "%BUILD_TYPE%"=="" set BUILD_TYPE=Debug
if /I "%BUILD_TYPE%" NEQ "Debug" if /I "%BUILD_TYPE%" NEQ "Release" (
    echo Invalid build type: %BUILD_TYPE%
    echo Usage: build-window.bat [Debug|Release] [x86|x64]
    exit /b 1
)

if "%ARCH%"=="" set ARCH=x64
if /I "%ARCH%" NEQ "x86" if /I "%ARCH%" NEQ "x64" (
    echo Invalid architecture: %ARCH%
    echo Usage: build-window.bat [Debug|Release] [x86|x64]
    exit /b 1
)

if not exist build mkdir build

if not exist build\%BUILD_TYPE% mkdir build\%BUILD_TYPE%
if not exist build\%BUILD_TYPE%\%ARCH% mkdir build\%BUILD_TYPE%\%ARCH%

rem generate cmake files
cmake -O . -B ./build/%BUILD_TYPE%/%ARCH% -A %ARCH% -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DBUILD_SHARED_LIBS=OFF

rem copy assets & .dll files to output dir
robocopy "./%PROJECT_NAME%/Assets"  "./build/%BUILD_TYPE%/%ARCH%/%PROJECT_NAME%/%BUILD_TYPE%/Assets" /E
robocopy "./Vendors/bin/"  "./build/%BUILD_TYPE%/%ARCH%/lib/%BUILD_TYPE%/" /E

rem compile project

cd build/%BUILD_TYPE%/%ARCH% && cmake --build . --config %BUILD_TYPE%

echo compilation finished!