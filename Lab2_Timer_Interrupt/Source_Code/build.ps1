param(
    [string]$FirmwareRoot = "$env:USERPROFILE\STM32Cube\Repository\STM32Cube_FW_F1_V1.8.7",
    [string]$CompilerBin = '',
    [int[]]$Exercises = (1..10),
    [int]$TickMs = 10,
    [int]$ScanSlotMs = 250,
    [int]$MatrixSlotMs = 10,
    [string]$OutputDirectory = ''
)
$ErrorActionPreference = 'Stop'
if (-not $CompilerBin) {
    $candidate = Get-ChildItem -Path 'C:\ST\STM32CubeIDE_*\STM32CubeIDE\plugins\com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.*\tools\bin\arm-none-eabi-gcc.exe' | Select-Object -First 1
    if (-not $candidate) { throw 'Pass -CompilerBin with the ARM GCC bin directory.' }
    $CompilerBin = $candidate.DirectoryName
}
if ($TickMs -lt 1 -or $TickMs -gt 65 -or $ScanSlotMs -lt $TickMs -or $MatrixSlotMs -lt $TickMs) {
    throw 'TickMs must be 1..65; both scan slots must be >= TickMs.'
}
$gcc = Join-Path $CompilerBin 'arm-none-eabi-gcc.exe'
$objcopy = Join-Path $CompilerBin 'arm-none-eabi-objcopy.exe'
$size = Join-Path $CompilerBin 'arm-none-eabi-size.exe'
$hal = Join-Path $FirmwareRoot 'Drivers\STM32F1xx_HAL_Driver'
$cmsis = Join-Path $FirmwareRoot 'Drivers\CMSIS'
$device = Join-Path $cmsis 'Device\ST\STM32F1xx'
$out = if ($OutputDirectory) { $OutputDirectory } else { Join-Path $PSScriptRoot '..\Firmware' }
New-Item -ItemType Directory -Force -Path $out | Out-Null
$sources = @(Get-ChildItem -LiteralPath (Join-Path $PSScriptRoot 'Src') -Filter '*.c' | ForEach-Object FullName)
$sources += Join-Path $device 'Source\Templates\system_stm32f1xx.c'
$sources += Join-Path $device 'Source\Templates\gcc\startup_stm32f103x6.s'
foreach ($name in @('hal','hal_rcc','hal_rcc_ex','hal_gpio','hal_gpio_ex','hal_cortex','hal_flash','hal_flash_ex','hal_pwr','hal_dma','hal_tim','hal_tim_ex')) {
    $sources += Join-Path $hal ('Src\stm32f1xx_' + $name + '.c')
}
foreach ($source in $sources) {
    if (-not (Test-Path -LiteralPath $source)) { throw "Missing source: $source" }
}
foreach ($exercise in $Exercises) {
    if ($exercise -lt 1 -or $exercise -gt 10) { throw 'Exercise must be 1..10.' }
    $stem = Join-Path $out ('exercise{0:D2}' -f $exercise)
    $compileArgs = @('-mcpu=cortex-m3','-mthumb','-std=c11','-Os','-g3','-Wall','-Wextra','-Werror','-ffunction-sections','-fdata-sections','-DSTM32F103x6','-DUSE_HAL_DRIVER',"-DLAB2_ACTIVE_EXERCISE=$exercise","-DLAB2_TIMER_TICK_MS=$TickMs","-DLAB2_SCAN_SLOT_MS=$ScanSlotMs","-DLAB2_MATRIX_SLOT_MS=$MatrixSlotMs",'-I',(Join-Path $PSScriptRoot 'Inc'),'-I',(Join-Path $hal 'Inc'),'-I',(Join-Path $cmsis 'Include'),'-I',(Join-Path $device 'Include'),'-T',(Join-Path $PSScriptRoot 'STM32F103C6.ld'),'--specs=nano.specs','--specs=nosys.specs','-Wl,--gc-sections','-o',"$stem.elf") + $sources
    & $gcc @compileArgs
    if ($LASTEXITCODE) { throw "Build failed for exercise $exercise" }
    & $objcopy -O ihex "$stem.elf" "$stem.hex"
    if ($LASTEXITCODE) { throw 'HEX conversion failed' }
    & $size "$stem.elf"
    if ($LASTEXITCODE) { throw 'ELF size check failed' }
}
