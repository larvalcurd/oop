@echo off
setlocal enabledelayedexpansion

REM ============================
REM Paths
REM ============================
set EXE=D:\university\second_grade\oop\Lab1\out\build\x64-debug\Lab1\replace.exe
set INPUT_DIR=.\tests\input
set EXPECTED_DIR=.\tests\expected
set OUTPUT_DIR=.\tests\output

REM Create output dir if needed
if not exist %OUTPUT_DIR% mkdir %OUTPUT_DIR%

set FAILED=0

echo Running tests...
echo.

REM ============================
REM Test 1
REM ============================
echo Test 1: CLI basic replacement
%EXE% %INPUT_DIR%\input1.txt %OUTPUT_DIR%\output1.txt "ma" "mama"
fc %OUTPUT_DIR%\output1.txt %EXPECTED_DIR%\expected1.txt >nul
if %errorlevel% equ 0 (
    echo PASS
) else (
    echo FAIL
    set FAILED=1
)
echo.

REM ============================
REM Test 2
REM ============================
echo Test 2: CLI overlapping replacement
%EXE% %INPUT_DIR%\input2.txt %OUTPUT_DIR%\output2.txt "1231234" "XYZ"
fc %OUTPUT_DIR%\output2.txt %EXPECTED_DIR%\expected2.txt >nul
if %errorlevel% equ 0 (
    echo PASS
) else (
    echo FAIL
    set FAILED=1
)
echo.

REM ============================
REM Test 3
REM ============================
echo Test 3: CLI empty search string
%EXE% %INPUT_DIR%\input3.txt %OUTPUT_DIR%\output3.txt "" "replacement"
fc %OUTPUT_DIR%\output3.txt %EXPECTED_DIR%\expected3.txt >nul
if %errorlevel% equ 0 (
    echo PASS
) else (
    echo FAIL
    set FAILED=1
)
echo.

REM ============================
REM Test 4
REM ============================
echo Test 4: CLI invalid arguments
%EXE% %INPUT_DIR%\input1.txt >nul 2>&1
set CODE=%ERRORLEVEL%
if %CODE% equ 1 (
    echo PASS
) else (
    echo FAIL
    set FAILED=1
)
echo.

REM ============================
REM Test 5
REM ============================
echo Test 5: CLI file not found
%EXE% nonexistent.txt %OUTPUT_DIR%\output5.txt "search" "replace" >nul 2>&1
set CODE=%ERRORLEVEL%
if %CODE% equ 1 (
    echo PASS
) else (
    echo FAIL
    set FAILED=1
)
echo.

REM ============================
REM Test 6
REM ============================
echo Test 6: Stdin basic
set TEMP_FILE=temp_input.txt

> %TEMP_FILE% (
    echo ma
    echo mama
    echo mama delala pelmeni
    echo ya pokushal plotno
)

type %TEMP_FILE% | %EXE% > %OUTPUT_DIR%\output6.txt
del %TEMP_FILE%

fc %OUTPUT_DIR%\output6.txt %EXPECTED_DIR%\expected6.txt >nul
if %errorlevel% equ 0 (
    echo PASS
) else (
    echo FAIL
    set FAILED=1
)
echo.

REM ============================
REM Test 7
REM ============================
echo Test 7: Stdin error
set TEMP_FILE=temp_input.txt

> %TEMP_FILE% (
    echo hello
)

type %TEMP_FILE% | %EXE% > %OUTPUT_DIR%\output7.txt
set CODE=%ERRORLEVEL%
del %TEMP_FILE%

fc %OUTPUT_DIR%\output7.txt %EXPECTED_DIR%\expected7.txt >nul

if %errorlevel% equ 0 (
    if %CODE% equ 0 (
        echo PASS
    ) else (
        echo FAIL
        set FAILED=1
    )
) else (
    echo FAIL
    set FAILED=1
)
echo.

REM ============================
REM Test 8
REM ============================
echo Test 8: Help mode
%EXE% -h > %OUTPUT_DIR%\output8.txt
fc %OUTPUT_DIR%\output8.txt %EXPECTED_DIR%\expected8.txt >nul
if %errorlevel% equ 0 (
    echo PASS
) else (
    echo FAIL
    set FAILED=1
)
echo.

REM ============================
REM Test 9
REM ============================
echo Test 9: CLI self-overlap prevention
%EXE% %INPUT_DIR%\input9.txt %OUTPUT_DIR%\output9.txt "ma" "mama"
fc %OUTPUT_DIR%\output9.txt %EXPECTED_DIR%\expected9.txt >nul
if %errorlevel% equ 0 (
    echo PASS
) else (
    echo FAIL
    set FAILED=1
)
echo.

REM ============================
REM Test 10
REM ============================
echo Test 10: CLI large file handling
%EXE% %INPUT_DIR%\input10.txt %OUTPUT_DIR%\output10.txt "large" "small"
fc %OUTPUT_DIR%\output10.txt %EXPECTED_DIR%\expected10.txt >nul
if %errorlevel% equ 0 (
    echo PASS
) else (
    echo FAIL
    set FAILED=1
)
echo.

REM ============================
REM Summary
REM ============================
if %FAILED% equ 0 (
    echo ALL TESTS PASSED
) else (
    echo SOME TESTS FAILED
)

echo All tests completed.