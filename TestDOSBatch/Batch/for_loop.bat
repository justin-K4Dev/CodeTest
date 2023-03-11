
:: FOR 구문

@echo off

pushd.

set target_path="K:\my-project\TestCode\TestDOSBatch\Batch\target"

rem FOR
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Conditionally perform a command on several files.
::
:: Syntax
::     FOR %%parameter IN (set) DO command
::
:: Key
::     set         : A set of one or more files, separated by any standard delimiter.
::                   enclosed in parenthesis (file1,file2). Wildcards can be used.
::
::     command     : The command to carry out, including any parameters.
::                   This can be a single command, or if you enclose it
::                   in (brackets), several commands, one per line.
::
::    %%parameter : A replaceable parameter:
::                  e.g. in a batch file use %%G 
::                       (on the command line %G <- in console window)
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

echo FOR statement

:: copy file
set source_file_1="K:\my-project\TestCode\TestDOSBatch\Batch\source\data_1.txt"
FOR %%i IN (%source_file_1%) DO copy %%i %target_path%

:: copy file list
set source_file_2="K:\my-project\TestCode\TestDOSBatch\Batch\source\data_2.txt"
FOR %%i IN (%source_file_1% %source_file_2%) DO copy %%i %target_path%

FOR %%i IN ("Hello World") DO echo %%i

:: using variables within a FOR loop
set source_path="K:\my-project\TestCode\TestDOSBatch\Batch\source\"
cd /d %source_path%
SET count=1
FOR /F "tokens=*" %%i IN ('dir /b') DO (
	call :subroutine %%i )

:subroutine
	echo %count%:%1
	set /a count += 1

pause
:: output
:: 1:data_1.txt
:: 계속하려면 아무 키나 누르십시오...
:: 2:data_2.txt
:: 계속하려면 아무 키나 누르십시오...
:: 3:data_3.txt
:: 계속하려면 아무 키나 누르십시오...
:: 4:data_4.txt
:: 계속하려면 아무 키나 누르십시오...
:: 5:sub


rem FOR /R
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Loop through files (Recurse subfolders)
::
:: Syntax
::     FOR /R [[drive:]path] %%parameter IN (set) DO command
::
:: Key
::     drive:path  : The folder tree where the files are located.
::
::     set         : A set of one or more files enclosed in parenthesis (file1.*, another?.log).
::                   Wildcards must be used.
::                   If (set) is a period character (.) then FOR will loop through every folder.
::
::     command     : The command to carry out, including any parameters.
::                   This can be a single command, or if you enclose it
::                   in (parenthesis), several commands, one per line.
::
::     %%parameter : A replaceable parameter:
::                   in a batch file use %%G (on the command line %G) 
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

echo FOR /R statement

:: list every .txt file in every subfolder starting at TargetPath
set source_path="K:\my-project\TestCode\TestDOSBatch\Batch\source\"
FOR /R %source_path% %%i IN (*.txt) DO echo %%i

:: a batch file to rename all .txt files to .log in the SourcePath folder and all sub-folders
:: Parameter Extensions -> ~d is drive, ~p is the path(without drive),
::                         ~n is the file name, ~t is date/time, ~z is file size
set source_path="K:\my-project\TestCode\TestDOSBatch\Batch\source\"
FOR /R %source_path% %%i IN (*.log) DO ren %%i %%~ni.txt

:: change directory to each subfolder under SourcePath in turn:
set source_path="K:\my-project\TestCode\TestDOSBatch\Batch\source\"
FOR /R %source_path% %%i IN (.) DO (
	pushd %%i
	echo now in %%i
	popd )
echo "back home"

pause

rem FOR /D
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Conditionally perform a command on several Directories/Folders.
::
:: Syntax
::     FOR /D [/r] %%parameter IN (folder_set) DO command
::
:: Key
::     folder_set  :  A set of one or more folders enclosed in parenthesis (folder1,folder2).
::                    Wildcards must be used.
::
::     command     :  The command to carry out, including any parameters.
::                    This can be a single command, or if you enclose it
::                    in (brackets), several commands, one per line.
::
::     %%parameter :  A replaceable parameter:
::                    in a batch file use %%G (on the command line %G)
::
::     /r          :  Recurse into subfolders (see notes below)
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

:: List every subfolder, below the folder SourcePath that has a name starting with "Sub"
set source_path="K:\my-project\TestCode\TestDOSBatch\Batch\source\"
cd /d %source_path%

FOR /D /R %%i IN ("Sub*") DO echo We found %%~nii

pause
:: output
:: We found sub

rem FOR /L
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Conditionally perform a command for a range of numbers.
::
:: Syntax
::     FOR /L %%parameter IN (start,step,end) DO command
::
:: Key
::     start       : The first number  
::     step        : The amount by which to increment the sequence 
::     end         : The last number 
::
::     command     : The command to carry out, including any parameters.
::                   This can be a single command, or if you enclose it
::                   in (brackets), several commands, one per line.
::
::     %%parameter : A replaceable parameter:
::                   in a batch file use %%G (on the command line %G)
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

:: Count from 1 up to 10
FOR /L %%i IN (1, 2, 10) DO echo %%i
::output
:: 1
:: 3
:: 5
:: 5
:: 7
:: 9

:: non-numeric lists can use a standard FOR command:
FOR %%i IN (Sun Mon Tue Wed Thur Fri Sat) DO echo %%i
::output
:: Sun
:: Mon
:: Tue
:: Wed
:: Thur
:: Fir
:: Sat


