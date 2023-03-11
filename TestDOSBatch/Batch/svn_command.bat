
:: SVN command 사용 하기

@echo off

:: svn 실행 파일 경로 설정
set svn=C:\Program Files\TortoiseSVN\bin


:: 특정 경로 update 하기
set target_path=K:\my-project\TestCode\TestDOSBatch

%svn% CLEANUP %target_path%
%svn% REVERT %target_path% -R
%svn% UPDATE %target_path%


:: 여러 경로 update 하기
set target_1=K:\my-project\TestCode\TestDOSBatch\Batch
set target_2=K:\my-project\TestCode\TestDOSBatch\Command

for  %%x in (%target_1%, %target_2%) do (
	echo Revert and Update [%%x]
	cd %%x
	%svn% CLEANUP %%x
	%svn% REVERT %%x -R
	%svn% UPDATE %%x
)

:: 특정 경로 commit 하기
set commit_target=K:\my-project\TestCode\TestDOSBatch\Batch

cd %commit_target%
%svn% COMMIT -M "test commit !!!"


:: 특정 경로로 변경
set working_path=K:\my-project\TestCode\TestDOSBatch
cd %working_path%

:: Working Path 에만 없는 디렉토리 & 파일을 SVN 서버에서 삭제 하기
%svn% status | findstr /R "^!" > missing.list
for /F "token=* delims=! " %%A in (missing.list) do (svn delete "%%A")
del missing.list 2>NUL

:: Working Path 에 추가된 디렉토리 & 파일을 Add 설정 하기
%svn% add --force * --auto-props --parents --depth infinity -q


pause