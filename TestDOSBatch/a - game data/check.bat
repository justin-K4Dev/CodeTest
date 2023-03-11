@echo off

echo start check %1

if exist %1 (
	echo exist %1
) else (
	echo not exist %1
)

pause