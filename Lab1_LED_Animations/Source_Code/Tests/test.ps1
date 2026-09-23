param([string]$Compiler = 'gcc')
$ErrorActionPreference = 'Stop'
Push-Location $PSScriptRoot
try {
$outputDir = '..\..\Firmware\host-tests'
New-Item -ItemType Directory -Force -Path $outputDir | Out-Null
$exe = Join-Path $outputDir 'test_exercises.exe'
$sources = @(Get-ChildItem -Path '..\Src\exercise*.c' | ForEach-Object { '..\Src\' + $_.Name })
& $Compiler -std=c11 -Wall -Wextra -Werror -I . -I '..\Inc' 'test_exercises.c' @sources -o $exe
if ($LASTEXITCODE) { throw 'Host test compilation failed' }
& $exe
if ($LASTEXITCODE) { throw 'Host behavioral tests failed' }
} finally { Pop-Location }
