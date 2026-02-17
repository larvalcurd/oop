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

REM === File-based tests (matrix passed as file argument) ===
call :file_test 01 "Basic integer matrix"    || exit /b 1
call :file_test 02 "Float coefficients"      || exit /b 1
call :file_test 03 "Singular matrix"         || exit /b 1
call :file_test 04 "Non-numeric value"       || exit /b 1
call :file_test 05 "Partial number 3abc"     || exit /b 1
call :file_test 06 "Only 2 rows"             || exit /b 1
call :file_test 07 "4 elements per row"      || exit /b 1
call :file_test 08 "2 elements per row"      || exit /b 1
call :file_test 09 "Empty file"              || exit /b 1
call :file_test 10 "Identity matrix"         || exit /b 1
call :file_test 11 "Diagonal matrix"         || exit /b 1
call :file_test 12 "Negative numbers"        || exit /b 1

REM === Stdin pipe test ===
call :stdin_test 13 "Stdin pipe"             || exit /b 1

REM === Special argument tests ===
call :args_test 14 "Help flag"          "-h"              || exit /b 1
call :args_test 15 "Nonexistent file"   "nonexistent.txt" || exit /b 1
call :args_test 16 "Too many args"      "arg1 arg2"       || exit /b 1

echo.
echo All tests passed!
exit /b 0

REM ============================================================
:file_test
set N=%~1
set D=%~2
"%EXE%" "tests\input\t%N%_input.txt" > "tests\output\t%N%_output.txt" 2>&1
fc "tests\output\t%N%_output.txt" "tests\expected\t%N%_expected.txt" > nul
if errorlevel 1 (
    echo [FAIL] t%N% - %D%
    exit /b 1
)
echo [ OK ] t%N% - %D%
exit /b 0

REM ============================================================
:stdin_test
set N=%~1
set D=%~2
cmd /c "type tests\input\t01_input.txt | %EXE%" > "tests\output\t%N%_output.txt" 2>&1
fc "tests\output\t%N%_output.txt" "tests\expected\t%N%_expected.txt" > nul
if errorlevel 1 (
    echo [FAIL] t%N% - %D%
    exit /b 1
)
echo [ OK ] t%N% - %D%
exit /b 0

REM ============================================================
:args_test
set N=%~1
set D=%~2
set A=%~3
"%EXE%" %A% > "tests\output\t%N%_output.txt" 2>&1
fc "tests\output\t%N%_output.txt" "tests\expected\t%N%_expected.txt" > nul
if errorlevel 1 (
    echo [FAIL] t%N% - %D%
    exit /b 1
)
echo [ OK ] t%N% - %D%
exit /b 0