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
set DST_DIR=/data/local/tmp/ring/test

adb push %TEST_EXECUTABLE_FILE% %DST_DIR%/%TARGET_TEST_FILENAME%
adb shell chmod 775 %DST_DIR%/%TARGET_TEST_FILENAME%
adb shell "%DST_DIR%/%TARGET_TEST_FILENAME% && touch %DST_DIR%/%SUCCEEDED_FILENAME%"
adb pull %DST_DIR%/%SUCCEEDED_FILENAME% TestResult\%SUCCEEDED_FILENAME%

if not exist TestResult\%SUCCEEDED_FILENAME% (
	goto :TEST_FAILED
) else (
	goto :TEST_SUCCEEDED
)

:Func_GetFileName
	set TARGET_TEST_FILENAME=%~nx1
exit /b

:TEST_SUCCEEDED
popd
endlocal
echo "TEST SUCCEEDED!!"
exit /b 0

:TEST_FAILED
popd
endlocal
echo "TEST FAILED!!"
exit /b -1
