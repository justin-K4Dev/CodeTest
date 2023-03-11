
:: Windows Service 사용 하기

@echo off


Set ServiceName=Jenkins


:: service 실행 & 종료 하기
NET STOP %ServiceName%
NET START %ServiceName%


:: query 를 사용하여 서비스 실행 상태 체크 하기
SC QUERY %ServiceName% | FIND "RUNNING" >nul
IF ERRORLEVEL 1 (
	echo NOT RUNNING
) ELSE (
	echo RUNNING
)

:: queryex 사용하여 서비스 실행 상태 체크 하여 서비스 실행 하기
SC QUERYEX "%ServiceName%" | find /i "STOPPED" > nul && (
    echo %ServiceName% not running 
    echo Start %ServiceName%

    NET START "%ServiceName%" > nul || (
        echo "%ServiceName%" wont start 
        exit /b 1
    )
    echo "%ServiceName%" started
    exit /b 0
)||(
    echo "%ServiceName%" working
    exit /b 0
)

pause