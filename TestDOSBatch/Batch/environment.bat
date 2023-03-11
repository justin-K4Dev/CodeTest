
:: 환경변수 사용 하기.

@echo off

echo %PATH%

pause

:: Batch 파일내에서 환경변수 적용 시작 & 끝 내기.

:: 여기서 부터 변수, 환경변수 local 영역에 할당 된다.
setlocal

set my_env=TEST

:: PATH 환경변수 재정의.
set PATH=K:\my-project\TestCode\TestDOSBatch\Batch\

:: 여기서 부터 변수는 제거되고, 환경변수는 원래의 값으로 복원 된다.
endlocal

:: my_env 제거.
:: PATH 환경변수 원래의 값으로 복원.

:: 수식 연산 연동
:: SET /A 변수=수식 ( = , *= , /= , %= , += , -= 가능 )
set B=5
set /a B=B+3
echo %B%

:: B에 3을 더해서 새로운 B 값을 할당
set /a B+=3
:: B에 3을 빼서 새로운 B 값을 할당
set /a B-=3
:: B에 3을 곱해서 새로운 B 값을 할당
set /a B*=3
:: B를 3으로 나눈 몫을 새로운 B 값에 할당
set /a B/=3
:: B를 3으로 나눈 나머지를 새로운 B 값에 할당          
set /a B%=3

:: 문자열 자르는 기능 :~문자열개수
set snoopy=스누피는 컴퓨터를 좋아합니다.
:: 뒤에서 10개의 문자만 추출
set snoopy=%snoopy:~-10%
:: 퓨터를 좋아합니다 로 출력함.
echo %snoopy%

:: 출력 되지 않음 !!!
for %%a in (C: D: E: F: G: H: I: J: K: L: M: N: O: P: Q: R: S: T: U: V: W: X: Y: Z:) do (
     set b=%%a
     echo %b%
)

:: 아래 명령어 추가시 출력됨 !!!
:: for 문이나 if 문 내에서 set 명령어 사용시 setlocal ENABLEDELAYEDEXPANSION 반드시 필요 !!!
:: 해당 변수에 접근시 % 대신 ! 사용해야 함 !!!
setlocal ENABLEDELAYEDEXPANSION

:: 출력 됨 !!!
for %%a in (C: D: E: F: G: H: I: J: K: L: M: N: O: P: Q: R: S: T: U: V: W: X: Y: Z:) do (
     set b=%%a
     echo !b!
)

endlocal

:: 시스템 환경 변수 저장 - Overcoming the 1024 character limit with setx
setx MY_ENV "test" /m
:: 시스템 환경 변수 조회
for /f "tokens=3 delims=^ " %%i in ('reg query "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\Environment" ^| findstr /i /c:"MY_ENV"') do (
	echo MY_ENV: %%i
)

:: 시스템 환경 변수 값만 불러 오기
set curr_path="
for /f "skip=2 tokens=3*" %%a in ('reg query "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\Environment" /v Path') do (
	set curr_path="%%a %%b"
	echo !curr_path!	
)

set my_path="%%test_path_1%%;%%test_path_2%%;%%test_path_3%%"

set filter_path=%my_path:"=%
echo %filter_path%

:: 경로 정보에 끝에 ";" 없을 경우 추가 하기
if not "%filter_path:~-1%" == ";" (
	echo Not found
	set "filter_path=%filter_path%;"
) else (
	echo Found
)
echo %filter_path%

:: 시스템 환경 변수에 없는 값만 저장 하기 (%curr_path% 콘솔 출력 않됨)
echo %curr_path% | findstr "%%test_path_1%%" 1>nul
if %ERRORLEVEL% == 1 (
	echo Not found path !!! "%%test_path_1%%"
	reg add "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Environment" /v "Path" /t REG_EXPAND_SZ /f /d "%path%;%%test_path_1%%"
)

:: 사용자 환경 변수 저장
setx MY_ENV "test"
:: 사용자 환경 변수 조회
for /f "tokens=3 delims=^ " %%i in ('reg query "HKCU\Environment" ^| findstr /i /c:"MY_ENV"') do (
	echo MY_ENV: %%i
)

:: 시스템 환경 변수 저장 - up to the maximum environment variable length; 2,048 or 32,768 bytes depending on the source
set my_path="%%test_path_1%%;%%test_path_2%%;%%test_path_3%%"
echo %my_path%

reg add "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Environment" /T REG_EXPAND_SZ /V "PATH" /D "%path%;%my_path%" /F

:: Note however that while you can enter a very long path,
:: (up to the maximum environment variable length; 2,048 or 32,768 bytes depending on the source),
:: not all software will be able to read and handle it correctly if it is too long.

:: 현재 디렉터리 문자열로 확장합니다.
echo %CD%
:: DATE 명령과 같은 포맷을 사용하여 현재 날짜로 확장합니다.
echo %DATE%
:: TIME 명령과 같은 포맷을 사용하여 현재 시간으로 확장합니다.
echo %TIME%
:: 0과 32767 사이에 있는 임의 숫자로 확장합니다.
echo %RANDOM%
:: 현재 ERRPRLEVEL 값으로 확장합니다
echo %ERRORLEVEL%
:: 현재 명령 프로세서 확장자 버전 번호로 확장합니다.
echo %CMDEXTVERSION%
:: 명령 프로세서를 호출하는 원본 명령줄로 확장합니다.
echo %CMDCMDLINE%
:: 이 컴퓨터의 최고 NUMA 노드 수로 확장합니다.
echo %HIGHESTNUMANODENUMBER%


pause




