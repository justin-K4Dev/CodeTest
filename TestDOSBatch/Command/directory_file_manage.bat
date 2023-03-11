
:: 디렉토리 & 파일 관리 하기

@echo off

rem switch
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: command /? : 해당 명령어의 여러 옵션 기능을 처리
::              입력 위치는 command 바로 뒤 or 제일 뒤에만 있으면 무관
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


rem change directory
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: CD .         : 현 위치의 디렉토리
:: CD ..        : 바로 위의 디렉토리
:: CD \         : 현 드라이브의 루트 디렉토리
:: CD [path]    : 현 드라이브내에서 path 로 이동 (다른 드라이브일 경우 이동 불능)
:: CD [path] /D : path 로 이동 (다른 드라이브 이더라도 이동 가능)
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
CD /D K:\my-project\TestCode\TestDOSBatch


rem directory output
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: DIR          : 현 위치의 디렉토리, 파일 목록 출력
:: DIR [path]   : path 위치의 디렉토리, 파일 목록 출력
:: DIR ... /P   : 디렉토리, 파일 목록을 한 화면씩 끊어서 출력
:: DIR ... /W   : 한 화면에 5줄 씩 파일 이름만 출력
:: DIR ... /S   : 하위 디렉토리에 있는 목록까지 모두 출력
:: DIR ... /A   : 특정 속성의 파일을 출력(/AH, /AR, /AS, /AD, /AA)
:: DIR ... /O   : 파일을 정렬하여 출력(/on, /OE, /OD, /OS, /OG, /OC)
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
DIR K:\my-project\TestCode\TestDOSBatch /P /A


rem text file output
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: TYPE [filename]        : 현 위치에서 filename 의 파일 내용 출력
:: TYPE [path + filename] : path 위치에서 filename 의 파일 내용 출력
:: TYPE [path + filename] > [target_path + filename] : 대상 경로로 파일을 생성 & source 파일들의 내용을 모두 결합 
:: MORE [filename]        : 한 화면에 출력 후 초과된 이후 부분들은 라인 단위로 출력 (너무 큰 파일이라면 사용)
:: MORE [path + filename] : path 위치에서 filename 의 파일 내용 출력
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
TYPE K:\my-project\TestCode\TestDOSBatch\test.bat
TYPE K:\my-project\TestCode\TestDOSBatch\Command\source\file_*.txt > merge.txt
MORE K:\my-project\TestCode\TestDOSBatch\Batch\for_loop.bat


rem file & directory copy
rem file copy
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: COPY [source_path + filename] [target_path]  : 소량의 파일들을 복사하려는 경우에 사용 (내부 메모리 활용 파일 단위 복사), 
:: COPY ... /V                                  : 복사한 파일이 원본과 동일한지 검사
:: COPY ... /Y                                  : 대상 위치 경로에 동일한 파일이 있을 경우 묻지 않고 무조건 덮어 쓰기
:: COPY ... /-Y                                 : 덮어 쓰기가 될 경우 모두 확인 절차를 거침(기본값)
:: COPY [[source_path + filename1]+[source_path + filename2]] [target_path+filename] : 여러 파일을 하나로 결합 복사
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
COPY K:\my-project\TestCode\TestDOSBatch\Command\source\dos_command.txt K:\my-project\TestCode\TestDOSBatch\Command\target
COPY K:\my-project\TestCode\TestDOSBatch\Command\source\*.* K:\my-project\TestCode\TestDOSBatch\Command\target /Y
COPY K:\my-project\TestCode\TestDOSBatch\Command\source\file_1.txt+K:\my-project\TestCode\TestDOSBatch\Command\source\file_2.txt K:\my-project\TestCode\TestDOSBatch\Command\target\merge.txt /Y


rem directory copy
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: XCOPY [source_path] [target_path]            : 다량의 파일들을 복사하려는 경우에 사용 (외부 메모리 활용 버퍼 단위 복사), 디렉토리 단위 복사 가능
:: XCOPY ... /D                                 : 소스파일과 타겟파일을  비교하여 새로운 것만 복사
:: XCOPY ... /E                                 : 모든 서브디렉토리를 포함하여 복사 (빈 폴더 포함) –> 빈폴더 제외는 /s 옵션
:: XCOPY ... /C                                 : 오류가 발생하더라도 중단하지 말고 계속 복사 (깨진 파일때문에 복사가 중단되는 일이 있음)
:: XCOPY ... /Y                                 : 덮어쓰기 할때 묻지않고 복사
:: XCOPY ... /I                                 : 복사할 대상이 존재하지 않거나 하나이상의 파일을 복사할때 타켓을 디렉토리로 인식
:: XCOPY ... /H                                 : 숨김 파일이나 시스템 파일도 복사
:: XCOPY ... /G                                 : 암호화파일을 복사
:: XCOPY ... /K                                 : 파일의 속성을 복사 (이 옵션을 빼면 read-only 속성을 리셋)
:: XCOPY ... /O                                 : 파일의 소유권과 ACL 정보까지 복사
:: XCOPY ... /X                                 : 파일의 감사 속성을 복사
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
XCOPY K:\my-project\TestCode\TestDOSBatch\Command\source K:\my-project\TestCode\TestDOSBatch\Command\target /s /h /e /d /k /y
XCOPY K:\my-project\TestCode\TestDOSBatch\Command\source\*.txt K:\my-project\TestCode\TestDOSBatch\Command\target /s /h /e /d /k /y

