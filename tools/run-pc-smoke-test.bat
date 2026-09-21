@echo off
setlocal
cd /d "%~dp0\.."

echo ==========================================
echo PSController - PC smoke tests
echo ==========================================

where cl >nul 2>nul
if errorlevel 1 (
  echo [ERROR] Microsoft C/C++ compiler cl.exe was not found.
  echo Run this script from a Developer Command Prompt for VS 2022.
  exit /b 2
)

if not exist build mkdir build

echo [1/2] Build identity test...
cl /nologo /EHsc /W4 /std:c++14 tests\pc_smoke_test.cpp src\controller\hiddriver360\build_info.cpp /Fe:build\pscontroller_pc_smoke_test.exe
if errorlevel 1 exit /b 3
build\pscontroller_pc_smoke_test.exe
if errorlevel 1 exit /b 4

echo.
echo [2/2] Target entry contract test...
cl /nologo /EHsc /W4 /std:c++14 tests\target_entry_contract_test.cpp src\controller\hiddriver360\target_entry_contract.cpp src\controller\hiddriver360\first_xex_adapter.cpp src\controller\hiddriver360\retail17559_probe.cpp src\controller\hiddriver360\retail17559_probe_format.cpp /Fe:build\pscontroller_target_entry_test.exe
if errorlevel 1 (
  echo [FAIL] Target entry contract compilation failed.
  exit /b 5
)
build\pscontroller_target_entry_test.exe
if errorlevel 1 (
  echo [FAIL] Target entry contract test failed.
  exit /b 6
)

echo.
echo [OK] All PSController PC tests completed successfully.
exit /b 0