rem FOR /F
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Loop command: against the results of another command.
::
:: Syntax
::     FOR /F ["options"] %%parameter IN ('command_to_process') DO command
::
:: Key   
::     options:
::         delims=xxx   The delimiter character(s) (default = a space)
::
::         skip=n       A number of lines to skip at the beginning of the file. 
::                      (default = 0)
:: 
::         eol=;        Character at the start of each line to indicate a comment 
::                      The default is a semicolon ; 
::
::         tokens=n     Specifies which numbered items to read from each line 
::                      (default = 1)
::
::         usebackq     Use the alternate quoting style:                        
::                      - Use double quotes for long file names in "filenameset".
::                      - Use single quotes for 'Text string to process'
::                      - Use back quotes for `command to process`
::
::     command_to_process : The output of the 'command_to_process' is 
::                          passed into the FOR parameter.
::
::         command    :   The command to carry out, including any parameters.
::                        This can be a single command, or if you enclose it
::                        in (brackets), several commands, one per line.
::
::     %%parameter :  A replaceable parameter:
::                    in a batch file use %%G (on the command line %G)
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

set source_path="K:\my-project\TestCode\TestDOSBatch\Batch\source\"
cd /d %source_path%

:: 줄단위로 읽거나 공백문자 까지 읽는다.
FOR /F %%i IN (test.txt) DO echo %%i
:: output
:: 111
:: 111.222.333.444
:: 111
:: 111-222-333-444

:: 파일내의 모든 내용이 출력 된다.
FOR /F "delims=" %%i IN (test.txt) DO echo %%i
:: or FOR /F "tokens=1 delims=" %%i in (test.txt) do echo %%i
:: output
:: 111 222 333 444
:: 111.222.333.444
:: 111    222    333    444
:: 111-222-333-444


FOR /F "tokens=1,2,3* delims=. " %%i IN (test.txt) DO echo %%i
:: output
:: 111
:: 111
:: 111
:: 111-222-333-444


FOR /F "tokens=1,2,3* delims=. " %%i IN (test.txt) DO echo %%i %%j
:: output
:: 111 222
:: 111 222
:: 111 222
:: 111-222-333-444


FOR /F "tokens=1,2,3* delims=. " %%i IN (test.txt) DO echo %%i %%j %%k
:: output
:: 111 222 333
:: 111 222 333
:: 111 222 333
:: 111-222-333-444


FOR /F "tokens=1,2,3* delims=.- " %%i IN (test.txt) DO echo %%i %%j %%k %%l
:: output
:: 111 222 333 444
:: 111 222 333 444
:: 111 222 333 444
:: 111 222 333 444


FOR /F "tokens=2,3* delims=.- " %%i IN (test.txt) DO echo %%i %%j %%k
:: output
:: 222 333 444
:: 222 333 444
:: 222 333 444
:: 222 333 444


FOR /F "tokens=2,3 delims=. " %%i IN (test.txt) DO echo %%i %%j %%k
:: output
:: 222 333 %k
:: 222 333 %k
:: 222 333 %k


FOR /F "tokens=* delims=.- " %%i IN (test.txt) DO echo %%i %%j
:: output
:: 111 222 333 444 %j
:: 111.222.333.444 %j
:: 111    222    333    444 %j
:: 111-222-333-444 %j


FOR /F "tokens=1* delims=.- " %%i IN (test.txt) DO echo %%i %%j
:: output
:: 111 222 333 444
:: 111 222.333.444
:: 111 222    333    444
:: 111 222-333-444


:: use back quote key, 공백 문자도 문자열로 인식 처리 해준다.
FOR /F "usebackq tokens=1* delims=.- " %%i IN ("t est.txt") DO echo %%i %%j
:: output
:: 111 222 333 444
:: 111 222.333.444
:: 111 222    333    444
:: 111 222-333-444


:: 문자열 변수에 접근 하여 필터 한다.
setlocal EnableDelayedExpansion
set curr_path="d:\Program Files\Bluetooth Suite\Atheros Outlook Addin 2010.vsto"
set target_path="file:///C:/Program Files/Bluetooth Suite/Atheros Outlook Addin 2010.vsto"

set replace_path=""
FOR /F "tokens=* delims=file:///" %%i in ( %target_path% ) do (
	echo %%i
	
	rem 확장된 변수에 저장 한다.
	set replace_path=%%i
	echo !replace_path!
	
	rem / 문자를 \ 로 변경 한다.
	set replace_path="!replace_path:/=\!"
	echo !replace_path!
)

if not !curr_path! == !replace_path! (
	echo Not equal path : !curr_path! , !replace_path!
)
endlocal
:: output
:: "C:/Program Files/Bluetooth Suite/Atheros Outlook Addin 2010.vsto"
:: "C:/Program Files/Bluetooth Suite/Atheros Outlook Addin 2010.vsto"
:: "C:\Program Files\Bluetooth Suite\Atheros Outlook Addin 2010.vsto"
:: Not equal path : "d:\Program Files\Bluetooth Suite\Atheros Outlook Addin 2010.vsto" , "C:\Program Files\Bluetooth Suite\Atheros Outlook Addin 2010.vsto"


:: To ECHO from the command line, the name of every environment variable.
:: use single quote key
FOR /F "delims==" %%i IN ('SET') DO echo %%i
:: output
:: Path
:: OS
:: ...

:: use back quote key
FOR /F "usebackq delims==" %%i IN (`SET`) do echo %%i
:: output
:: Path
:: OS
:: ...


popd.

pause





