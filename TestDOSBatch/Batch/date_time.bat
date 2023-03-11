
:: 날짜 시간 (Date Time)

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Date Time 정보 얻기
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

:: DATE 환경 변수 : 년월일 정보 반환
echo %DATE%
:: output
:: 2021-01-11
set year=%DATE:~0,4%
echo year=%year%
:: output
:: 2021
set month=%DATE:~5,2%
echo month=%month%
:: output
:: 01
set day=%DATE:~8,2%
echo day=%day%
:: output
:: 11

:: TIME 환경 변수 : 시분초 정보 반환
echo %TIME%
:: output
:: 15-12-45
set hour=%TIME:~0,2%
if "%hour:~0,1%" == " " (
	set hour=0%hour:~1,1%
)
echo hour=%hour%
:: output
:: 15
set min=%TIME:~3,2%
if "%min:~0,1%" == " " (
	set min=0%min:~1,1%
)
echo min=%min%
:: output
:: 12
set secs=%TIME:~6,2%
if "%secs:~0,1%" == " " (
	set secs=0%secs:~1,1%
)
echo secs=%secs%
:: output
:: 45


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Date Time Week 정보 얻기
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

pushd "%temp%"

makecab /d RptFileName=~.rpt /d InfFileName=~.inf /f nul >nul
for /f "tokens=3-7" %%a in ('find /i "makecab"^<~.rpt') do (
	set "current-date=%%e-%%b-%%c"
	set "current-time=%%d"
	set "weekday=%%a"
)
del ~.*

popd

echo %weekday% %current-date% %current-time%
:: output
:: Sun 2021-Jan-10 22:06:04







