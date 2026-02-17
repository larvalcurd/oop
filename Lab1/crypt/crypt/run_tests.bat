@echo off
cd /d "%~dp0"
setlocal enabledelayedexpansion

if "%~1"=="" (
    echo Usage: run_tests.bat ^<path_to_exe^>
    exit /b 1
)

set PROGRAM=%~1
set PASSED=0
set FAILED=0

echo ============================================
echo         crypt.exe automated tests
echo ============================================
echo.

REM --- Clean previous temp files ---
del /q _enc.bin _dec.txt _input.txt _empty.txt _single.txt 2>nul

REM --- Create test input files ---
echo hello>_input.txt
type nul >_empty.txt
<nul set /p="A">_single.txt

REM ========== ROUND-TRIP TESTS ==========
echo [Round-trip tests]

%PROGRAM% crypt _input.txt _enc.bin 42 >nul 2>&1 && %PROGRAM% decrypt _enc.bin _dec.txt 42 >nul 2>&1 && fc /b _input.txt _dec.txt >nul 2>&1 && (
    echo   Test 1 PASSED: key=42
    set /a PASSED+=1
) || (
    echo   Test 1 FAILED: key=42
    set /a FAILED+=1
)

%PROGRAM% crypt _input.txt _enc.bin 0 >nul 2>&1 && %PROGRAM% decrypt _enc.bin _dec.txt 0 >nul 2>&1 && fc /b _input.txt _dec.txt >nul 2>&1 && (
    echo   Test 2 PASSED: key=0
    set /a PASSED+=1
) || (
    echo   Test 2 FAILED: key=0
    set /a FAILED+=1
)

%PROGRAM% crypt _input.txt _enc.bin 255 >nul 2>&1 && %PROGRAM% decrypt _enc.bin _dec.txt 255 >nul 2>&1 && fc /b _input.txt _dec.txt >nul 2>&1 && (
    echo   Test 3 PASSED: key=255
    set /a PASSED+=1
) || (
    echo   Test 3 FAILED: key=255
    set /a FAILED+=1
)

%PROGRAM% crypt _input.txt _enc.bin 128 >nul 2>&1 && %PROGRAM% decrypt _enc.bin _dec.txt 128 >nul 2>&1 && fc /b _input.txt _dec.txt >nul 2>&1 && (
    echo   Test 4 PASSED: key=128
    set /a PASSED+=1
) || (
    echo   Test 4 FAILED: key=128
    set /a FAILED+=1
)

%PROGRAM% crypt _empty.txt _enc.bin 100 >nul 2>&1 && %PROGRAM% decrypt _enc.bin _dec.txt 100 >nul 2>&1 && fc /b _empty.txt _dec.txt >nul 2>&1 && (
    echo   Test 5 PASSED: empty file
    set /a PASSED+=1
) || (
    echo   Test 5 FAILED: empty file
    set /a FAILED+=1
)

%PROGRAM% crypt _single.txt _enc.bin 77 >nul 2>&1 && %PROGRAM% decrypt _enc.bin _dec.txt 77 >nul 2>&1 && fc /b _single.txt _dec.txt >nul 2>&1 && (
    echo   Test 6 PASSED: single byte
    set /a PASSED+=1
) || (
    echo   Test 6 FAILED: single byte
    set /a FAILED+=1
)

REM ========== ENCRYPTION VALIDATION ==========
echo.
echo [Encryption validation]

%PROGRAM% crypt _input.txt _enc.bin 42 >nul 2>&1
fc /b _input.txt _enc.bin >nul 2>&1 && (
    echo   Test 7 FAILED: encrypted = original
    set /a FAILED+=1
) || (
    echo   Test 7 PASSED: encrypted differs from original
    set /a PASSED+=1
)

%PROGRAM% crypt _input.txt _enc.bin 42 >nul 2>&1
%PROGRAM% decrypt _enc.bin _dec.txt 43 >nul 2>&1
fc /b _input.txt _dec.txt >nul 2>&1 && (
    echo   Test 8 FAILED: wrong key decoded correctly
    set /a FAILED+=1
) || (
    echo   Test 8 PASSED: wrong key gives wrong result
    set /a PASSED+=1
)

