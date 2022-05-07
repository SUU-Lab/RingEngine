@echo off
setlocal

echo ---------- vswhere ----------

set CURRENT_DIR=%~dp0
pushd %CURRENT_DIR%

set TARGET_DIR=%CURRENT_DIR%
set VSWHERE_VERSION=2.8.4
set VSWHERE_PATH=%TARGET_DIR%\vswhere

where /Q "vswhere.exe"
if not ERRORLEVEL 1 (
	goto :VSWHERE_INSTALLED
) else if exist %VSWHERE_PATH%\vswhere.exe (
	goto :VSWHERE_INSTALLED
) else if not exist %VSWHERE_PATH% (
	mkdir %VSWHERE_PATH%
)

bitsadmin /RawReturn /TRANSFER getfile ^
https://github.com/microsoft/vswhere/releases/download/%VSWHERE_VERSION%/vswhere.exe ^
%VSWHERE_PATH%\%vswhere.exe

set PATH=%VSWHERE_PATH%;%PATH%

:VSWHERE_INSTALLED
vswhere.exe -latest

popd
endlocal
