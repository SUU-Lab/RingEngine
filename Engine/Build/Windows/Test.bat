@echo off
setlocal

set CURRENT_DIR=%~dp0
pushd %CURRENT_DIR%

@rem Add subfolders to the path
for /f "usebackq delims=" %%A in (`dir /b /a:d`) do (
	call :Func_SetPath %CURRENT_DIR%%%A
)

set RING_ENGINE_SOURCE_ROOT=..\..\Source\

set TEST_RESULT=1

@rem %1 : platform x86 x64
@rem %2 : configuration Debug Release
@rem %3 : cxx_standard 14 17 20
if "%1" == "" if "%2" == "" if "%3" == "" (
	call :Func_Test x86 Debug 20
	call :Func_Test x86 Release 20
	call :Func_Test x64 Debug 20
	call :Func_Test x64 Release 20
)
if not "%1" == "" if not "%2" == "" if not "%3" == "" (
	call :Func_Test %1 %2 %3
)

if %TEST_RESULT% equ 0 (
	goto :TEST_SUCCEEDED
) else (
	goto :TEST_FAILED
)

@rem ########## Func_Test ##########
:Func_Test

echo ---------- Test %1 %2 ----------
set BUILD_TARGET=%1
set BUILD_CONFIGURATION=%2
set CXX_STANDARD=%3
set BUILD_DIR=build\%BUILD_TARGET%\%BUILD_CONFIGURATION%\%CXX_STANDARD%

pushd %BUILD_DIR%

echo ---------- Testing ----------
ctest.exe -j 4 -C %BUILD_CONFIGURATION%

if %ERRORLEVEL% equ 0 (
	set TEST_RESULT=0
)

popd

exit /b


@rem ########## Func_SetPath ##########
:Func_SetPath

set PATH=%1;%PATH%

exit /b


:TEST_FAILED
popd
endlocal
echo "TEST FAILED!!"
exit /b -1

:TEST_SUCCEEDED
popd
endlocal
echo "TEST SUCCEEDED!!"
exit /b 0
