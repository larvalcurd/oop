@echo off

echo ===========================
echo    Running tests
echo ===========================
echo.

set EXE=D:\university\second_grade\oop\Lab1\invert\x64\Debug\invert.exe

set PASS=0
set FAIL=0
set TOTAL=0

REM ---- TEST 01 ----
set /a TOTAL+=1
%EXE% input\t01_input.txt > output\t01_output.txt 2>&1
fc output\t01_output.txt expected\t01_expected.txt >nul
if %errorlevel%==0 (
    echo [PASS] 01 Basic integer matrix
    set /a PASS+=1
) else (
    echo [FAIL] 01 Basic integer matrix
    set /a FAIL+=1
)

REM ---- TEST 02 ----
set /a TOTAL+=1
%EXE% input\t02_input.txt > output\t02_output.txt 2>&1
fc output\t02_output.txt expected\t02_expected.txt >nul
if %errorlevel%==0 (
    echo [PASS] 02 Float coefficients
    set /a PASS+=1
) else (
    echo [FAIL] 02 Float coefficients
    set /a FAIL+=1
)

REM ---- TEST 03 ----
set /a TOTAL+=1
%EXE% input\t03_input.txt > output\t03_output.txt 2>&1
fc output\t03_output.txt expected\t03_expected.txt >nul
if %errorlevel%==0 (
    echo [PASS] 03 Singular matrix
    set /a PASS+=1
) else (
    echo [FAIL] 03 Singular matrix
    set /a FAIL+=1
)

REM ---- TEST 04 ----
set /a TOTAL+=1
%EXE% input\t04_input.txt > output\t04_output.txt 2>&1
fc output\t04_output.txt expected\t04_expected.txt >nul
if %errorlevel%==0 (
    echo [PASS] 04 Non-numeric
    set /a PASS+=1
) else (
    echo [FAIL] 04 Non-numeric
    set /a FAIL+=1
)

REM ---- TEST 05 ----
set /a TOTAL+=1
%EXE% input\t05_input.txt > output\t05_output.txt 2>&1
fc output\t05_output.txt expected\t05_expected.txt >nul
if %errorlevel%==0 (
    echo [PASS] 05 Partial number
    set /a PASS+=1
) else (
    echo [FAIL] 05 Partial number
    set /a FAIL+=1
)

REM ---- TEST 06 ----
set /a TOTAL+=1
%EXE% input\t06_input.txt > output\t06_output.txt 2>&1
fc output\t06_output.txt expected\t06_expected.txt >nul
if %errorlevel%==0 (
    echo [PASS] 06 Only 2 rows
    set /a PASS+=1
) else (
    echo [FAIL] 06 Only 2 rows
    set /a FAIL+=1
)

REM ---- TEST 07 ----
set /a TOTAL+=1
%EXE% input\t07_input.txt > output\t07_output.txt 2>&1
fc output\t07_output.txt expected\t07_expected.txt >nul
if %errorlevel%==0 (
    echo [PASS] 07 4 elements per row
    set /a PASS+=1
) else (
    echo [FAIL] 07 4 elements per row
    set /a FAIL+=1
)

REM ---- TEST 08 ----
set /a TOTAL+=1
%EXE% input\t08_input.txt > output\t08_output.txt 2>&1
fc output\t08_output.txt expected\t08_expected.txt >nul
if %errorlevel%==0 (
    echo [PASS] 08 2 elements per row
    set /a PASS+=1
) else (
    echo [FAIL] 08 2 elements per row
    set /a FAIL+=1
)

REM ---- TEST 09 ----
set /a TOTAL+=1
%EXE% input\t09_input.txt > output\t09_output.txt 2>&1
fc output\t09_output.txt expected\t09_expected.txt >nul
if %errorlevel%==0 (
    echo [PASS] 09 Empty file
    set /a PASS+=1
) else (
    echo [FAIL] 09 Empty file
    set /a FAIL+=1
)

REM ---- TEST 10 ----
set /a TOTAL+=1
%EXE% input\t10_input.txt > output\t10_output.txt 2>&1
fc output\t10_output.txt expected\t10_expected.txt >nul
if %errorlevel%==0 (
    echo [PASS] 10 Identity matrix
    set /a PASS+=1
) else (
    echo [FAIL] 10 Identity matrix
    set /a FAIL+=1
)

REM ---- TEST 11 ----
set /a TOTAL+=1
%EXE% input\t11_input.txt > output\t11_output.txt 2>&1
fc output\t11_output.txt expected\t11_expected.txt >nul
if %errorlevel%==0 (
    echo [PASS] 11 Diagonal matrix
    set /a PASS+=1
) else (
    echo [FAIL] 11 Diagonal matrix
    set /a FAIL+=1
)

REM ---- TEST 12 ----
set /a TOTAL+=1
%EXE% input\t12_input.txt > output\t12_output.txt 2>&1
fc output\t12_output.txt expected\t12_expected.txt >nul
if %errorlevel%==0 (
    echo [PASS] 12 Negative numbers
    set /a PASS+=1
) else (
    echo [FAIL] 12 Negative numbers
    set /a FAIL+=1
)

REM ---- TEST 13 (command pipe) ----
set /a TOTAL+=1
cmd /c "type input\t01_input.txt | %EXE%" > output\t13_output.txt 2>&1
fc output\t13_output.txt expected\t13_expected.txt >nul
if %errorlevel%==0 (
    echo [PASS] 13 Stdin pipe
    set /a PASS+=1
) else (
    echo [FAIL] 13 Stdin pipe
    set /a FAIL+=1
)

REM ---- TEST HELP ----
set /a TOTAL+=1
%EXE% -h > output\t14_output.txt 2>&1
fc output\t14_output.txt expected\t14_expected.txt >nul
if %errorlevel%==0 (
    echo [PASS] 14 Help flag
    set /a PASS+=1
) else (
    echo [FAIL] 14 Help flag
    set /a FAIL+=1
)

REM ---- TEST NONEXISTENT FILE ----
set /a TOTAL+=1
%EXE% nonexistent.txt > output\t15_output.txt 2>&1
fc output\t15_output.txt expected\t15_expected.txt >nul
if %errorlevel%==0 (
    echo [PASS] 15 Nonexistent file
    set /a PASS+=1
) else (
    echo [FAIL] 15 Nonexistent file
    set /a FAIL+=1
)

REM ---- TEST TOO MANY ARGS ----
set /a TOTAL+=1
%EXE% arg1 arg2 > output\t16_output.txt 2>&1
fc output\t16_output.txt expected\t16_expected.txt >nul
if %errorlevel%==0 (
    echo [PASS] 16 Too many args
    set /a PASS+=1
) else (
    echo [FAIL] 16 Too many args
    set /a FAIL+=1
)

echo.
echo Tests done.
echo Total: %TOTAL%
echo Passed: %PASS%
echo Failed: %FAIL%