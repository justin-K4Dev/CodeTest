
:: SETLOCAL
:: 환경 변수의 지역화를 사용하도록 설정하는 명령어
:: 배치파일 내에서 CMD /E:OFF 또는 CMD V:ON 없이 명령 처리 확장 또는 지연된 환경 변수 확장을 사용 여부를 설정할 수 있는 명령어

SETLOCAL
SET "string_value=ABCD"
ECHO %string_value%
:: output
:: ABCD

SETLOCAL
SET int_value=1
ECHO %int_value%
:: output
:: 1

SET "string_value=ZXWV..."
ECHO %string_value%
:: output
:: ZXWV...
ENDLOCAL

ECHO %string_value%
:: output
:: ABCD
ECHO %int_value%
:: output
:: ECHO가 설정되어 있지 않습니다.
ECHO !int_value!
:: output
:: !int_value!


:: SETLOCAL ENABLEEXTENSIONS/DISABLEEXTENSIONS
:: ENABLEEXTENSIONS : 기본값
:: DISABLEEXTENSIONS : CD, COLOR과 같은 명령이나 FOR 명령의 /F, /D, /R 등을 사용할 수 없다.

SETLOCAL ENABLEEXTENSIONS

CD /D "K:\my-project\TestCode\TestDOSBatch"
DIR
:: output
:: K 드라이브의 볼륨: Data
:: 볼륨 일련 번호: 8C36-DFB9
::
:: K:\my-project\TestCode\TestDOSBatch 디렉터리
::
:: 2021-01-07  오전 04:20    <DIR>          .
:: 2021-01-07  오전 04:20    <DIR>          ..
:: 2021-01-09  오전 03:59    <DIR>          Batch
:: 2020-09-14  오전 02:09    <DIR>          Command
:: 2020-01-22  오전 12:43                46 merge.txt
:: 2021-01-09  오후 09:27               229 test.bat
::                2개 파일                 275 바이트
::                4개 디렉터리  13,789,888,512 바이트 남음

SETLOCAL DISABLEEXTENSIONS

cd /D "K:\my-project\TestCode\TestDOSBatch"
:: output
:: 파일 이름, 디렉터리 이름 또는 볼륨 레이블 구문이 잘못되었습니다.
dir
:: K 드라이브의 볼륨: Data
:: 볼륨 일련 번호: 8C36-DFB9
::
:: K:\my-project\TestCode\TestDOSBatch 디렉터리
::
:: 2021-01-07  오전 04:20    <DIR>          .
:: 2021-01-07  오전 04:20    <DIR>          ..
:: 2021-01-09  오전 03:59    <DIR>          Batch
:: 2020-09-14  오전 02:09    <DIR>          Command
:: 2020-01-22  오전 12:43                46 merge.txt
:: 2021-01-09  오후 09:27               229 test.bat
::                2개 파일                 275 바이트
::                4개 디렉터리  13,789,888,512 바이트 남음

ENDLOCAL


:: SETLOCAL ENABLEDELAYEDEXPANSION/DISABLEELAYEDEXPANSION
:: ENABLEDELAYEDEXPANSION : 해당 변수의 값이 원래 값으로 변경 되는 것을 지연시켜주는 확장 기능 활성화 설정
:: DISABLEELAYEDEXPANSION : 기본값

SETLOCAL ENABLEDELAYEDEXPANSION

echo ENABLEDELAYEDEXPANSION on

set var="before"
if %var% == "before" (
	set var="after"
	if %var% == "after" (
		echo non-delay equal %var% , "after"
	)
	if !var! == "after" (
		echo delay equal !var! , "after"
		rem output
		rem delay equal "after" , "after"		
	)	
	echo non-delay %var% , delay !var!
	rem output
	rem non-delay "before" , delay "after"		
) 

echo non-delay %var% , delay !var!
:: rem output
:: non-delay "after" , delay "after"

ENDLOCAL

echo ENABLEDELAYEDEXPANSION off
set var="finish"	
if %var% == "finish" (
	echo non-delay equal %var% , "after"
	rem output
	rem non-delay equal "finish" , "after"	
)
if !var! == "finish" (
	echo delay equal !var! , "after"
)
echo non-delay %var% , delay !var!
:: output
:: non-delay "finish" , delay !var!


SETLOCAL ENABLEDELAYEDEXPANSION
set num=0
for %%i in (1 2 3 4) do (
	set num=!num!:%%i
	echo !num!
	rem output
	rem 0:1
	rem 0:1:2
	rem 0:1:2:3
	rem 0:1:2:3:4
)
echo %num%
:: output
:: 0:1:2:3:4
ENDLOCAL































