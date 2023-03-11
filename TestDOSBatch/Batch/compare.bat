
:: Equal, Great than, less than 비교문 사용 하기.

@echo off

rem 비교문 목록
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: 구문     의미
:: EQU      equal
:: NEQ      not equal
:: LSS      less than
:: LEQ      less than or equal
:: GTR      greater than
:: GEQ      greater than or equal
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

:Start2
	cls
	goto Start

:Start
	title Frequently Used Websites
	echo Please select a website from the list
	echo with the corresponding key
	echo --------------------------------------
	echo [1] Google
	echo [2] Wikipedia
	echo [3] Facebook
	echo [4] Youtube
	echo [5] Yahoo
	echo [6] Exit
	
	set input=
	set /p input= choice:
	if %input% equ 1 goto Z if NOT goto Start2
	if %input% equ 2 goto X if NOT goto Start2
	if %input% equ 3 goto C if NOT goto Start2
	if %input% equ 4 goto V if NOT goto Start2
	if %input% equ 5 goto B if NOT goto Start2
	if %input% equ 6 goto E if NOT goto Start2
	if %input% geq 7 goto N

:Z
	cls
	echo You have selected Google
	pause
	start www.google.com
	goto :Start2
	
:X
	cls
	echo You have selected Wikipedia
	pause
	start www.wikipedia.com
	goto :Start2

:C
	cls
	echo You have selected Facebook
	pause
	start www.facebook.com
	goto :Start2

:V
	cls
	echo You have selected Youtube
	pause
	start www.youtube.com
	goto :Start2
	
:B
	cls
	echo You have selected Yahoo
	pause
	start www.Yahoo.com
	goto :Start2
	
:E
	echo You have exit
	goto :eof

:N
	cls
	echo Invalid Selection! Try again
	pause
	goto :Start2
