
:: Color 사용 하기

@echo off

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Sets the default console foreground and background colours.
::
:: COLOR [background][foreground]
::
:: 0 = Black       8 = Gray
:: 1 = Blue        9 = Light Blue
:: 2 = Green       A = Light Green
:: 3 = Aqua        B = Light Aqua
:: 4 = Red         C = Light Red
:: 5 = Purple      D = Light Purple
:: 6 = Yellow      E = Light Yellow
:: 7 = White       F = Bright White
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Color 0F

echo Test


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Echo Color 
::
:: echo -e "\033[COLOR1;COLOR2m sample text\033[0m"
:: 
:: [ TEXT ATTRIBUTES ]
:: ANSI CODE      Meaning
::     0          Normal Characters
::     1          Bold Characters
::     4          Underlined Characters
::     5          Blinking Characters
::     7          Reverse video Characters
::
:: [ COLORS ]
:: Bold off	  Color	   		Bold on	   	Color
:: 0;30	      Balck	   		1;30		Dark Gray
:: 0;31	      Red	   		1;31		Dark Red
:: 0;32	      Green	   		1;32		Dark Green
:: 0;33	      Brown	   		1;33		Yellow
:: 0;34	      Blue	   		1;34		Dark Blue
:: 0;35	      Magenta  		1;35		Dark Magenta
:: 0;36	      Cyan	   		1;30		Dark Cyan
:: 0;37	      Light Gray	1;30		White
::
::
:: Color	Foreground	Background
:: black	30			40
:: red		31			41
:: green	32			42
:: yellow	33			43
:: blue		34			44
:: magenta	35			45
:: cyan		36			46
:: white	37			47
::
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
echo -e "\033[COLOR1;COLOR2m sample text\033[0m"
echo -e '\E[47;34m'"\033[1mE\033[0m"
echo -e "\033[COLORm Sample text"
:: printf "\e[COLORm sample text\n"
echo -e "\033[32m Hello World"
:: printf "\e[32m Hello World"

echo -e "\033[40;37m Hello World\033[0m"
echo -e "\033[40;37;7m Hello World\033[0m"
echo -e "\033[33;44m Yellow text on blue background\033[0m"
echo -e "\033[1;33;44m Bold yellow text on blue background\033[0m"
echo -e "\033[1;4;33;44mBold yellow underlined text on blue background\033[0m"

:: This script echoes colors and codes
echo -e "\n\033[4;31mLight Colors\033[0m  \t\t\033[1;4;31mDark Colors\033[0m"
 
echo -e "\e[0;30;47m Black    \e[0m 0;30m \t\e[1;30;40m Dark Gray  \e[0m 1;30m"
echo -e "\e[0;31;47m Red      \e[0m 0;31m \t\e[1;31;40m Dark Red   \e[0m 1;31m"
echo -e "\e[0;32;47m Green    \e[0m 0;32m \t\e[1;32;40m Dark Green \e[0m 1;32m"
echo -e "\e[0;33;47m Brown    \e[0m 0;33m \t\e[1;33;40m Yellow     \e[0m 1;33m"
echo -e "\e[0;34;47m Blue     \e[0m 0;34m \t\e[1;34;40m Dark Blue  \e[0m 1;34m"
echo -e "\e[0;35;47m Magenta  \e[0m 0;35m \t\e[1;35;40m DarkMagenta\e[0m 1;35m"
echo -e "\e[0;36;47m Cyan     \e[0m 0;36m \t\e[1;36;40m Dark Cyan  \e[0m 1;36m"
echo -e "\e[0;37;47m LightGray\e[0m 0;37m \t\e[1;37;40m White      \e[0m 1;37m"




:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Echo color example
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

@echo off
setlocal

call :Echo.Color.Init

goto main

:Echo.Color %1=Color %2=Str [%3=/n]
setlocal enableDelayedExpansion
set "str=%~2"
:Echo.Color.2
:# Replace path separators in the string, so that the final path still refers to the current path.
set "str=a%ECHO.DEL%!str:\=a%ECHO.DEL%\..\%ECHO.DEL%%ECHO.DEL%%ECHO.DEL%!"
set "str=!str:/=a%ECHO.DEL%/..\%ECHO.DEL%%ECHO.DEL%%ECHO.DEL%!"
set "str=!str:"=\"!"
:# Go to the script directory and search for the trailing -
pushd "%ECHO.DIR%"
findstr /p /r /a:%~1 "^^-" "!str!\..\!ECHO.FILE!" nul
popd
:# Remove the name of this script from the output. (Dependant on its length.)
for /l %%n in (1,1,12) do if not "!ECHO.FILE:~%%n!"=="" <nul set /p "=%ECHO.DEL%"
:# Remove the other unwanted characters "\..\: -"
<nul set /p "=%ECHO.DEL%%ECHO.DEL%%ECHO.DEL%%ECHO.DEL%%ECHO.DEL%%ECHO.DEL%%ECHO.DEL%"
:# Append the optional CRLF
if not "%~3"=="" echo.
endlocal & goto :eof

:Echo.Color.Var %1=Color %2=StrVar [%3=/n]
if not defined %~2 goto :eof
setlocal enableDelayedExpansion
set "str=!%~2!"
goto :Echo.Color.2

:Echo.Color.Init
set "ECHO.COLOR=call :Echo.Color"
set "ECHO.DIR=%~dp0"
set "ECHO.FILE=%~nx0"
set "ECHO.FULL=%ECHO.DIR%%ECHO.FILE%"

:# Use prompt to store a backspace into a variable. (Actually backspace+space+backspace)
for /F "tokens=1 delims=#" %%a in ('"prompt #$H# & echo on & for %%b in (1) do rem"') do set "ECHO.DEL=%%a"
goto :eof

:main
call :Echo.Color 0a "a"
call :Echo.Color 0b "b"
set "txt=^" & call :Echo.Color.Var 0c txt
call :Echo.Color 0d "<"
call :Echo.Color 0e ">"
call :Echo.Color 0f "&"
call :Echo.Color 1a "|"
call :Echo.Color 1b " "
call :Echo.Color 1c "%%%%"
call :Echo.Color 1d ^"""
call :Echo.Color 1e "*"
call :Echo.Color 1f "?"

:# call :Echo.Color 2a "!"
call :Echo.Color 2b "."
call :Echo.Color 2c ".."
call :Echo.Color 2d "/"
call :Echo.Color 2e "\"
call :Echo.Color 2f "q:" /n
echo(
set complex="c:\hello world!/.\..\\a//^<%%>&|!" /^^^<%%^>^&^|!\
call :Echo.Color.Var 74 complex /n

pause
exit /b

:# The following line must be last and not end by a CRLF.
-

pause
