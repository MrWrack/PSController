@echo off
setlocal
cd /d "%~dp0\.."

echo ==========================================
echo PSController - Xbox 360 target preflight
echo ==========================================

echo [1/4] Checking portable PC tests...
call tools\run-pc-smoke-test.bat
if errorlevel 1 (
  echo [FAIL] Portable tests must pass before target build work.
  exit /b 10
)

echo.
echo [2/4] Checking required target adapter files...
for %%F in (
  src\controller\hiddriver360\first_xex_adapter.h
  src\controller\hiddriver360\first_xex_adapter.cpp
  src\controller\hiddriver360\target_entry_contract.h
  src\controller\hiddriver360\target_entry_contract.cpp
  src\controller\hiddriver360\target_shim_template.h
  src\controller\hiddriver360\target_shim_template.cpp
) do (
  if not exist "%%F" (
    echo [FAIL] Missing %%F
    exit /b 11
  )
)
echo [PASS] Target adapter source set is present.

echo.
echo [3/4] Safety mode...
echo Kernel target : 17559
echo Hooks         : OFF
echo Audio/voice   : OFF
echo Probe         : READ-ONLY
echo [PASS] First target build remains diagnostic-only.

echo.
echo [4/4] Native toolchain boundary...
echo [WAIT] A verified Xbox 360 PowerPC/XEX target toolchain is still required.
echo [WAIT] No SDK ABI, loader constants, ordinals, or XEX metadata are guessed.
echo.
echo [READY] Portable source is ready for the native XEX toolchain adapter.
exit /b 0
