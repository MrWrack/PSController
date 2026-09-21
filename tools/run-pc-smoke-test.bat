@echo off
setlocal
cd /d "%~dp0\.."

echo ==========================================
echo PSController - PC smoke test
echo ==========================================

where cl >nul 2>nul
if errorlevel 1 (
  echo [ERROR] Microsoft C/C++ compiler ^(cl.exe^) was not found.
  echo Install Visual Studio Build Tools with Desktop development with C++,
  echo then run this script from a Developer Command Prompt.
  exit /b 2
)

if not exist build mkdir build

cl /nologo /EHsc /W4 /std:c++14 ^
  tests\pc_smoke_test.cpp ^
  src\controller\hiddriver360\build_info.cpp ^
  /Fe:build\pscontroller_pc_smoke_test.exe
if errorlevel 1 (
  echo [FAIL] Compilation failed.
  exit /b 3
)

echo.
build\pscontroller_pc_smoke_test.exe
if errorlevel 1 (
  echo [FAIL] Smoke test failed.
  exit /b 4
)

echo.
echo [OK] PC smoke test completed successfully.
exit /b 0
