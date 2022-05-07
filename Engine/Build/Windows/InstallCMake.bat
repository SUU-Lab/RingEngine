@echo off
setlocal

echo ---------- CMake ----------
set CURRENT_DIR=%~dp0
pushd %CURRENT_DIR%

set TARGET_DIR=%CURRENT_DIR%
set CMAKE_VERSION=3.23.1
set CMAKE_ARCHIVE_NAME=cmake-%CMAKE_VERSION%-windows-x86_64
set CMAKE_PATH=%TARGET_DIR%\CMake\bin

where /Q "cmake.exe"
if not ERRORLEVEL 1 (
	goto :CMAKE_INSTALLED
) else if exist %CMAKE_PATH%\cmake.exe (
	goto :CMAKE_INSTALLED
)

bitsadmin /RawReturn /TRANSFER getfile ^
https://github.com/Kitware/CMake/releases/download/v%CMAKE_VERSION%/%CMAKE_ARCHIVE_NAME%.zip ^
%TARGET_DIR%\cmake.zip

powershell Expand-Archive -Path cmake.zip -DestinationPath %TARGET_DIR%

rename %TARGET_DIR%\%CMAKE_ARCHIVE_NAME% CMake

del cmake.zip

set PATH=%CMAKE_PATH%;%PATH%

:CMAKE_INSTALLED
cmake.exe --version

popd
endlocal
