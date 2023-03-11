
:: cmd.exe 에서 키보드 문자 입력 받기.

@echo off

setlocal

::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:LOOP
	set /p YN= (yes/no)?

	:: /i 대소문자 구분 무시 !!!
	if /i "%YN%" == "yes" goto YES
	if /i "%YN%" == "no" goto NO

	goto LOOP
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

:YES
	echo YES
	goto QUIT

:NO
	echo NO
	goto QUIT

:QUIT
	endlocal
	pause