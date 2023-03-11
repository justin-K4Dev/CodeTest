
:: File & Directory 존재 체크

@echo off

rem 파일 & 디렉토리 존재 유무 분기 처리
:::::::::::::::::::::::::::::::::::::::::::::::::::::
:: if exist <insert file name here or directory name> (
::    rem file exists
:: ) else (
::    rem file doesn't exist
:: )
:::::::::::::::::::::::::::::::::::::::::::::::::::::

set target_file="K:\my-project\TestCode\TestDOSBatch\Batch\target\data_1.txt"

IF EXIST %target_file% (
	del %target_file%
) ELSE (
	echo file not found : %target_file%
)


rem 파일 & 디렉토리 존재할 경우 처리
:::::::::::::::::::::::::::::::::::::::::::::::::::::
:: if exist <insert file name here or directory name> <action>
:::::::::::::::::::::::::::::::::::::::::::::::::::::

IF EXIST %target_file% echo file found : %target_file%


pause
