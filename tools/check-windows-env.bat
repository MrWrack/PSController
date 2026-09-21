@echo off
setlocal
echo PSController - Windows environment check
echo.
where git >nul 2>nul
if errorlevel 1 (echo [MISSING] Git) else (echo [OK] Git)
where cl >nul 2>nul
if errorlevel 1 (
  echo [INFO] Microsoft C/C++ compiler is not in PATH.
  echo        This is fine until the PC development environment is installed.
) else (
  echo [OK] C/C++ compiler found:
  cl 2>&1 | findstr /I "Version"
)
echo.
echo Xbox 360 target compiler/XEX tools are intentionally not auto-detected
echo until the exact compatible build environment is selected.
echo No proprietary SDK files should be copied into this repository.
echo.
pause
