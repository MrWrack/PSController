@echo off
setlocal
set CFG=config\toolchain.local.ini
echo PSController - target toolchain configuration
echo.
if not exist "%CFG%" (
  echo [NOT CONFIGURED] %CFG%
  echo Copy config\toolchain.example.ini to %CFG%
  echo and fill it only with paths/settings from your compatible build environment.
  exit /b 2
)
findstr /B /C:"kernel=17559" "%CFG%" >nul || (
  echo [ERROR] Target kernel must be 17559 for the first test.
  exit /b 3
)
findstr /B /C:"mode=diagnostic-only" "%CFG%" >nul || (
  echo [ERROR] First test must remain diagnostic-only.
  exit /b 4
)
echo [OK] Local target manifest found.
echo [OK] First-test safety settings present.
echo.
echo This validator does not invoke proprietary target tools.
exit /b 0
