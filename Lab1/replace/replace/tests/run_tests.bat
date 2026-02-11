@echo off
setlocal enabledelayedexpansion

set EXE=D:\university\second_grade\oop\Lab1\replace\x64\Debug\replace.exe
set INPUT_DIR=D:\university\second_grade\oop\Lab1\replace\replace\tests\input
set OUTPUT_DIR=D:\university\second_grade\oop\Lab1\replace\replace\tests\output
set EXPECTED_DIR=D:\university\second_grade\oop\Lab1\replace\replace\tests\expected

set PASSED=0
set FAILED=0
set TOTAL=0

if not exist "%OUTPUT_DIR%" mkdir "%OUTPUT_DIR%"

echo ============================================================
echo  Running tests for replace.exe
echo ============================================================
echo.

REM ============================================================
REM  CLI MODE TESTS (with files)
REM ============================================================

REM --- Test 01: Basic replacement "ma" -> "mama" ---
set /a TOTAL+=1
echo Test 01: CLI - Basic replacement ("ma" -^> "mama")
"%EXE%" "%INPUT_DIR%\input01.txt" "%OUTPUT_DIR%\output01.txt" "ma" "mama"
fc "%OUTPUT_DIR%\output01.txt" "%EXPECTED_DIR%\expected01.txt" >nul 2>&1
if !errorlevel! equ 0 (echo   [PASS] & set /a PASSED+=1) else (echo   [FAIL] & set /a FAILED+=1)

REM --- Test 02: Backtracking "1231234" -> "XYZ" in "12312312345" ---
set /a TOTAL+=1
echo Test 02: CLI - Backtracking ("1231234" -^> "XYZ" in "12312312345")
"%EXE%" "%INPUT_DIR%\input02.txt" "%OUTPUT_DIR%\output02.txt" "1231234" "XYZ"
fc "%OUTPUT_DIR%\output02.txt" "%EXPECTED_DIR%\expected02.txt" >nul 2>&1
if !errorlevel! equ 0 (echo   [PASS] & set /a PASSED+=1) else (echo   [FAIL] & set /a FAILED+=1)

REM --- Test 03: Empty search string ---
set /a TOTAL+=1
echo Test 03: CLI - Empty search string (no replacement expected)
"%EXE%" "%INPUT_DIR%\input03.txt" "%OUTPUT_DIR%\output03.txt" "" "replacement"
fc "%OUTPUT_DIR%\output03.txt" "%EXPECTED_DIR%\expected03.txt" >nul 2>&1
if !errorlevel! equ 0 (echo   [PASS] & set /a PASSED+=1) else (echo   [FAIL] & set /a FAILED+=1)

REM --- Test 04: No occurrences found ---
set /a TOTAL+=1
echo Test 04: CLI - No occurrences found
"%EXE%" "%INPUT_DIR%\input04.txt" "%OUTPUT_DIR%\output04.txt" "xyz" "abc"
fc "%OUTPUT_DIR%\output04.txt" "%EXPECTED_DIR%\expected04.txt" >nul 2>&1
if !errorlevel! equ 0 (echo   [PASS] & set /a PASSED+=1) else (echo   [FAIL] & set /a FAILED+=1)

REM --- Test 05: Replace with empty string (deletion) ---
set /a TOTAL+=1
echo Test 05: CLI - Replace with empty string (deletion)
"%EXE%" "%INPUT_DIR%\input05.txt" "%OUTPUT_DIR%\output05.txt" "beautiful " ""
fc "%OUTPUT_DIR%\output05.txt" "%EXPECTED_DIR%\expected05.txt" >nul 2>&1
if !errorlevel! equ 0 (echo   [PASS] & set /a PASSED+=1) else (echo   [FAIL] & set /a FAILED+=1)

REM --- Test 06: Multiple single-char replacements "a" -> "bb" ---
set /a TOTAL+=1
echo Test 06: CLI - Multiple single-char replacements ("a" -^> "bb" in "aaa")
"%EXE%" "%INPUT_DIR%\input06.txt" "%OUTPUT_DIR%\output06.txt" "a" "bb"
fc "%OUTPUT_DIR%\output06.txt" "%EXPECTED_DIR%\expected06.txt" >nul 2>&1
if !errorlevel! equ 0 (echo   [PASS] & set /a PASSED+=1) else (echo   [FAIL] & set /a FAILED+=1)

