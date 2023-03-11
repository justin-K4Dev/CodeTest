
:: 조건문 사용 하기.

@echo off

rem IF (NOT) EXIST 조건문
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: IF EXIST value (
::    echo found file or directory
:: ) ELSE ( ELSE 는 IF의 닫는 괄호와 같은 라인에 있어야 한다. !!!
::    echo not found file or directory
:: )
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

IF EXIST %windir%\syswow64 echo windows 64 bit
IF NOT EXIST %windir%\syswow64 echo windows no 64 bit

rem IF (NOT) DEFINED 조건문
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: IF DEFINED value (
::    echo true !!!
:: ) ELSE ( ELSE 는 IF의 닫는 괄호와 같은 라인에 있어야 한다. !!!
::    echo false
:: )
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

IF DEFINED myValue echo find myValue
IF NOT DEFINED myValue echo not found myValue

rem IF (NOT) ERRORLEVEL 조건문
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: IF ERRORLEVEL value (
::    echo error !!!
:: ) ELSE ( ELSE 는 IF의 닫는 괄호와 같은 라인에 있어야 한다. !!!
::    echo no error
:: )
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

ren C:\Windows WindowsXP
IF ERRORLEVEL 1 echo Can't rename Windows Folder

rem IF (NOT) condition ELSE 조건문
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: IF condition (
::    echo true action
:: ) ELSE ( ELSE 는 IF의 닫는 괄호와 같은 라인에 있어야 한다. !!!
::    echo false action
:: )
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

rem 주의 !!!, = 양쪽으로 공백 문자 없어야 함 !!!
set numberValue=1

IF %numberValue% == 1 (
	echo OK
)

set stringValue = 'ABC'

IF DEFINED stringValue (
	echo OK : stringValue
) ELSE (
	echo not OK : stringValue
)

IF %stringValue% equ 'ABC' (
	echo OK : %stringValue%
) ELSE (
	echo not OK : %stringValue%
)

set abc='abc'

rem 대소문자 구분 무시
IF /i %abc% equ 'abc' (
	echo OK : %stringValue%
) ELSE (
	echo not OK : %stringValue%
)

IF %abc% == 'ABC' (
	echo OK
) ELSE (
	echo not OK
)

rem 비교 않됨 !!! , 'abc' 값이기 때문에 double quotation 사용 하면 비교 않됨 !!!
IF %abc% == "ABC" ( 
	echo yes
) ELSE (
	echo no
)

rem 아규먼트를 만자열과 비교 하는 경우 double quotation 사용 해야함
IF "%1" == "kang" (
	echo yes
) ELSE (
	echo no
)

set value="kang"

IF %value% == "kang" (
    goto action1
) ELSE (
    goto action2
)

IF NOT %value% == 'kang' (
	goto action1
) ELSE (
	goto action2
)
  
:action1
	ECHO value is %value%
	pause
  
:action2
	GOTO:EOF
	
:: output
:: value is "kang"

