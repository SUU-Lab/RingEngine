@echo off
setlocal

set CURRENT_DIR=%~dp0
pushd %CURRENT_DIR%

if not exist TestResult (
	md TestResult
)

set TEST_EXECUTABLE_FILE=%1
set TARGET_TEST_FILENAME=%1
call :Func_GetFileName %TARGET_TEST_FILENAME%

set SUCCEEDED_FILENAME=%TARGET_TEST_FILENAME%_SUCCEEDED.txt
set DST_DIR=/data/local/tmp/ring/%TARGET_TEST_FILENAME%


@shift

if "%1"=="" goto :ARGS_END
set ARGS=%1

@shift

:ARGS_SHIFT
if "%1"=="" goto :ARGS_END
set ARGS=%ARGS% %1
@shift
goto :ARGS_SHIFT
:ARGS_END


adb push %TEST_EXECUTABLE_FILE% %DST_DIR%/%TARGET_TEST_FILENAME% > nul
adb shell "cd %DST_DIR% && chmod 775 ./%TARGET_TEST_FILENAME%" > nul
adb shell "cd %DST_DIR% && ./%TARGET_TEST_FILENAME% %ARGS% > output.txt && touch %SUCCEEDED_FILENAME%" > nul
adb pull %DST_DIR% TestResult > nul
adb shell rm -rf %DST_DIR% > nul

type TestResult\%TARGET_TEST_FILENAME%\output.txt

if not exist TestResult\%TARGET_TEST_FILENAME%\%SUCCEEDED_FILENAME% (
	goto :TEST_FAILED
) else (
	goto :TEST_SUCCEEDED
)

:Func_GetFileName
	set TARGET_TEST_FILENAME=%~nx1
exit /b

:TEST_SUCCEEDED
del /Q TestResult\%TARGET_TEST_FILENAME%
popd
endlocal
exit /b 0

:TEST_FAILED
del /Q TestResult\%TARGET_TEST_FILENAME%
popd
endlocal
exit /b -1