REM --- Test 07: Self-overlap prevention "ma" -> "mama" (no infinite loop) ---
set /a TOTAL+=1
echo Test 07: CLI - Self-overlap prevention ("ma" -^> "mama" in "mamama")
"%EXE%" "%INPUT_DIR%\input07.txt" "%OUTPUT_DIR%\output07.txt" "ma" "mama"
fc "%OUTPUT_DIR%\output07.txt" "%EXPECTED_DIR%\expected07.txt" >nul 2>&1
if !errorlevel! equ 0 (echo   [PASS] & set /a PASSED+=1) else (echo   [FAIL] & set /a FAILED+=1)

REM --- Test 08: Multi-line file ---
set /a TOTAL+=1
echo Test 08: CLI - Multi-line file ("foo" -^> "bar")
"%EXE%" "%INPUT_DIR%\input08.txt" "%OUTPUT_DIR%\output08.txt" "foo" "bar"
fc "%OUTPUT_DIR%\output08.txt" "%EXPECTED_DIR%\expected08.txt" >nul 2>&1
if !errorlevel! equ 0 (echo   [PASS] & set /a PASSED+=1) else (echo   [FAIL] & set /a FAILED+=1)

REM --- Test 09: Empty input file ---
set /a TOTAL+=1
echo Test 09: CLI - Empty input file
"%EXE%" "%INPUT_DIR%\input09.txt" "%OUTPUT_DIR%\output09.txt" "test" "replace"
fc "%OUTPUT_DIR%\output09.txt" "%EXPECTED_DIR%\expected09.txt" >nul 2>&1
if !errorlevel! equ 0 (echo   [PASS] & set /a PASSED+=1) else (echo   [FAIL] & set /a FAILED+=1)

REM --- Test 10: Search string = entire line ---
set /a TOTAL+=1
echo Test 10: CLI - Search string equals entire line ("hello" -^> "world")
"%EXE%" "%INPUT_DIR%\input10.txt" "%OUTPUT_DIR%\output10.txt" "hello" "world"
fc "%OUTPUT_DIR%\output10.txt" "%EXPECTED_DIR%\expected10.txt" >nul 2>&1
if !errorlevel! equ 0 (echo   [PASS] & set /a PASSED+=1) else (echo   [FAIL] & set /a FAILED+=1)

REM --- Test 11: Non-overlapping consecutive "aa" -> "b" in "aaaa" ---
set /a TOTAL+=1
echo Test 11: CLI - Non-overlapping consecutive ("aa" -^> "b" in "aaaa")
"%EXE%" "%INPUT_DIR%\input11.txt" "%OUTPUT_DIR%\output11.txt" "aa" "b"
fc "%OUTPUT_DIR%\output11.txt" "%EXPECTED_DIR%\expected11.txt" >nul 2>&1
if !errorlevel! equ 0 (echo   [PASS] & set /a PASSED+=1) else (echo   [FAIL] & set /a FAILED+=1)

REM --- Test 12: Search string longer than line content ---
set /a TOTAL+=1
echo Test 12: CLI - Search string longer than line content
"%EXE%" "%INPUT_DIR%\input12.txt" "%OUTPUT_DIR%\output12.txt" "this is a very long search string" "x"
fc "%OUTPUT_DIR%\output12.txt" "%EXPECTED_DIR%\expected12.txt" >nul 2>&1
if !errorlevel! equ 0 (echo   [PASS] & set /a PASSED+=1) else (echo   [FAIL] & set /a FAILED+=1)

REM --- Test 13: Partial match backtrack "aab" -> "X" in "aaab" ---
set /a TOTAL+=1
echo Test 13: CLI - Partial match backtrack ("aab" -^> "X" in "aaab")
"%EXE%" "%INPUT_DIR%\input13.txt" "%OUTPUT_DIR%\output13.txt" "aab" "X"
fc "%OUTPUT_DIR%\output13.txt" "%EXPECTED_DIR%\expected13.txt" >nul 2>&1
if !errorlevel! equ 0 (echo   [PASS] & set /a PASSED+=1) else (echo   [FAIL] & set /a FAILED+=1)

