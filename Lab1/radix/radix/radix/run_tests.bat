@echo off
setlocal enabledelayedexpansion

if "%~1"=="" (
    echo Usage: run_tests.bat ^<path_to_exe^>
    exit /b 1
)

set EXE=%~1

echo Running tests for: %EXE%

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