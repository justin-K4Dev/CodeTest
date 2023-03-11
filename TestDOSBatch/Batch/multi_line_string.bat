
:: Multi-line 사용 하기.

@echo off

pushd.

rem Windows 에서 멀티 라인은 ^ 문자를 사용
set target_dir="K:\my-project\TestCode\TestDOSBatch\Batch"

cd /d %target_dir%

xcopy.exe hello.txt ^
K:\my-project\TestCode\TestDOSBatch\Batch\^
hi.txt /F /Y

popd.

pause