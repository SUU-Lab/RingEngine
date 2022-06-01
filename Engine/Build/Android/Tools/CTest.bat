@echo off
setlocal

set CURRENT_DIR=%~dp0
pushd %CURRENT_DIR%\..\%1

set BUILD_DIR=

for /f %%A in (cmake_binary_dir.txt) do (
        set BUILD_DIR=%BUILD_DIR%%%A
)

pushd %BUILD_DIR%
echo %BUILD_DIR%

shift
ctest %*

if %ERRORLEVEL% equ 0 (
	goto :TEST_SUCCEEDED
) else (
	goto :TEST_FAILED
)

:TEST_SUCCEEDED
popd
popd
endlocal
exit /b 0

:TEST_FAILED
popd
popd
endlocal
exit /b -1
