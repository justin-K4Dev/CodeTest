
:: Process 관리 하기

@echo off


rem process 조회
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: TASKLIST                                 : 모든 프로세스 표시
:: TASKLIST /[process_image_name]           : 동일한 프로세스 이미지 표시
:: TASKLIST /V                              : 자세한 작업 정보 표시
:: TASKLIST /FO [출력형식:TABLE, LIST, CSV] : 출력 형식 지정
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
TASKLIST /V /FO CSV > tasklist.csv

rem 북수개의 process 반복 체크

setlocal EnableExtensions EnableDelayedExpansion

set "process_list=notepad.exe notepad++.exe"

:ProcessCheck
for %%a in (%process_list%) do (

	set value=%%a
	echo check start : !value!
	
	TASKLIST /FI "imagename eq !value!*" 2>nul | find /i /n "!value!">nul
	if !ERRORLEVEL! equ 0 (
		echo found running Process !!! : !value!
		timeout 10
		call :ProcessCheck
	)
)

echo check end !!!

rem process 실행
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: CALL [target_path+exe_filename]         : 동일한 실행 파일을 실행
:: 실행 결과값 반환 받은 후 다음 명령 실행
:: 
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
CALL calc
CALL notepad.exe

rem process 실행
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: START [target_path+exe_filename]         : 동일한 실행 파일을 실행
:: 실행 결과값 반환 받지 않고 바로 다음 명령 실행
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
START calc
START notepad.exe

rem process 죽이기
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: TASKKILL /IM [process_image_name]       : 동일한 프로세스 이미지 이름을 가진 모든 프로세스 종료 
:: TASKKILL /PID [process_id]              : 동일한 프로세스 id 가진 프로세스 종료
:: TASKKILL ... /F                         : 해당 프로세스를 강제로 종료
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
TASKKILL /IM afidev.exe /F
TASKKILL /PID 3314


pause
