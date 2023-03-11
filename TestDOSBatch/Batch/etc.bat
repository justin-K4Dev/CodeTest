
:: etc 정리

@echo off

pushd.


rem 주요 operator
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::
:: command  >  filename       			Redirect command output to a file
:: command  >> filename       			APPEND into a file
:: command  <  filename       			Type a text file and pass the text to command
::
:: commandA |  commandB     			Pipe the output from commandA into commandB
::
:: commandA &  commandB      			Run commandA and then run commandB
:: commandA && commandB      			Run commandA, if it succeeds then run commandB
:: commandA || commandB      			Run commandA, if it fails then run commandB
::
:: commandA && commandB || commandC		If commandA succeeds run commandB, if it fails commandC
::
:: Success and failure are based on the Exit Code of the command.
:: In most cases the Exit Code is the same as the ErrorLevel
::
:: Numeric handles:
:: 
::	STDIN  = 0  Keyboard input
:: 	STDOUT = 1  Text output
:: 	STDERR = 2  Error text output
:: 	UNDEFINED = 3-9
::
:: 		command  2> filename       	Redirect any error message into a file
:: 		command  2>> filename      	Append any error message into a file
:: 		(command) 2> filename       Redirect any CMD.exe error into a file
:: 		command > file 2>&1       	Redirect errors and output to one file
:: 		command > fileA 2> fileB  	Redirect output and errors to separate files
::
:: 		command 2>&1 >filename    	This will fail!
::
:: Redirect to NUL (hide errors)
::
:: 		command 2> nul            	Redirect error messages to NUL
::   	command >nul 2>&1         	Redirect error and output to NUL
::   	command >filename 2> nul  	Redirect output to file but suppress error
::  	(command)>filename 2> nul  	Redirect output to file but suppress CMD.exe errors
::
:: Any long filenames must be surrounded in "double quotes".
:: A CMD error is an error raised by the command processor itself rather than the program/command.
::
:: Redirection with > or 2> will overwrite any existing file.
::
:: You can also redirect to a printer with > PRN or >LPT1
::
:: Multiple commands on one line
::								
::	In a batch file the default behaviour is to read and expand variables one line at a time,
::	if you use & to run multiple commands on a single line,
::	then any variable changes will not be visible until execution moves to the next line.
::
::	For example:
:: 		SET /P _cost="Enter the price: " & ECHO %_cost%
::
::	This behaviour can be changed using SETLOCAL EnableDelayedExpansion
::
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

:: 오류 메시지 화면 출력
dir xxx.txt
echo EL: %errorlevel%
:: output
:: K 드라이브의 볼륨: Work
:: 볼륨 일련 번호: 6099-9B74
::
:: K:\my-project\TestCode\TestDOSBatch\Batch 디렉터리 <- stdout
::
:: 파일을 찾을 수 없습니다. <- stderr
:: EL: 1


:: 결과 정보를 파일에 출력
dir > out.txt
echo EL: %errorlevel%
:: output
:: EL: 0


:: 화면에 출력 되지 않게
dir > nul
echo EL: %errorlevel%
:: output
:: EL: 0


:: 데이터를 입력 받게
sort < out.txt
echo EL: %errorlevel%
:: output
:: ...
:: 2019-10-30  오전 01:44    <DIR>          target
:: 2019-10-30  오후 09:00                11 hello.txt
:: 2019-10-30  오후 09:00                11 hi.txt
:: 2019-10-30  오후 11:19               140 program_start_exit.bat
:: 2019-10-30  오후 11:19               176 batch_run_close.bat
:: 2019-10-30  오후 11:48               463 input_choise.bat
:: 2019-10-30  오후 11:48               517 environment.bat
:: 2019-10-30  오후 11:48             1,643 compare.bat
:: 2019-10-30  오후 11:49               966 string_print.bat
:: 2019-10-30  오후 11:50             1,259 batch_template_usage.txt
:: 2019-10-31  오전 12:08               451 parameter_pass.bat
:: 2019-11-01  오전 09:56               656 cd_drive_change.bat
:: 2019-11-02  오후 03:51             3,205 batch_template.bat
:: 2019-11-02  오후 03:52               295 multi_line_string.bat
:: 2019-11-02  오후 03:55               532 description.bat
:: 2019-11-03  오전 01:49    <DIR>          source
:: 2019-11-03  오전 02:14            10,066 for_loop.bat
:: 2019-11-03  오전 02:38               824 file_directory_exist_check.bat
:: 2019-11-04  오후 11:56             1,984 condition.bat
:: 2019-11-05  오전 09:33               502 windows_service.bat
:: 2019-11-05  오전 10:24                91 test.bat
:: 2019-11-05  오전 12:13               618 color_change.bat
:: 2019-11-05  오전 12:50             1,012 error_level.bat
:: 2019-11-05  오후 10:46    <DIR>          .
:: 2019-11-05  오후 10:46    <DIR>          ..
:: 2019-11-05  오후 10:55             1,376 etc.bat
:: 2019-11-05  오후 10:56                 0 out.txt
:: EL: 0


