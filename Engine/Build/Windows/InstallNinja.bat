@echo off
setlocal

echo ---------- Ninja ----------

set CURRENT_DIR=%~dp0
pushd %CURRENT_DIR%

set TARGET_DIR=%CURRENT_DIR%
set NINJA_VERSION=1.10.2
set NINJA_PATH=%TARGET_DIR%\Ninja

where /Q "ninja.exe"
if not ERRORLEVEL 1 (
	goto :NINJA_INSTALLED
) else if exist %NINJA_PATH%\ninja.exe (
	goto :NINJA_INSTALLED
) else if not exist %NINJA_PATH% (
	mkdir %NINJA_PATH%
)

pushd %NINJA_PATH%

bitsadmin /RawReturn /TRANSFER getfile ^
https://github.com/ninja-build/ninja/releases/download/v%NINJA_VERSION%/ninja-win.zip ^
%NINJA_PATH%\Ninja.zip

powershell Expand-Archive -Path Ninja.zip -DestinationPath %NINJA_PATH%

del Ninja.zip

popd

set PATH=%NINJA_PATH%;%PATH%

:NINJA_INSTALLED
ninja.exe --version

popd
endlocal