echo.
echo ============================================================
echo  CLI ERROR TESTS
echo ============================================================
echo.

REM --- Test 14: Too few arguments ---
set /a TOTAL+=1
echo Test 14: CLI Error - Too few arguments (2 args instead of 4)
"%EXE%" "%INPUT_DIR%\input01.txt" "%OUTPUT_DIR%\output14.txt" > "%OUTPUT_DIR%\stdout14.txt" 2>&1
set EXIT_CODE=!errorlevel!
if !EXIT_CODE! equ 1 (
    fc "%OUTPUT_DIR%\stdout14.txt" "%EXPECTED_DIR%\expected14.txt" >nul 2>&1
    if !errorlevel! equ 0 (echo   [PASS] & set /a PASSED+=1) else (echo   [FAIL] stdout mismatch & set /a FAILED+=1)
) else (echo   [FAIL] exit code=!EXIT_CODE!, expected 1 & set /a FAILED+=1)

REM --- Test 15: Input file not found ---
set /a TOTAL+=1
echo Test 15: CLI Error - Input file not found
"%EXE%" "nonexistent_file.txt" "%OUTPUT_DIR%\output15.txt" "search" "replace" > "%OUTPUT_DIR%\stdout15.txt" 2>&1
set EXIT_CODE=!errorlevel!
if !EXIT_CODE! equ 1 (
    fc "%OUTPUT_DIR%\stdout15.txt" "%EXPECTED_DIR%\expected15.txt" >nul 2>&1
    if !errorlevel! equ 0 (echo   [PASS] & set /a PASSED+=1) else (echo   [FAIL] stdout mismatch & set /a FAILED+=1)
) else (echo   [FAIL] exit code=!EXIT_CODE!, expected 1 & set /a FAILED+=1)

REM --- Test 16: Invalid output path ---
set /a TOTAL+=1
echo Test 16: CLI Error - Invalid output path
"%EXE%" "%INPUT_DIR%\input01.txt" "Z:\nonexistent_dir\output.txt" "ma" "mama" > "%OUTPUT_DIR%\stdout16.txt" 2>&1
set EXIT_CODE=!errorlevel!
if !EXIT_CODE! equ 1 (
    fc "%OUTPUT_DIR%\stdout16.txt" "%EXPECTED_DIR%\expected16.txt" >nul 2>&1
    if !errorlevel! equ 0 (echo   [PASS] & set /a PASSED+=1) else (echo   [FAIL] stdout mismatch & set /a FAILED+=1)
) else (echo   [FAIL] exit code=!EXIT_CODE!, expected 1 & set /a FAILED+=1)

echo.
echo ============================================================
echo  STDIN MODE TESTS
echo ============================================================
echo.

REM --- Test 17: Stdin basic replacement (Example 1) ---
set /a TOTAL+=1
echo Test 17: Stdin - Basic replacement ("ma" -^> "mama")
(echo ma & echo mama & echo mama delala pelmeni) | "%EXE%" > "%OUTPUT_DIR%\output17.txt"
fc "%OUTPUT_DIR%\output17.txt" "%EXPECTED_DIR%\expected17.txt" >nul 2>&1
if !errorlevel! equ 0 (echo   [PASS] & set /a PASSED+=1) else (echo   [FAIL] & set /a FAILED+=1)

REM --- Test 18: Stdin backtracking (Example 2) ---
set /a TOTAL+=1
echo Test 18: Stdin - Backtracking ("1231234" -^> "XYZ")
(echo 1231234 & echo XYZ & echo 12312312345) | "%EXE%" > "%OUTPUT_DIR%\output18.txt"
fc "%OUTPUT_DIR%\output18.txt" "%EXPECTED_DIR%\expected18.txt" >nul 2>&1
if !errorlevel! equ 0 (echo   [PASS] & set /a PASSED+=1) else (echo   [FAIL] & set /a FAILED+=1)

