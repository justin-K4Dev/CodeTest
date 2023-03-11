
:: 문자열 조작 하기 (String Manipulation)

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Align Right - Align text to the right i.e. to improve readability of number columns
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
set x=3000
set y=2
set x=        %x%
set y=        %y%
echo.X=%x:~-8%
echo.Y=%y:~-8%
:: output
:: X=    3000
:: Y=       2


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Left String - Extract characters from the beginning of a string
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
set str=politic
echo.%str%
set str=%str:~0,4%
echo.%str%
:: output
:: politic
:: poli


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Map and Lookup - Use Key-Value pair list to lookup and translate values
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
rem Example 1: Translate name of month into two digit number ----
set v=Mai
echo.%v%
:: output
:: Mai

set map=Jan-01;Feb-02;Mar-03;Apr-04;Mai-05;Jun-06;Jul-07;Aug-08;Sep-09;Oct-10;Nov-11;Dec-12
call set v=%%map:*%v%-=%%
set v=%v:;=&rem.%

echo.%v%
:: output
:: 05

rem Example 2: Translate abbreviation into full string ----
set v=sun
echo.%v%
:: output
:: sun

set map=mon-Monday;tue-Tuesday;wed-Wednesday;thu-Thursday;fri-Friday;sat-Saturday;sun-Sunday
call set v=%%map:*%v%-=%%
set v=%v:;=&rem.%

echo.%v%
:: output
:: Sunday


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Mid String - Extract a Substring by Position
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
echo %DATE%
:: output
:: 2021-01-11
set year=%DATE:~0,4%
echo year=%year%
:: output
:: 2021
set month=%DATE:~5,2%
echo month=%month%
:: output
:: 01
set day=%DATE:~8,2%
echo day=%day%
:: output
:: 11

echo %TIME%
:: output
:: 15-12-45
set hour=%TIME:~0,2%
if "%hour:~0,1%" == " " (
	set hour=0%hour:~1,1%
)
echo hour=%hour%
:: output
:: 15
set min=%TIME:~3,2%
if "%min:~0,1%" == " " (
	set min=0%min:~1,1%
)
echo min=%min%
:: output
:: 12
set secs=%TIME:~6,2%
if "%secs:~0,1%" == " " (
	set secs=0%secs:~1,1%
)
echo secs=%secs%
:: output
:: 45


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Remove both Ends - Remove the first and the last character of a string
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
set str=the cat in the hat
echo.%str%
:: output
:: the cat in the hat
set str=%str:the =%
echo.%str%
:: output
:: cat in hat

:: to remove characters from the right hand side of a string is 
:: a two step process and requires the use of a CALL statement
set remove=the
set str=the cat in the hat
echo.%str%
:: output
:: the cat in the hat
call set str=%%str:%remove% =%%
echo.%str%
:: output
:: cat in hat


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Remove Spaces - Remove all spaces in a string via substitution
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
set str=      word       &rem
echo."%str%"
:: output
:: "      word       "
set str=%str: =%
echo."%str%"
:: output
:: "word"


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Remove Double Quotation
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
set str="word"
echo. %str%
:: output
:: "word"
set str=%str:"=%
echo. %str%
:: output
:: word


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Replace - Replace a substring using string substitution
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
set str=teh cat in teh hat
echo.%str%
:: output
:: teh cat in teh hat
set str=%str:teh=the%
echo.%str%
:: output
:: the cat in the hat


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Right String - Extract characters from the end of a string
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
set str=politic
echo.%str%
:: output
:: politic
set str=%str:~-4%
echo.%str%
:: output
:: itic


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Split String - Split a String, Extract Substrings by Delimiters
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
echo.-- Split off the first date token, i.e. day of the week
for /f %%a in ("%date%") do set d=%%a
echo.Date   : %date%
echo.d      : %d%
:: output
:: 2021-01-10
:: 2021-01-10
echo.-- Split the date into weekday, month, day, and year, using slash and space as delimiters
for /f "tokens=1,2,3 delims=-" %%a in ("%date%") do set year=%%a&set month=%%b&set day=%%c
echo.Year   : %year%
echo.Month  : %month%
echo.Day    : %day%
:: output
:: 2021
:: 01
:: 10


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: String Concatenation - Add one string to another string
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
set "str1=Hello"
set "str2=World"
set "str3=%str1%%str2%"
set "str4=%str1% %str2%"
set "str1=%str1% DOS %str2%"
echo.%str2%
echo.%str3%
echo.%str4%
echo.%str1%
:: output
:: World
:: HelloWorld
:: Hello World
:: Hello DOS World


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Trim Left - Trim spaces from the beginning of a string via "FOR" command
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
set str=               15 Leading spaces to truncate
echo."%str%"
:: output
:: "               15 Leading spaces to truncate"
for /f "tokens=* delims= " %%a in ("%str%") do set str=%%a
echo."%str%"
:: output
:: "15 Leading spaces to truncate"


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Trim Quotes - Remove surrounding quotes via FOR command
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
set str="cmd politic"
echo.%str%
:: output
:: "cmd politic"
for /f "useback tokens=*" %%a in ('%str%') do set str=%%~a
echo.%str%
:: output
:: cmd politic


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Trim Right - Trim spaces from the end of a string via "FOR" command
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
setlocal EnableDelayedExpansion
set str=15 Trailing Spaces to truncate               &rem
echo."%str%"
:: output
:: "15 Trailing Spaces to truncate               "
for /l %%a in (1, 1, 31) do (
	if "!str:~-1!" == " " (
		set str=!str:~0,-1!
	)
)
echo."%str%"
:: output
:: "15 Trailing Spaces to truncate"
endlocal


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Trim Right - Trim spaces from the end of a string via substitution
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
set str=15 Trailing Spaces to truncate               &rem
echo."%str%"
:: "15 Trailing Spaces to truncate               "
set str=%str%##
echo."%str%"
:: "15 Trailing Spaces to truncate               ##"
set str=%str:                ##=##%
echo."%str%"
:: "15 Trailing Spaces to truncate               ##"
set str=%str:        ##=##%
echo."%str%"
:: "15 Trailing Spaces to truncate       ##"
set str=%str:    ##=##%
echo."%str%"
:: "15 Trailing Spaces to truncate   ##"
set str=%str:  ##=##%
:: "15 Trailing Spaces to truncate ##"
echo."%str%"
set str=%str: ##=##%
echo."%str%"
:: "15 Trailing Spaces to truncate##"
set str=%str:##=%
echo."%str%"
:: "15 Trailing Spaces to truncate"


pause















