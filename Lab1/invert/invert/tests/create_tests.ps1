# create_tests.ps1
# Creates test files for 3x3 matrix inversion program
# Run: powershell -ExecutionPolicy Bypass -File create_tests.ps1

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

#region === SETTINGS ===

$BaseDirectory = if ($PSScriptRoot) { $PSScriptRoot } else { (Get-Location).Path }

$Tab  = "`t"
$Crlf = "`r`n"

#endregion

#region === HELPER FUNCTIONS ===

function Initialize-TestDirectories {
    $directories = @("input", "expected", "output")
    
    foreach ($dirName in $directories) {
        $dirPath = Join-Path $BaseDirectory $dirName
        if (-not (Test-Path $dirPath)) {
            New-Item -ItemType Directory -Path $dirPath | Out-Null
        }
    }
}

function Write-TestFile {
    param(
        [string]$RelativePath,
        [string]$Content
    )
    
    $fullPath = Join-Path $BaseDirectory $RelativePath
    [System.IO.File]::WriteAllText($fullPath, $Content)
}

function Format-MatrixRow {
    param([array]$Values)
    return ($Values -join $Tab) + $Crlf
}

function Format-Matrix {
    param(
        [array]$Row1,
        [array]$Row2,
        [array]$Row3
    )
    
    return (Format-MatrixRow $Row1) + 
           (Format-MatrixRow $Row2) + 
           (Format-MatrixRow $Row3)
}

#endregion

#region === CREATE TESTS ===

Initialize-TestDirectories

# ---------------------------------------------------------------------
#  TEST 01: Integer matrix (example 1)
# ---------------------------------------------------------------------
Write-TestFile "input\t01_input.txt" (Format-Matrix `
    @(1, 2, 3) `
    @(0, 1, 4) `
    @(5, 6, 0)
)

Write-TestFile "expected\t01_expected.txt" (Format-Matrix `
    @("-24.000", "18.000",  "5.000") `
    @("20.000",  "-15.000", "-4.000") `
    @("-5.000",  "4.000",   "1.000")
)

# ---------------------------------------------------------------------
#  TEST 02: Fractional coefficients (example 2)
# ---------------------------------------------------------------------
Write-TestFile "input\t02_input.txt" (Format-Matrix `
    @(4, 7, 2.3) `
    @(2, 1, 1) `
    @(3, -2, -2.31)
)

Write-TestFile "expected\t02_expected.txt" (Format-Matrix `
    @("-0.009", "0.321",  "0.131") `
    @("0.212",  "-0.448", "0.017") `
    @("-0.194", "0.806",  "-0.278")
)

# ---------------------------------------------------------------------
#  TEST 03: Singular matrix - det = 0 (example 3)
# ---------------------------------------------------------------------
Write-TestFile "input\t03_input.txt" (Format-Matrix `
    @(1, 2, 3) `
    @(2, 4, 6) `
    @(1, 2, 3)
)

Write-TestFile "expected\t03_expected.txt" "Non-invertible$Crlf"

# ---------------------------------------------------------------------
#  TEST 04: Non-numeric value "a" (example 4)
# ---------------------------------------------------------------------
Write-TestFile "input\t04_input.txt" (Format-Matrix `
    @(1, 2, "a") `
    @(2, 4, 6) `
    @(1, 2, 3)
)

Write-TestFile "expected\t04_expected.txt" "Invalid matrix$Crlf"

