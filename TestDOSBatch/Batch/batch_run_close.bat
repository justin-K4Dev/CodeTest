
:: Batch 파일 실행 & 종료 하기

@echo off


:: EXIT 로 종료하면 batch 를 실행하는 cmd.exe 도 종료 된다.
EXIT


:: 배치 파일내에 메인 or 서버 루틴에서 실행할 경우 종료 된다.
:: EXIT /B error_level
:: 서브 루틴에서 실행될 경우 ErrorLevel 을 반환 한다.
EXIT /B 1


:: GOTO:EOF 를 실행하면 현재 배치 파일 실행만 종료 된다.
GOTO:EOF
