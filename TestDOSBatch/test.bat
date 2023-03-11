@echo off

setlocal ENABLEDELAYEDEXPANSION


set curr_path="
for /f "skip=2 tokens=3*" %%a in ('reg query "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\Environment" /v Path') do (
	set curr_path="%%a %%b"
	echo !curr_path!	
)

echo %curr_path% | findstr "%%test_path_1%%" 1>nul
if %ERRORLEVEL% == 1 (
	echo Not found path !!! "%%test_path_1%%"
	reg add "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Environment" /v "Path" /t REG_EXPAND_SZ /f /d "%path%;%%test_path_1%%"
)



pause