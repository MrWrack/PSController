@echo off
setlocal
cd /d "%~dp0\.."
echo ==========================================
echo PSController - PC test launcher
echo ==========================================
echo.
powershell -NoProfile -ExecutionPolicy Bypass -File tools\check-msvc.ps1
if errorlevel 1 (
  echo.
  echo Setup is not ready yet. Follow the message above.
  exit /b 2
)
echo.
echo Setup check passed.
echo Run tools\run-pc-smoke-test.bat from a Developer Command Prompt.
exit /b 0
