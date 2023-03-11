
:: 파라메터 전달 하기.

rem 첫번째 파라미터는 %1, 두번째는 %2, n 번째는 %n
rem 모든 파라미터는 %* 를 의미

@echo off

rem parameter_pass 1 2 3
set arg1=%1
set arg2=%2

echo %arg1% , %arg2% , %*
rem output
rem 1 , 2 , 1 2 3

rem shift 호출시 %1 <- %2 < - %3 ... 하나씩 파라메터 값 이동
shift
shift

set arg1=%1
set arg2=%2

echo %arg1% , %arg2% , %*
rem output
rem 3 ,  , 1 2 3

rem 경로 전달 하기

rem 파일 전체 경로 얻기 : %0
echo %0
rem K:\my-project\TestCode\TestDOSBatch\parameter_pass.bat 

rem 드라이브명 얻기 : %~d0
echo %~d0
rem K:

rem 경로 얻기 : %~p0
echo %~p0
rem \my-project\TestCode\TestDOSBatch\

rem 파일명 얻기 : %~n0
echo %~n0
rem parameter_pass

rem 확장자명 얻기 : %~x0
echo %~x0
rem .bat

rem 드라이브와 경로 얻기 : %~dp0
echo %~dp0
rem K:\my-project\TestCode\TestDOSBatch\


pause
