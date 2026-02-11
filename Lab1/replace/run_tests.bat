@echo off
setlocal enabledelayedexpansion

set REPLACE_EXE=replace.exe
if not exist %REPLACE_EXE% (
    echo replace.exe not found.
    exit /b 1
)

md tests\output 2>nul

set PASSED=0
set TOTAL=16

rem Test 01: CLI ??????? ??????
%REPLACE_EXE% tests\input\input01.txt tests\output\output01.txt "hello" "hi"
if %errorlevel% equ 0 (
    fc tests\output\output01.txt tests\expected\expected01.txt >nul 2>&1
    if !errorlevel! equ 0 (
        echo Test 01: PASS
        set /a PASSED+=1
    ) else (
        echo Test 01: FAIL
    )
) else (
    echo Test 01: FAIL
)

rem Test 02: CLI ??????????????? ??????
%REPLACE_EXE% tests\input\input02.txt tests\output\output02.txt "1231234" "XYZ"
if %errorlevel% equ 0 (
    fc tests\output\output02.txt tests\expected\expected02.txt >nul 2>&1
    if !errorlevel! equ 0 (
        echo Test 02: PASS
        set /a PASSED+=1
    ) else (
        echo Test 02: FAIL
    )
) else (
    echo Test 02: FAIL
)

rem Test 03: CLI ?????? ?????? ??????
%REPLACE_EXE% tests\input\input03.txt tests\output\output03.txt "" "x"
if %errorlevel% equ 0 (
    fc tests\output\output03.txt tests\expected\expected03.txt >nul 2>&1
    if !errorlevel! equ 0 (
        echo Test 03: PASS
        set /a PASSED+=1
    ) else (
        echo Test 03: FAIL
    )
) else (
    echo Test 03: FAIL
)

rem Test 04: CLI ???????????? ??????????
%REPLACE_EXE% tests\input\input01.txt tests\output\output04.txt "hello" > tests\output\output04.txt 2>&1
if %errorlevel% equ 1 (
    fc tests\output\output04.txt tests\expected\expected04.txt >nul 2>&1
    if !errorlevel! equ 0 (
        echo Test 04: PASS
        set /a PASSED+=1
    ) else (
        echo Test 04: FAIL
    )
) else (
    echo Test 04: FAIL
)

rem Test 05: CLI ??????? ???? ?? ??????
%REPLACE_EXE% nonexistent.txt tests\output\output05.txt "search" "replace" > tests\output\output05.txt 2>&1
if %errorlevel% equ 1 (
    fc tests\output\output05.txt tests\expected\expected05.txt >nul 2>&1
    if !errorlevel! equ 0 (
        echo Test 05: PASS
        set /a PASSED+=1
    ) else (
        echo Test 05: FAIL
    )
) else (
    echo Test 05: FAIL
)

rem Test 06: CLI ?????? ?? ????? ??????? ??????, ?????????? ?????? ??????
%REPLACE_EXE% tests\input\input06.txt tests\output\output06.txt "ma" "mama"
if %errorlevel% equ 0 (
    fc tests\output\output06.txt tests\expected\expected06.txt >nul 2>&1
    if !errorlevel! equ 0 (
        echo Test 06: PASS
        set /a PASSED+=1
    ) else (
        echo Test 06: FAIL
    )
) else (
    echo Test 06: FAIL
)

rem Test 07: CLI ????????
%REPLACE_EXE% tests\input\input07.txt tests\output\output07.txt " world" ""
if %errorlevel% equ 0 (
    fc tests\output\output07.txt tests\expected\expected07.txt >nul 2>&1
    if !errorlevel! equ 0 (
        echo Test 07: PASS
        set /a PASSED+=1
    ) else (
        echo Test 07: FAIL
    )
) else (
    echo Test 07: FAIL
)

rem Test 08: CLI ????? == ??????
%REPLACE_EXE% tests\input\input08.txt tests\output\output08.txt "a" "a"
if %errorlevel% equ 0 (
    fc tests\output\output08.txt tests\expected\expected08.txt >nul 2>&1
    if !errorlevel! equ 0 (
        echo Test 08: PASS
        set /a PASSED+=1
    ) else (
        echo Test 08: FAIL
    )
) else (
    echo Test 08: FAIL
)

