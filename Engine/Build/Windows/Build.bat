@echo off
setlocal

set CURRENT_DIR=%~dp0
pushd %CURRENT_DIR%

@rem サブフォルダにパスを通す
for /f "usebackq delims=" %%A in (`dir /b /a:d`) do (
	call :Func_SetPath %CURRENT_DIR%%%A
)

set RING_ENGINE_SOURCE_ROOT=..\..\Source\

for /f "usebackq delims=" %%A in (`vswhere.exe -products * -requires Microsoft.Component.MSBuild -property installationPath -latest`) do (
        set VS_INSTALL_PATH=%%A
)
echo VS_INSTALL_PATH=%VS_INSTALL_PATH%

@rem %1 : platform x86 x64
@rem %2 : configuration Debug Release
if "%1" == "" if "%2" == "" (
	call :Func_Build x86 Debug
	call :Func_Build x86 Release
	call :Func_Build x64 Debug
	call :Func_Build x64 Release
)
if not "%1" == "" if not "%2" == "" (
	call :Func_Build %1 %2
)


goto :BUILD_END


@rem ########## Func_Build ##########
:Func_Build

setlocal

echo ---------- Build %1 %2 ----------
set BUILD_TARGET=%1
set BUILD_CONFIGURATION=%2
set BUILD_DIR=build\%BUILD_TARGET%\%BUILD_CONFIGURATION%

if not exist %BUILD_DIR% (
	md %BUILD_DIR%
)

echo ---------- Call vcvarsall.bat ----------
call "%VS_INSTALL_PATH%\VC\Auxiliary\Build\vcvarsall.bat" %BUILD_TARGET%

echo ---------- Generating ----------
cmake.exe ^
-H%RING_ENGINE_SOURCE_ROOT% ^
-GNinja ^
-DCMAKE_BUILD_TYPE=%BUILD_CONFIGURATION% ^
-B%BUILD_DIR%

echo ---------- Building ----------
cmake.exe --build %BUILD_DIR%

endlocal

exit /b


@rem ########## Func_SetPath ##########
:Func_SetPath

set PATH=%1;%PATH%

exit /b


:BUILD_END
popd
endlocal
