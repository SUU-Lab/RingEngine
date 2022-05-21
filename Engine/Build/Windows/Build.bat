@echo off
setlocal

set CURRENT_DIR=%~dp0
pushd %CURRENT_DIR%

@rem Add subfolders to the path
for /f "usebackq delims=" %%A in (`dir /b /a:d`) do (
	call :Func_SetPath %CURRENT_DIR%%%A
)

set RING_ENGINE_SOURCE_ROOT=..\..\Source\

for /f "usebackq delims=" %%A in (`vswhere.exe -products * -requires Microsoft.Component.MSBuild -property installationPath -latest`) do (
        set VS_INSTALL_PATH=%%A
)
echo VS_INSTALL_PATH=%VS_INSTALL_PATH%

set BUILD_RESULT=1

@rem %1 : platform x86 x64
@rem %2 : configuration Debug Release
@rem %3 : cxx_standard 17 20
if "%1" == "" if "%2" == "" if "%3" == "" (
	call :Func_Build x86 Debug 20
	call :Func_Build x86 Release 20
	call :Func_Build x64 Debug 20
	call :Func_Build x64 Release 20
)
if not "%1" == "" if not "%2" == "" if not "%3" == "" (
	call :Func_Build %1 %2 %3
)

if %BUILD_RESULT% equ 0 (
	goto :BUILD_SUCCEEDED
) else (
	goto :BUILD_FAILED
)

@rem ########## Func_Build ##########
:Func_Build

setlocal

echo ---------- Build %1 %2 ----------
set BUILD_TARGET=%1
set BUILD_CONFIGURATION=%2
set CXX_STANDARD=%3
set BUILD_DIR=build\%BUILD_TARGET%\%BUILD_CONFIGURATION%\%CXX_STANDARD%

if not exist %BUILD_DIR% (
	md %BUILD_DIR%
)

echo ---------- Call vcvarsall.bat ----------
call "%VS_INSTALL_PATH%\VC\Auxiliary\Build\vcvarsall.bat" %BUILD_TARGET%

echo ---------- Generating ----------
cmake.exe ^
-GNinja ^
-H%RING_ENGINE_SOURCE_ROOT% ^
-B%BUILD_DIR% ^
-DCMAKE_CXX_STANDARD=%CXX_STANDARD% ^
-DCMAKE_BUILD_TYPE=%BUILD_CONFIGURATION%

if %ERRORLEVEL% neq 0 (
	goto :Func_Build_FAILED
)

echo ---------- Building ----------
cmake.exe --build %BUILD_DIR%

if %ERRORLEVEL% neq 0 (
	goto :Func_Build_FAILED
)

:Func_Build_SUCCEEDED
endlocal
set BUILD_RESULT=0
exit /b

:Func_Build_FAILED
endlocal
exit /b


@rem ########## Func_SetPath ##########
:Func_SetPath

set PATH=%1;%PATH%

exit /b

:BUILD_SUCCEEDED
popd
endlocal
echo "BUILD SUCCEEDED!!"
exit /b 0

:BUILD_FAILED
popd
endlocal
echo "BUILD FAILED!!"
exit /b -1