REM --- Test 19: Stdin empty search string (Example 3) ---
set /a TOTAL+=1
echo Test 19: Stdin - Empty search string (no replacement)
(echo. & echo tam & echo tut text) | "%EXE%" > "%OUTPUT_DIR%\output19.txt"
fc "%OUTPUT_DIR%\output19.txt" "%EXPECTED_DIR%\expected19.txt" >nul 2>&1
if !errorlevel! equ 0 (echo   [PASS] & set /a PASSED+=1) else (echo   [FAIL] & set /a FAILED+=1)

REM --- Test 20: Stdin multi-line text ---
set /a TOTAL+=1
echo Test 20: Stdin - Multi-line text
(echo ma & echo mama & echo mama delala pelmeni & echo ya pokushal plotno) | "%EXE%" > "%OUTPUT_DIR%\output20.txt"
fc "%OUTPUT_DIR%\output20.txt" "%EXPECTED_DIR%\expected20.txt" >nul 2>&1
if !errorlevel! equ 0 (echo   [PASS] & set /a PASSED+=1) else (echo   [FAIL] & set /a FAILED+=1)

REM --- Test 21: Stdin no text after search/replace ---
set /a TOTAL+=1
echo Test 21: Stdin - No text lines (only search and replace, then EOF)
(echo search & echo replace) | "%EXE%" > "%OUTPUT_DIR%\output21.txt"
fc "%OUTPUT_DIR%\output21.txt" "%EXPECTED_DIR%\expected21.txt" >nul 2>&1
if !errorlevel! equ 0 (echo   [PASS] & set /a PASSED+=1) else (echo   [FAIL] & set /a FAILED+=1)

echo.
echo ============================================================
echo  STDIN ERROR TESTS (exit code must be 0)
echo ============================================================
echo.

REM --- Test 22: Stdin error - missing replace string (Example 4) ---
set /a TOTAL+=1
echo Test 22: Stdin Error - Missing replace string (EOF after search)
(echo hello) | "%EXE%" > "%OUTPUT_DIR%\output22.txt"
set EXIT_CODE=!errorlevel!
fc "%OUTPUT_DIR%\output22.txt" "%EXPECTED_DIR%\expected22.txt" >nul 2>&1
if !errorlevel! equ 0 (
    if !EXIT_CODE! equ 0 (echo   [PASS] & set /a PASSED+=1) else (echo   [FAIL] exit code=!EXIT_CODE!, expected 0 & set /a FAILED+=1)
) else (echo   [FAIL] stdout mismatch & set /a FAILED+=1)

REM --- Test 23: Stdin error - immediate EOF (no input at all) ---
set /a TOTAL+=1
echo Test 23: Stdin Error - Immediate EOF (no search string)
"%EXE%" < nul > "%OUTPUT_DIR%\output23.txt"
set EXIT_CODE=!errorlevel!
fc "%OUTPUT_DIR%\output23.txt" "%EXPECTED_DIR%\expected23.txt" >nul 2>&1
if !errorlevel! equ 0 (
    if !EXIT_CODE! equ 0 (echo   [PASS] & set /a PASSED+=1) else (echo   [FAIL] exit code=!EXIT_CODE!, expected 0 & set /a FAILED+=1)
) else (echo   [FAIL] stdout mismatch & set /a FAILED+=1)

echo.
echo ============================================================
echo  HELP MODE TEST
echo ============================================================
echo.

REM --- Test 24: Help flag -h ---
set /a TOTAL+=1
echo Test 24: Help - "-h" flag
"%EXE%" -h > "%OUTPUT_DIR%\output24.txt"
fc "%OUTPUT_DIR%\output24.txt" "%EXPECTED_DIR%\expected24.txt" >nul 2>&1
if !errorlevel! equ 0 (echo   [PASS] & set /a PASSED+=1) else (echo   [FAIL] & set /a FAILED+=1)

echo.
echo ============================================================
echo  SUMMARY
echo ============================================================
echo  Total:  !TOTAL!
echo  Passed: !PASSED!
echo  Failed: !FAILED!
echo ============================================================

if !FAILED! gtr 0 (
    echo  RESULT: SOME TESTS FAILED
) else (
    echo  RESULT: ALL TESTS PASSED
)

echo.
endlocal
pause