rem file & directory all copy with extension append

SETLOCAL EnableDelayExpansion

SET "srcDir=k:\my-project\test\src"
SET "destDir=k:\my-project\test\target"

FOR /R %srcDir% %%i IN (*.txt) DO (
	echo srcDir: !srcDir!
    set strFilePath=%%i
	echo srcFilePath: !strFilePath!
	
	call set trimFile=%%strFilePath:!srcDir!=%%
	echo trim left: !trimFile!
	
	set targetFilePath=!destDir!!trimFile!.bytes
	echo targetPath: !targetFilePath!
	
	echo f|XCOPY /E /Y %%i !targetFilePath!
)

ENDLOCAL

:: output
:: srcDir: k:\my-project\test\src
:: srcFilePath: k:\my-project\test\src\a\a.txt
:: trim left: \a\a.txt
:: targetPath: k:\my-project\test\target\a\a.txt.bytes
:: K:\my-project\test\src\a\a.txt
:: 1개 파일이 복사되었습니다.
:: srcDir: k:\my-project\test\src
:: srcFilePath: k:\my-project\test\src\a\b\b.txt
:: trim left: \a\b\b.txt
:: targetPath: k:\my-project\test\target\a\b\b.txt.bytes
:: K:\my-project\test\src\a\b\b.txt
:: 1개 파일이 복사되었습니다.
:: srcDir: k:\my-project\test\src
:: srcFilePath: k:\my-project\test\src\a\b\c\c.txt
:: trim left: \a\b\c\c.txt
:: targetPath: k:\my-project\test\target\a\b\c\c.txt.bytes
:: K:\my-project\test\src\a\b\c\c.txt
:: 1개 파일이 복사되었습니다.
:: 계속하려면 아무 키나 누르십시오 . . .


rem copy for backup
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: ROBOCOPY [source_path] [target_path]         : 한 화면 내에서 보기에 너무 큰 파일이라면 이 명령을 사용
:: ROBOCOPY ... /R:[횟수]                       : 오류의 경우 재시도 횟수
:: ROBOCOPY ... /W:[횟수]                       : 다시 시도 대기시간
:: ROBOCOPY ... /E                              : 비어 있는 디렉토리를 포함하여 하위 디렉토리를 복사
:: ROBOCOPY ... /MOV                            : 파일을 이동 (복사후 원본데이터는 삭제)
:: ROBOCOPY ... /MOVE                           : 파일 & 디렉터리를 이동 (복사후 원본데이터는 삭제)
:: ROBOCOPY ... /V                              : 자세한 정보를 출력하며 건더뛴 파일을 표시
:: ROBOCOPY ... /L                              : 목록 전용 - 파일을 복사 또는 삭제하거나 타임스탬프를 만들지 않음
:: ROBOCOPY ... /FP                             : 출력되는 파일의 전체 경로 이름을 포합
:: ROBOCOPY ... /Z                              : 다시 시작 모드에서 파일을 복사
:: ROBOCOPY ... /MAX:[크기]                     : 최대 파일 크기 - 옵션에 크기가 초과한 파일을 제외
:: ROBOCOPY ... /MIN:[크기]                     : 최소 파일 크기 - 옵션에 크기가 미만인 파일을 제외
:: ROBOCOPY ... /MAXAGE:[날짜]                  : 최대 파일 사용기간 - 옵션의 날짜보다 오래된 파일을 제외
:: ROBOCOPY ... /MINAGE:[날짜]                  : 최소 파일 사용기간 - 옵션의 날짜보다 최신의 파일을 제외
:: ROBOCOPY ... /RH: HHMM-HHMM                  : 실행시간 - 새 복사본을 시작할 수 있는 시작 시간 (/RH:1230-1240 <- 12시30분 ~ 12시40분 사이에 시작)
:: ROBOCOPY ... /NFL                            : 파일 목록 없음 - 파일 이름을 기록하지 않음
:: ROBOCOPY ... /NDL                            : 디렉터리 목록 없음 - 디렉터리 이름을 기록하지 않음
:: ROBOCOPY ... /MOT:[분]                       : 몇 분안에 변동이 있으면 복사
:: ROBOCOPY ... /MON:[개수]                     : 몇 개이상의 변동이 있으면 복사
:: ROBOCOPY ... /LOG:[파일이름]                 : 상태를 로그파일에 출력 (기존 로그에 덮어씀)
:: ROBOCOPY ... /LOG+:[파일이름]                : 상태를 로그파일에 출력, 기존 로그에 추가
:: ROBOCOPY ... /UNILOG:[파일이름]              : 상태를 유니코드로 로그 파일에 출력 (기존 로그에 덮어씀) 
:: ROBOCOPY ... /UNILOG+:[파일이름]             : 상태를 유니코드로 로그 파일에 출력, 기존 로그에 추가
:: ROBOCOPY ... /MIR:[파일이름]                 : 디렉토리 트리를 미러링 (복사하는 데이터를 일치화)
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
ROBOCOPY K:\my-project\TestCode\TestDOSBatch\Command\source K:\my-project\TestCode\TestDOSBatch\Command\target /MIR
ROBOCOPY K:\my-project\TestCode\TestDOSBatch\Command\source K:\my-project\TestCode\TestDOSBatch\Command\backup /MIR /RH:1230-1240
ROBOCOPY K:\my-project\TestCode\TestDOSBatch\Command\source K:\my-project\TestCode\TestDOSBatch\Command\backup /MIR /LOG+:"K:\my-project\TestCode\TestDOSBatch\Command\log\robocopy.log"


