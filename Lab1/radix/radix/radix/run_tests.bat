@echo off
setlocal enabledelayedexpansion

set EXE=D:\university\second_grade\oop\Lab1\radix\radix\x64\Debug\radix.exe

echo Running tests...

if not exist tests\output mkdir tests\output

del tests\output\*.txt > nul 2>&1

for %%f in (tests\input\*.txt) do (
    set fname=%%~nf

    for /f "usebackq tokens=* delims=" %%l in ("%%f") do (
        set OUTFILE=tests\output\!fname!.txt

        %EXE% %%l > "!OUTFILE!" 2>&1

        fc "!OUTFILE!" "tests\expected\!fname!.txt" > nul
        if errorlevel 1 (
            echo [FAIL] !fname!
            echo   Input: %%l
            echo   Output was saved to: !OUTFILE!
            exit /b 1
        ) else (
            echo [ OK ] !fname!
        )
    )
)

echo All tests passed!