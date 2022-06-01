@echo off
setlocal

set CURRENT_DIR=%~dp0
pushd %CURRENT_DIR%

set TEST_EXECUTABLE_FILE=%1
set TARGET_TEST_FILENAME=%1
call :Func_GetFileName %TARGET_TEST_FILENAME%
set TEST_RUNNER_FILENAME=%TARGET_TEST_FILENAME%.bat

echo @rem #------------------------------------------ > %TEST_RUNNER_FILENAME%
echo @rem # %TEST_RUNNER_FILENAME% >> %TEST_RUNNER_FILENAME%
echo @rem # This is auto generated file. >> %TEST_RUNNER_FILENAME%
echo @rem #------------------------------------------ >> %TEST_RUNNER_FILENAME%

echo. >> %TEST_RUNNER_FILENAME%
echo @echo off >> %TEST_RUNNER_FILENAME%
echo setlocal >> %TEST_RUNNER_FILENAME%

echo. >> %TEST_RUNNER_FILENAME%
echo set CURRENT_DIR=%%~dp0 >> %TEST_RUNNER_FILENAME%
echo pushd %%CURRENT_DIR%% >> %TEST_RUNNER_FILENAME%

echo. >> %TEST_RUNNER_FILENAME%
echo call TestRunner.bat %TEST_EXECUTABLE_FILE% >> %TEST_RUNNER_FILENAME%

echo. >> %TEST_RUNNER_FILENAME%
echo if %%ERRORLEVEL%% neq 0 ( goto :TEST_FAILED ) else ( goto :TEST_SUCCEEDED ) >> %TEST_RUNNER_FILENAME%

echo. >> %TEST_RUNNER_FILENAME%
echo :TEST_FAILED >> %TEST_RUNNER_FILENAME%
echo popd >> %TEST_RUNNER_FILENAME%
echo endlocal >> %TEST_RUNNER_FILENAME%
echo exit /b -1 >> %TEST_RUNNER_FILENAME%

echo. >> %TEST_RUNNER_FILENAME%
echo :TEST_SUCCEEDED >> %TEST_RUNNER_FILENAME%
echo popd >> %TEST_RUNNER_FILENAME%
echo endlocal >> %TEST_RUNNER_FILENAME%
echo exit /b 0 >> %TEST_RUNNER_FILENAME%

goto :END

:Func_GetFileName
	set TARGET_TEST_FILENAME=%~nx1
exit /b

:END
popd
endlocal

