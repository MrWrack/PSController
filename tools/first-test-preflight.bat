@echo off
setlocal
echo ==========================================
echo PSController - first test preflight
echo ==========================================
echo Target kernel : 17559
echo Mode          : diagnostic-only
echo HID hooks     : disabled
echo Audio         : disabled
echo.
where git >nul 2>nul
if errorlevel 1 (
  echo [MISSING] Git
) else (
  echo [OK] Git
)
where cl >nul 2>nul
if errorlevel 1 (
  echo [INFO] C/C++ compiler not detected in PATH
) else (
  echo [OK] C/C++ compiler detected
)
echo.
echo This check does NOT build an XEX.
echo Xbox target toolchain validation comes next.
pause
