$ErrorActionPreference = "Stop"
Set-Location (Join-Path $PSScriptRoot "..")

Write-Host "PSController - PC setup check"
$pf86 = [Environment]::GetFolderPath("ProgramFilesX86")
$vswhere = Join-Path $pf86 "Microsoft Visual Studio\Installer\vswhere.exe"
if (-not (Test-Path $vswhere)) {
  Write-Host "[MISSING] Visual Studio Installer / Build Tools"
  Write-Host "Install Visual Studio Build Tools and select: Desktop development with C++"
  exit 2
}
$install = & $vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
if (-not $install) {
  Write-Host "[MISSING] MSVC C++ build tools"
  Write-Host "Open Visual Studio Installer and add: Desktop development with C++"
  exit 3
}
$devcmd = Join-Path $install "Common7\Tools\VsDevCmd.bat"
if (-not (Test-Path $devcmd)) { Write-Host "[ERROR] VsDevCmd.bat was not found."; exit 4 }
Write-Host "[OK] MSVC build environment found:"
Write-Host $install
Write-Host ""
Write-Host "Next: run tools\run-pc-smoke-test.bat from a Developer Command Prompt."
exit 0
