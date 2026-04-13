cls
@echo off

set BUILD_TYPE=%1
set ARCH=%2
set PROJECT_NAME=%3

if "%BUILD_TYPE%"=="" set BUILD_TYPE=Debug
if /I "%BUILD_TYPE%" NEQ "Debug" if /I "%BUILD_TYPE%" NEQ "Release" (
    echo Invalid build type: %BUILD_TYPE%
    exit /b 1
)

if "%ARCH%"=="" set ARCH=x64
if /I "%ARCH%" NEQ "x86" if /I "%ARCH%" NEQ "x64" (
    echo Invalid architecture: %ARCH%
    exit /b 1
)

if not exist build mkdir build

if not exist build\%BUILD_TYPE% echo "build\%BUILD_TYPE% folder is not found" exit /b 1
if not exist build\%BUILD_TYPE%\%ARCH% echo "build\%BUILD_TYPE%\%ARCH% folder is not found" exit /b 1
if not exist build\%BUILD_TYPE%\%ARCH%\%PROJECT_NAME% echo "build\%BUILD_TYPE%\%ARCH%\%PROJECT_NAME% folder is not found" exit /b 1

cd build/%BUILD_TYPE%/%ARCH%/%PROJECT_NAME% && ctest -C %BUILD_TYPE% --output-on-failure

echo Testing finished!