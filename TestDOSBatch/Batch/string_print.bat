
:: 화면 또는 파일로 메세지를 출력 하기.

@echo off

rem 빈줄 출력
echo.
rem output
:: 

rem 문장 출력-방법1
echo.
echo.Hello !!!
echo.
rem output
::
:: Hello !!!
:: 

rem 문장 출력-방법2
echo.
echo Hello !!!
echo.
rem output
::
:: Hello !!!
:: 

rem 문장 출력-방법3
set "str=Hi !!!"
echo %str%
set str="Hello !!!"
echo.%str%
rem output
:: Hi !!!
:: "Hello !!!"

rem 문장 출력 예외 : ECHO가 설정되어 있지 않습니다.
set "str="
echo %str%
echo.%str%
:: ECHO가 설정되어 있지 않습니다.


rem 문장 파일 출력 : hello.txt 파일을 생성하고 Hello !!! 문장을 저장 한다.
echo.Hello !!!>K:\my-project\TestCode\TestDOSBatch\Batch\hello.txt

rem @echo on 이후 부터 명령어는 출력 하지 않고 처리 결과만 출력 시킨다.
@echo off

rem @echo on 이후 부터 명령어와 처리 결과 모두 출력 시킨다.
@echo on

pause