
:: Change Directory 시 드라이브도 함께 변경 하기.

@echo off

::현재 경로 정보를 stack 넣어 둔다.
pushd.

:: 현재 경로 정보 출력 하기
echo current path : %CD

set target_dir="K:\my-project\TestCode\TestDOSBatch"

echo target path : %target_dir%

rem 드라이브도 함께 변경 /D 스위치 사용
cd /D %target_dir%

echo current path : %CD%

rem output
:: current path : K:\my-project\TestCode\TestDOSBatch\Batch
:: target path : "K:\my-project\TestCode\TestDOSBatch"
:: current path : K:\my-project\TestCode\TestDOSBatch

:: 넣어둔 경로 정보를 stack 에서 꺼낸다.
popd.

pause