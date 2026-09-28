param([string]$Compiler = 'gcc', [int[]]$Exercises = (1..10))
$ErrorActionPreference = 'Stop'
Push-Location $PSScriptRoot
try {
    $outputDir = '..\..\Firmware\host-tests'
    New-Item -ItemType Directory -Force -Path $outputDir | Out-Null
    $sources = @(Get-ChildItem -Path '..\Src\*.c' |
        Where-Object { $_.Name -ne 'main.c' -and $_.Name -ne 'stm32f1xx_it.c' } |
        ForEach-Object { '..\Src\' + $_.Name })
    foreach ($exercise in $Exercises) {
        if ($exercise -lt 1 -or $exercise -gt 10) { throw 'Exercise must be 1..10.' }
        $exe = Join-Path $outputDir ("exercise{0:D2}_test.exe" -f $exercise)
        & $Compiler -std=c11 -Wall -Wextra -Werror "-DLAB2_ACTIVE_EXERCISE=$exercise" -I . -I '..\Inc' 'test_lab2.c' @sources -o $exe
        if ($LASTEXITCODE) { throw "Host compile failed: exercise $exercise" }
        & $exe
        if ($LASTEXITCODE) { throw "Host test failed: exercise $exercise" }
    }
} finally { Pop-Location }