# ---------------------------------------------------------------------
#  TEST 05: Partially numeric token "3abc"
# ---------------------------------------------------------------------
Write-TestFile "input\t05_input.txt" (Format-Matrix `
    @(1, 2, "3abc") `
    @(2, 4, 6) `
    @(1, 2, 3)
)

Write-TestFile "expected\t05_expected.txt" "Invalid matrix$Crlf"

# ---------------------------------------------------------------------
#  TEST 06: Only 2 rows (missing row)
# ---------------------------------------------------------------------
Write-TestFile "input\t06_input.txt" `
    ((Format-MatrixRow @(1, 2, 3)) + (Format-MatrixRow @(4, 5, 6)))

Write-TestFile "expected\t06_expected.txt" "Invalid matrix format$Crlf"

# ---------------------------------------------------------------------
#  TEST 07: 4 elements per row (extra column)
# ---------------------------------------------------------------------
Write-TestFile "input\t07_input.txt" (
    (Format-MatrixRow @(1, 2, 3, 4)) +
    (Format-MatrixRow @(5, 6, 7, 8)) +
    (Format-MatrixRow @(9, 10, 11, 12))
)

Write-TestFile "expected\t07_expected.txt" "Invalid matrix format$Crlf"

# ---------------------------------------------------------------------
#  TEST 08: 2 elements per row (missing column)
# ---------------------------------------------------------------------
Write-TestFile "input\t08_input.txt" (
    (Format-MatrixRow @(1, 2)) +
    (Format-MatrixRow @(3, 4)) +
    (Format-MatrixRow @(5, 6))
)

Write-TestFile "expected\t08_expected.txt" "Invalid matrix format$Crlf"

# ---------------------------------------------------------------------
#  TEST 09: Empty file
# ---------------------------------------------------------------------
Write-TestFile "input\t09_input.txt" ""

Write-TestFile "expected\t09_expected.txt" "Invalid matrix format$Crlf"

# ---------------------------------------------------------------------
#  TEST 10: Identity matrix - inverse equals itself
# ---------------------------------------------------------------------
Write-TestFile "input\t10_input.txt" (Format-Matrix `
    @(1, 0, 0) `
    @(0, 1, 0) `
    @(0, 0, 1)
)

Write-TestFile "expected\t10_expected.txt" (Format-Matrix `
    @("1.000", "0.000", "0.000") `
    @("0.000", "1.000", "0.000") `
    @("0.000", "0.000", "1.000")
)

# ---------------------------------------------------------------------
#  TEST 11: Diagonal matrix diag(2, 4, 5) -> diag(0.5, 0.25, 0.2)
# ---------------------------------------------------------------------
Write-TestFile "input\t11_input.txt" (Format-Matrix `
    @(2, 0, 0) `
    @(0, 4, 0) `
    @(0, 0, 5)
)

Write-TestFile "expected\t11_expected.txt" (Format-Matrix `
    @("0.500", "0.000", "0.000") `
    @("0.000", "0.250", "0.000") `
    @("0.000", "0.000", "0.200")
)

# ---------------------------------------------------------------------
#  TEST 12: All negative (except zeros), det = -1
# ---------------------------------------------------------------------
Write-TestFile "input\t12_input.txt" (Format-Matrix `
    @(-1, -2, -3) `
    @(0,  -1, -4) `
    @(-5, -6,  0)
)

Write-TestFile "expected\t12_expected.txt" (Format-Matrix `
    @("24.000",  "-18.000", "-5.000") `
    @("-20.000", "15.000",  "4.000") `
    @("5.000",   "-4.000",  "-1.000")
)

# ---------------------------------------------------------------------
#  TEST 13: Stdin via pipe (uses t01_input.txt)
# ---------------------------------------------------------------------
Write-TestFile "expected\t13_expected.txt" (Format-Matrix `
    @("-24.000", "18.000",  "5.000") `
    @("20.000",  "-15.000", "-4.000") `
    @("-5.000",  "4.000",   "1.000")
)

# ---------------------------------------------------------------------
#  TEST 14: Flag -h (help)
# ---------------------------------------------------------------------
$helpText = "Usage:${Crlf}${Tab}invert.exe${Tab}${Tab}${Tab}Read Matrix from stdin${Crlf}${Tab}invert.exe <file>${Tab}Read Matrix from file${Crlf}${Tab}invert.exe -h${Tab}${Tab}Show help${Crlf}"

Write-TestFile "expected\t14_expected.txt" $helpText

# ---------------------------------------------------------------------
#  TEST 15: Non-existent file
# ---------------------------------------------------------------------
Write-TestFile "expected\t15_expected.txt" "Failed to open file: nonexistent.txt$Crlf"

# ---------------------------------------------------------------------
#  TEST 16: Too many arguments
# ---------------------------------------------------------------------
Write-TestFile "expected\t16_expected.txt" "Too many arguments. Use -h for help.$Crlf"

#endregion

#region === SUMMARY ===

Write-Host ""
Write-Host "=======================================================" -ForegroundColor Green
Write-Host "  All test files created successfully!" -ForegroundColor Green
Write-Host "=======================================================" -ForegroundColor Green
Write-Host ""
Write-Host "  Base directory: $BaseDirectory"
Write-Host ""
Write-Host "  Created directories:"
Write-Host "    input\     - 12 input files"
Write-Host "    expected\  - 16 expected result files"
Write-Host "    output\    - empty (filled by run_tests.bat)"
Write-Host ""

#endregion