
:: File Inout

@echo off

setlocal EnableDelayedExpansion

rem 파일에 저장 하기
:::::::::::::::::::::::::::::::::::::::::::::::::::::
:: data> file
:: data>> file
:::::::::::::::::::::::::::::::::::::::::::::::::::::

echo this is a Test> file_io.txt
echo 12345>> file_io.txt
echo 678.910> file_io.txt
echo (this is in the first line)> file_io.txt
echo (this is in the second line)>> file_io.txt

:::::::::::::::::::::::::::::::::::::::::::::::::::::
:: variable> file or variable>> file
:::::::::::::::::::::::::::::::::::::::::::::::::::::
set value="my data"
echo %value% > file_io.txt

set value="my value"
echo %value% >> file_io.txt



rem 파일 내용 읽기
:::::::::::::::::::::::::::::::::::::::::::::::::::::
:: 파일에서 라인 단위로 읽기
:: FOR /F "tokens=*" %%a IN file DO
:::::::::::::::::::::::::::::::::::::::::::::::::::::
FOR /F "tokens=*" %%a in (file_io.txt) do (
	echo %%a
)


rem 파일 내용 모두 삭제 하기
:::::::::::::::::::::::::::::::::::::::::::::::::::::
:: TYPE nul> file
:: COPY /y nul file
:::::::::::::::::::::::::::::::::::::::::::::::::::::
TYPE nul> file_io.txt
COPY /y nul file_io.txt



endlocal


pause