rem Test 09: CLI ????? ??????? ??????
%REPLACE_EXE% tests\input\input09.txt tests\output\output09.txt "hello" "x"
if %errorlevel% equ 0 (
    fc tests\output\output09.txt tests\expected\expected09.txt >nul 2>&1
    if !errorlevel! equ 0 (
        echo Test 09: PASS
        set /a PASSED+=1
    ) else (
        echo Test 09: FAIL
    )
) else (
    echo Test 09: FAIL
)

rem Test 10: CLI ??????? ????
if not exist tests\input\input10.txt (
    for /l %%i in (1,1,10000) do echo line %%i >> tests\input\input10.txt
)
if not exist tests\expected\expected10.txt (
    for /l %%i in (1,1,10000) do echo LINE %%i >> tests\expected\expected10.txt
)
%REPLACE_EXE% tests\input\input10.txt tests\output\output10.txt "line" "LINE"
if %errorlevel% equ 0 (
    fc tests\output\output10.txt tests\expected\expected10.txt >nul 2>&1
    if !errorlevel! equ 0 (
        echo Test 10: PASS
        set /a PASSED+=1
    ) else (
        echo Test 10: FAIL
    )
) else (
    echo Test 10: FAIL
)

rem Test 11: CLI ???????????
%REPLACE_EXE% tests\input\input11.txt tests\output\output11.txt "	" " "
if %errorlevel% equ 0 (
    fc tests\output\output11.txt tests\expected\expected11.txt >nul 2>&1
    if !errorlevel! equ 0 (
        echo Test 11: PASS
        set /a PASSED+=1
    ) else (
        echo Test 11: FAIL
    )
) else (
    echo Test 11: FAIL
)

rem Test 12: CLI Unicode
%REPLACE_EXE% tests\input\input12.txt tests\output\output12.txt "??????" "??????????"
if %errorlevel% equ 0 (
    fc tests\output\output12.txt tests\expected\expected12.txt >nul 2>&1
    if !errorlevel! equ 0 (
        echo Test 12: PASS
        set /a PASSED+=1
    ) else (
        echo Test 12: FAIL
    )
) else (
    echo Test 12: FAIL
)

rem Test 13: stdin ?????????? ????
type tests\input\input13.txt | %REPLACE_EXE% > tests\output\output13.txt
if %errorlevel% equ 0 (
    fc tests\output\output13.txt tests\expected\expected13.txt >nul 2>&1
    if !errorlevel! equ 0 (
        echo Test 13: PASS
        set /a PASSED+=1
    ) else (
        echo Test 13: FAIL
    )
) else (
    echo Test 13: FAIL
)

rem Test 14: stdin ??????
type tests\input\input14.txt | %REPLACE_EXE% > tests\output\output14.txt
if %errorlevel% equ 0 (
    fc tests\output\output14.txt tests\expected\expected14.txt >nul 2>&1
    if !errorlevel! equ 0 (
        echo Test 14: PASS
        set /a PASSED+=1
    ) else (
        echo Test 14: FAIL
    )
) else (
    echo Test 14: FAIL
)

rem Test 15: ????? -h
%REPLACE_EXE% -h > tests\output\output15.txt
if %errorlevel% equ 0 (
    fc tests\output\output15.txt tests\expected\expected15.txt >nul 2>&1
    if !errorlevel! equ 0 (
        echo Test 15: PASS
        set /a PASSED+=1
    ) else (
        echo Test 15: FAIL
    )
) else (
    echo Test 15: FAIL
)

rem Test 16: ?? ?????????? ?????
%REPLACE_EXE% tests\input\input16.txt tests\output\output16.txt "bc" "X"
if %errorlevel% equ 0 (
    fc tests\output\output16.txt tests\expected\expected16.txt >nul 2>&1
    if !errorlevel! equ 0 (
        echo Test 16: PASS
        set /a PASSED+=1
    ) else (
        echo Test 16: FAIL
    )
) else (
    echo Test 16: FAIL
)

echo Passed: %PASSED%/%TOTAL%