REM ========== ERROR HANDLING ==========
echo.
echo [Error handling - all must be rejected]

%PROGRAM% >nul 2>&1 && (
    echo   Test 9 FAILED: no args accepted
    set /a FAILED+=1
) || (
    echo   Test 9 PASSED: no args rejected
    set /a PASSED+=1
)

%PROGRAM% crypt >nul 2>&1 && (
    echo   Test 10 FAILED: 2 args accepted
    set /a FAILED+=1
) || (
    echo   Test 10 PASSED: 2 args rejected
    set /a PASSED+=1
)

%PROGRAM% crypt _input.txt _enc.bin >nul 2>&1 && (
    echo   Test 11 FAILED: missing key accepted
    set /a FAILED+=1
) || (
    echo   Test 11 PASSED: missing key rejected
    set /a PASSED+=1
)

%PROGRAM% crypt _input.txt _enc.bin 42 extra >nul 2>&1 && (
    echo   Test 12 FAILED: extra args accepted
    set /a FAILED+=1
) || (
    echo   Test 12 PASSED: extra args rejected
    set /a PASSED+=1
)

%PROGRAM% encode _input.txt _enc.bin 42 >nul 2>&1 && (
    echo   Test 13 FAILED: invalid mode accepted
    set /a FAILED+=1
) || (
    echo   Test 13 PASSED: invalid mode rejected
    set /a PASSED+=1
)

%PROGRAM% crypt _input.txt _enc.bin abc >nul 2>&1 && (
    echo   Test 14 FAILED: key=abc accepted
    set /a FAILED+=1
) || (
    echo   Test 14 PASSED: key=abc rejected
    set /a PASSED+=1
)

%PROGRAM% crypt _input.txt _enc.bin -1 >nul 2>&1 && (
    echo   Test 15 FAILED: key=-1 accepted
    set /a FAILED+=1
) || (
    echo   Test 15 PASSED: key=-1 rejected
    set /a PASSED+=1
)

%PROGRAM% crypt _input.txt _enc.bin 256 >nul 2>&1 && (
    echo   Test 16 FAILED: key=256 accepted
    set /a FAILED+=1
) || (
    echo   Test 16 PASSED: key=256 rejected
    set /a PASSED+=1
)

%PROGRAM% crypt _input.txt _enc.bin 42abc >nul 2>&1 && (
    echo   Test 17 FAILED: key=42abc accepted
    set /a FAILED+=1
) || (
    echo   Test 17 PASSED: key=42abc rejected
    set /a PASSED+=1
)

%PROGRAM% crypt _input.txt _enc.bin 3.14 >nul 2>&1 && (
    echo   Test 18 FAILED: key=3.14 accepted
    set /a FAILED+=1
) || (
    echo   Test 18 PASSED: key=3.14 rejected
    set /a PASSED+=1
)

%PROGRAM% crypt nonexistent.txt _enc.bin 42 >nul 2>&1 && (
    echo   Test 19 FAILED: missing file accepted
    set /a FAILED+=1
) || (
    echo   Test 19 PASSED: missing input file rejected
    set /a PASSED+=1
)

%PROGRAM% crypt _input.txt _input.txt 42 >nul 2>&1 && (
    echo   Test 20 FAILED: same in/out accepted
    set /a FAILED+=1
) || (
    echo   Test 20 PASSED: same in/out rejected
    set /a PASSED+=1
)

REM ========== SUMMARY ==========
echo.
echo ============================================
set /a TOTAL=PASSED+FAILED
echo Results: !PASSED!/!TOTAL! passed, !FAILED!/!TOTAL! failed
if !FAILED! EQU 0 (echo ALL TESTS PASSED) else (echo SOME TESTS FAILED)
echo ============================================

REM --- Cleanup ---
del /q _input.txt _empty.txt _single.txt _enc.bin _dec.txt 2>nul

exit /b !FAILED!