:: 오류 메시지 stdout 출력 않되고 stderr 출력 되게
dir xxx.txt > nul
echo EL: %errorlevel%
:: output
:: 파일을 찾을 수 없습니다.
:: EL: 1


:: 오류 메시지 stdout 출력 되고 stderr 출력 않되게
dir xxx.txt 2> nul
echo EL: %errorlevel%
:: output
:: K 드라이브의 볼륨: Work
:: 볼륨 일련 번호: 6099-9B74
::
:: K:\my-project\TestCode\TestDOSBatch\Batch 디렉터리
:: EL: 1


:: 오류 메시지 stdout, stderr 출력 않되게
dir xxx.txt > nul 2>&1
echo EL: %errorlevel%
:: output
:: EL: 1


:: dir 결과를 정렬 시켜준다.
dir | sort
echo EL: %errorlevel%
:: output
:: ...
:: 2019-10-30  오전 01:44    <DIR>          target
:: 2019-10-30  오후 09:00                11 hello.txt
:: 2019-10-30  오후 09:00                11 hi.txt
:: 2019-10-30  오후 11:19               140 program_start_exit.bat
:: 2019-10-30  오후 11:19               176 batch_run_close.bat
:: 2019-10-30  오후 11:48               463 input_choise.bat
:: 2019-10-30  오후 11:48               517 environment.bat
:: 2019-10-30  오후 11:48             1,643 compare.bat
:: 2019-10-30  오후 11:49               966 string_print.bat
:: 2019-10-30  오후 11:50             1,259 batch_template_usage.txt
:: 2019-10-31  오전 12:08               451 parameter_pass.bat
:: 2019-11-01  오전 09:56               656 cd_drive_change.bat
:: 2019-11-02  오후 03:51             3,205 batch_template.bat
:: 2019-11-02  오후 03:52               295 multi_line_string.bat
:: 2019-11-02  오후 03:55               532 description.bat
:: 2019-11-03  오전 01:49    <DIR>          source
:: 2019-11-03  오전 02:14            10,066 for_loop.bat
:: 2019-11-03  오전 02:38               824 file_directory_exist_check.bat
:: 2019-11-04  오후 11:56             1,984 condition.bat
:: 2019-11-05  오전 09:33               502 windows_service.bat
:: 2019-11-05  오전 10:24                91 test.bat
:: 2019-11-05  오전 12:13               618 color_change.bat
:: 2019-11-05  오전 12:50             1,012 error_level.bat
:: 2019-11-05  오후 10:56    <DIR>          .
:: 2019-11-05  오후 10:56    <DIR>          ..
:: 2019-11-05  오후 11:22               137 null
:: 2019-11-05  오후 11:22             1,800 out.txt
:: 2019-11-05  오후 11:22             3,529 etc.bat
:: EL: 0



rem 특정 코드 & 파일 실행 하기
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: CALL :label_name arguments ...              : label_name 호출 하면서 파라메터를 넘겨줌
:: CALL [target_path+filename] arguments ...   : 해당 파일을 실행 하면서 파라메터를 넘겨줌
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

:: echo.bat
:: call :subroutine %*
:: exit /b %ERRORLEVEL%
::  
:: :subroutine
:: echo Hello %*
:: goto :eof
::  
:: :subroutine2
:: echo We will never see this

:: echo.bat Nico
:: output:
:: Hello Nico


:: cmd 창 타이틀 설정 하기
TITLE Test


:: cmd 창 크기를 설정 하기
:: MODE 
MODE con cols=40 lines=11

:: 10 초간 기다리기
TIMEOUT /t 10 


popd.

pause