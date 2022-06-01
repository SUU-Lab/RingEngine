@rem #------------------------------------------ 
@rem # Ring_Runtime_Test.bat 
@rem # This is auto generated file. 
@rem #------------------------------------------ 
 
@echo off 
setlocal 
 
set CURRENT_DIR=%~dp0 
pushd %CURRENT_DIR% 
 
call TestRunner.bat E:\GitHub\SUU-Lab\RingEngine\Engine\Build\Android\RingRuntimeApp\app\build\intermediates\cxx\Debug\2x373e6x\obj\arm64-v8a/Ring_Runtime_Test 
 
if %ERRORLEVEL% neq 0 ( goto :TEST_FAILED ) else ( goto :TEST_SUCCEEDED ) 
 
:TEST_FAILED 
popd 
endlocal 
exit /b -1 
 
:TEST_SUCCEEDED 
popd 
endlocal 
exit /b 0 
