
:: error level 사용 하기

@echo off

pushd.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Commands that do NOT affect the ERRORLEVEL:
:: BREAK, ECHO, ENDLOCAL, FOR, IF, PAUSE, REM, RD/RMDIR, TITLE
::
:: Commands that will set but not clear an ERRORLEVEL:
:: CLS, GOTO, KEYS, POPD, SHIFT
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

dir xxx.txt

IF %ERRORLEVEL% EQU 0 (
	echo OK
) ELSE ( 
	echo ERROR FAILED &color 0A
)

dir xxx.txt
IF NOT %ERRORLEVEL% == 0 goto ERROR

goto OK


:ERROR
echo %ERRORLEVEL%
echo not found file !!!
goto QUIT


:OK
echo found file !!!
goto QUIT


:QUIT
popd.



set source_path="K:\my-project\TestCode\TestDOSBatch\Batch\"
cd /d %source_path%

FOR %%t IN (target1 target2 target3) DO (	
	IF EXIST %%t (
		set "ERRORLEVEL=1"
	)
	
	IF NOT %ERRORLEVEL%==0 ( 
		echo FAILURE: %ERRORLEVEL%
		exit /b 1
	) ELSE (
		echo SUCCESS: %ERRORLEVEL%
	)
)

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Jenkins Job 실패 처리할 경우
:: Windows Batch Command 
:: exit /b 1
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

pause