rem file create
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: COPY nul > [source_path+filename]      : 해당 경로에 파일명으로 파일 생성
:: COPY nul > [source_path+"file name"]   : 공백문자가 포함된 파일명으로 파일 생성
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
COPY nul K:\my-project\TestCode\TestDOSBatch\Command\source\file_x.txt
COPY nul K:\my-project\TestCode\TestDOSBatch\Command\source\"file z.txt"


rem file delete
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: DEL [source_path+filename]             : 해당 경로의 파일을 삭제
:: DEL ... /P                             : 파일을 삭제 하기전에 확인하는 메시지 표시
:: DEL ... /F                             : 읽기전용 파일도 삭제
:: DEL ... /S                             : 모든 하위 디렉토리내의 파일을 삭제
:: DEL ... /Q                             : 파일을 삭제할 것인지 묻는 메시지를 표시 하지 않음
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
DEL K:\my-project\TestCode\TestDOSBatch\Command\source\file_x.txt /Q
DEL K:\my-project\TestCode\TestDOSBatch\Command\backup\*.txt /F /S /Q
DEL K:\my-project\TestCode\TestDOSBatch\Command\backup\* /F /S /Q

rem 현재 경로내의 모든 파일 삭제
DEL *


rem directory create
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: MD & MKDIR 동일 파라메터 & 옵션
:: MD [source_path+directory]               : 해당 경로에 디렉토리명으로 생성
:: MD [source_path+directory]               : 해당 경로에 디렉토리명으로 생성
:: MD [source_path+"directory name"]        : 공백문자가 포함된 디렉토리 생성
:: MD [source_path+directory];[source_path+directory] ... : 복수개의 디렉토리 생성
:: MD [source_path+directory]\[source_path+directory] ... : 하위 디렉토리도 같이 생성
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
MD K:\my-project\TestCode\TestDOSBatch\Command\mydir
MD K:\my-project\TestCode\TestDOSBatch\Command\"mydir 2"
MD K:\my-project\TestCode\TestDOSBatch\Command\source\1; K:\my-project\TestCode\TestDOSBatch\Command\source\2
MD "K:\my-project\TestCode\TestDOSBatch\Command\source\3"\4


rem directory delete
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: RD & RMDIR 동일 파라메터 & 옵션
:: RD [source_path+directory]               : 해당 경로에 디렉토리명으로 삭제
:: RD ... /S                                : 하위 디렉토리까지 삭제
:: RD ... /Q                                : 디렉토리를 삭제할 것인지 묻지 않고 삭제
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
RD K:\my-project\TestCode\TestDOSBatch\Command\mydir
RD K:\my-project\TestCode\TestDOSBatch\Command\"mydir 2"
RD K:\my-project\TestCode\TestDOSBatch\Command\source\3 /S /Q

rem 현재 경로내의 모든 폴더 & 파일 삭제 하기, (target_path) <- 대상 경로 설정
for /d %%i in (*) do @RD /s /q "%%i"


