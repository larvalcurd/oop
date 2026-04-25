@echo off
setlocal

set "PROJECT_DIR=D:\university\second_grade\oop\Lab4\C++\Lab4"
set "EXE=%PROJECT_DIR%\build\src\Debug\Lab4.exe"
set "INPUT=%PROJECT_DIR%\input-art.txt"
set "MINGW_BIN=D:\Program Files\CLion 2025.3.3\bin\mingw\bin"

cd /d "%PROJECT_DIR%"

if not exist "%EXE%" (
    echo ERROR: executable not found:
    echo %EXE%
    exit /b 1
)

if not exist "%INPUT%" (
    echo ERROR: input file not found:
    echo %INPUT%
    exit /b 1
)

set "PATH=%MINGW_BIN%;%PATH%"

echo Running...
"%EXE%" < "%INPUT%"
if errorlevel 1 (
    echo ERROR: program finished with non-zero exit code.
    exit /b 1
)

echo App finished.

endlocal