rem file & directory rename
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: REN [source_path+filename] [target_path+new_filename]      : 해당 파일명을 변경
:: REN [source_path+directory] [target_path+new_directory]    : 해당 디렉토리명을 변경
:: MOVE [source_path+directory] [target_path+new_directory]   : 해당 디렉토리명을 변경
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
REN K:\my-project\TestCode\TestDOSBatch\Command\source\file_1.txt K:\my-project\TestCode\TestDOSBatch\Command\source\file_11.txt
REN K:\my-project\TestCode\TestDOSBatch\Command\source\file_11.txt K:\my-project\TestCode\TestDOSBatch\Command\source\file_1.txt
REN K:\my-project\TestCode\TestDOSBatch\Command\source K:\my-project\TestCode\TestDOSBatch\Command\source2
REN K:\my-project\TestCode\TestDOSBatch\Command\source2 K:\my-project\TestCode\TestDOSBatch\Command\source
MOVE K:\my-project\TestCode\TestDOSBatch\Command\source K:\my-project\TestCode\TestDOSBatch\Command\source3
MOVE K:\my-project\TestCode\TestDOSBatch\Command\source3 K:\my-project\TestCode\TestDOSBatch\Command\source


rem file attrib
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: ATTRIB [target_path+filename]           : 해당 경로의 파일의 속성 조회
:: ATTRIB [target_path+filename] +r        : 해당 경로의 파일에 읽기전용 속성 추가
:: ATTRIB [target_path+filename] -r        : 해당 경로의 파일에 읽기전용 속성 제거
:: ATTRIB [target_path+filename] +h        : 해당 경로의 파일에 숨김 속성 추가
:: ATTRIB [target_path+filename] -h        : 해당 경로의 파일에 숨김 속성 추가
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
ATTRIB K:\my-project\TestCode\TestDOSBatch\Command\source\file_1.txt +r
ATTRIB K:\my-project\TestCode\TestDOSBatch\Command\source\file_1.txt -r
ATTRIB K:\my-project\TestCode\TestDOSBatch\Command\source\"file z".txt +h
ATTRIB K:\my-project\TestCode\TestDOSBatch\Command\source\"file z".txt -h
ATTRIB *.* 


rem file move
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: MOVE [source_path+filename] [target_path]  : 해당 경로로 파일들을 이동
:: MOVE /Y ...                                : 대상 경로에 동명의 파일이 있을 경우 덮어 쓰기
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
MOVE /Y K:\my-project\TestCode\TestDOSBatch\Command\source\file_1.txt K:\my-project\TestCode\TestDOSBatch\Command\target
MOVE /Y K:\my-project\TestCode\TestDOSBatch\Command\target\file_1.txt K:\my-project\TestCode\TestDOSBatch\Command\source


rem file & directory symbol link
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: MKLINK [sympbol_path+link_name] [target_path+filename]        : 파일 심볼 링크
:: dir [sympbol_path] /AL                                        : 파일 심볼 링크 조회
:: MKLINK /H [sympbol_path+link_name] [target_path+filename]     : 파일 하드 링크 (동일 드라이브내에서만 사용 가능)
:: fsutil hardlink list [sympbol_path+link_name]                 : 하드 링크 정보 조회
:: MKLINK /D [sympbol_path+link_name] [target_path]              : 디렉토리 심볼 링크
:: dir [sympbol_path] /AL                                        : 디렉토리 심볼 링크 조회
:: MKLINK /J [sympbol_path+link_name] [target_path]              : 디렉토리 정션 링크
:: dir [sympbol_path] /AL                                        : 디렉토리 정션 링크 조회
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
MKLINK K:\my-project\TestCode\TestDOSBatch\Command\link\link_a.txt K:\my-project\TestCode\TestDOSBatch\Command\link\target_a.txt
dir K:\my-project\TestCode\TestDOSBatch\Command\link\ /AL
MKLINK /H K:\my-project\TestCode\TestDOSBatch\Command\link\link_b.txt K:\my-project\TestCode\TestDOSBatch\Command\link\target_b.txt
fsutil hardlink list "K:\my-project\TestCode\TestDOSBatch\Command\link\link_b.txt"
MKLINK /D K:\my-project\TestCode\TestDOSBatch\Command\dir_link_d K:\my-project\TestCode\TestDOSBatch\Command\target
dir K:\my-project\TestCode\TestDOSBatch\Command\ /AL
MKLINK /J K:\my-project\TestCode\TestDOSBatch\Command\dir_link_j K:\my-project\TestCode\TestDOSBatch\Command\target
dir K:\my-project\TestCode\TestDOSBatch\Command\ /AL


pause

