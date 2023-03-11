
@echo off


set PROTO_BIN=%CD%\..\..\ProtoBuf-Bin\3.19.6\bin\protoc.exe

set PROTO_4_UNITY_BIN=%CD%\..\..\ProtoBuf4Unity-Bin\2.3.5\bin\protogen.exe
set PROTO_4_UNITY_INCLUDE_PATH=%CD%\..\..\ProtoBuf4Unity-Bin\2.3.5\include\

set TYPE_DEFINES_PATH=%CD%\..\..\ProtoBuf-TypeDefines\


rem ProtocolBuffers 정의 코드 경로가 존재하는지 체크 한다.

if not exist %TYPE_DEFINES_PATH% (
	echo Not exist [%TYPE_DEFINES_PATH%] !!!
	goto ERROR
)

rem ProtocolBuffers 실행 파일과 Include 경로가 존재하는지 체크 한다.

if not exist %PROTO_BIN% (
	echo Not exist [%PROTO_BIN%] !!!
	goto ERROR
)

if not exist %PROTO_4_UNITY_BIN% (
	echo Not exist [%PROTO_4_UNITY_BIN%] !!!
	goto ERROR
)

if not exist %PROTO_4_UNITY_INCLUDE_PATH% (
	echo Not exist [%PROTO_4_UNITY_INCLUDE_PATH%] !!!
	goto ERROR
)


rem ===============================================================================================
rem 1. ProtocolBuffers 정의 코드들을 언어별 코드로 생성 한다.
rem ===============================================================================================

echo ===== Generate code for each language by ProtocolBuffers ======

set CPP_OUT_PATH=%CD%\..\..\ProtoBuf-Out\cpp\
set CSHARP_OUT_PATH=%CD%\..\..\ProtoBuf-Out\csharp\
set JAVASCRIPT_OUT_PATH=%CD%\..\..\ProtoBuf-Out\javascript\
set CSHARP_4_UNITY_OUT_PATH=%CD%\..\..\ProtoBuf-Out\csharp4unity\


rem 언어별 출력 경로가 존재하는지 체크 한다.

if not exist %CPP_OUT_PATH% (
	echo Not exist [%CPP_OUT_PATH%] !!!
	goto ERROR
)

if not exist %CSHARP_OUT_PATH% (
	echo Not exist [%CSHARP_OUT_PATH%] !!!
	goto ERROR
)

if not exist %JAVASCRIPT_OUT_PATH% (
	echo Not exist [%JAVASCRIPT_OUT_PATH%] !!!
	goto ERROR
)

if not exist %CSHARP_4_UNITY_OUT_PATH% (
	echo Not exist [%CSHARP_4_UNITY_OUT_PATH%] !!!
	goto ERROR
)


rem 언어별 출력 경로내의 파일들을 모두 제거 한다.

del %CPP_OUT_PATH% /q /f
if %ERRORLEVEL% NEQ 0 (
	echo Failed to DEL !!! - Path : [%CPP_OUT_PATH%] !!!
	goto ERROR
)

del %CSHARP_OUT_PATH% /q /f
if %ERRORLEVEL% NEQ 0 (
	echo Failed to DEL !!! - Path : [%CSHARP_OUT_PATH%] !!!
	goto ERROR
)

del %JAVASCRIPT_OUT_PATH% /q /f
if %ERRORLEVEL% NEQ 0 (
	echo Failed to DEL !!! - Path : [%JAVASCRIPT_OUT_PATH%] !!!
	goto ERROR
)

del %CSHARP_4_UNITY_OUT_PATH% /q /f
if %ERRORLEVEL% NEQ 0 (
	echo Failed to DEL !!! - Path : [%CSHARP_4_UNITY_OUT_PATH%] !!!
	goto ERROR
)


rem 언어별 코드를 생성 한다.

rem 현재 경로를 스택해 두고, 정의된 proto 파일이 있는 경로를 현재 경로로 변경 한다.
pushd .
cd /d %TYPE_DEFINES_PATH%

%PROTO_BIN% --cpp_out=%CPP_OUT_PATH% ^
protocol.CommandType.proto ^
protocol.Packet.proto ^
tutorial.player.proto ^
tutorial.hierarchy.proto

if %ERRORLEVEL% NEQ 0 (
	goto ERROR
)

%PROTO_BIN% --csharp_opt=serializable --csharp_out=%CSHARP_OUT_PATH% ^
protocol.CommandType.proto ^
protocol.Packet.proto ^
tutorial.player.proto ^
tutorial.hierarchy.proto

if %ERRORLEVEL% NEQ 0 (
	goto ERROR
)

%PROTO_BIN% --js_out=%JAVASCRIPT_OUT_PATH% ^
protocol.CommandType.proto ^
protocol.Packet.proto ^
tutorial.player.proto ^
tutorial.hierarchy.proto

if %ERRORLEVEL% NEQ 0 (
	goto ERROR
)

rem 필독 사항 !!!
rem protogen 은 코드 생성시 참조 하는 모든 .proto 파일들은 동일한 root 경로를 참조해야 하는 제약 사항이 있다.
rem 그래서 사용자의 .proto 파일들을 protogen 의 include 경로로 모두 복사하여
rem 코드 생성을 진행 해야 한다 !!!

del %PROTO_4_UNITY_INCLUDE_PATH%*.proto /q /f
if %ERRORLEVEL% NEQ 0 (
	echo Failed to DEL !!! - Path : [%PROTO_4_UNITY_INCLUDE_PATH%] !!!
	goto ERROR
)

rem 코드 생성을 위해 사용자의 .proto 파일들을 임시로 protogen 의 include 경로로 모두 복사 한다.
xcopy /e /y %TYPE_DEFINES_PATH%*.proto %PROTO_4_UNITY_INCLUDE_PATH%
if %ERRORLEVEL% NEQ 0 (
	echo Failed to XCOPY !!! - CopyTo : [%TYPE_DEFINES_PATH%*.proto] => [%PROTO_4_UNITY_INCLUDE_PATH%]
	goto ERROR
)

%PROTO_4_UNITY_BIN% --proto_path=%PROTO_4_UNITY_INCLUDE_PATH% --csharp_out=%CSHARP_4_UNITY_OUT_PATH% ^
protocol.CommandType.proto ^
protocol.Packet.proto ^
tutorial.player.proto ^
tutorial.hierarchy.proto

if %ERRORLEVEL% NEQ 0 (
	goto ERROR
)

rem 코드 생성을 위해 임시로 복사한 사용자의 .proto 파일들을 모두 제거 한다.
del %PROTO_4_UNITY_INCLUDE_PATH%*.proto /q /f
if %ERRORLEVEL% NEQ 0 (
	echo Failed to DEL !!! - Path : [%PROTO_4_UNITY_INCLUDE_PATH%] !!!
	goto ERROR
)

rem 스택해둔 이전 경로로 현재 경로를 되돌린다.
popd


rem ===============================================================================================
rem 2. 생성된 코드를 프로젝트별 지정 경로로 모두 복사 한다.
rem ===============================================================================================

echo ===== Copy To Targets =====

set COPY_TO_CPP_PROJECT_PATH=..\ProtoBuf-CPP\Message\
set COPY_TO_CSHARP_PROJECT_PATH=..\ProtoBuf-CSharp\Message\
set COPY_TO_CSHARP_4_UNITY_PROJECT_PATH=..\ProtoBuf-Net-Unity\Message\

set AUTO_UPDATE_FILES_TO_VS_PROJECT_BIN=..\out\AutoUpdateFilesToVSProject.exe


rem 프로젝트별 지정 경로가 존재하는지 체크 한다.

if not exist %COPY_TO_CPP_PROJECT_PATH% (
	echo Not exist [%COPY_TO_CPP_PROJECT_PATH%] !!!
	goto ERROR
)

if not exist %COPY_TO_CSHARP_PROJECT_PATH% (
	echo Not exist [%COPY_TO_CSHARP_PROJECT_PATH%] !!!
	goto ERROR
)

if not exist %COPY_TO_CSHARP_4_UNITY_PROJECT_PATH% (
	echo Not exist [%COPY_TO_CSHARP_4_UNITY_PROJECT_PATH%] !!!
	goto ERROR
)


rem AutoUpdateFilesToVSProject 실행 파일이 존재하는지 체크 한다.

if not exist %AUTO_UPDATE_FILES_TO_VS_PROJECT_BIN% (
	echo Not exist [%AUTO_UPDATE_FILES_TO_VS_PROJECT_BIN%] !!!
	goto ERROR
)


rem 프로젝트별 지정 경로내의 파일들을 모두 제거 한다.

del %COPY_TO_CPP_PROJECT_PATH% /q /f
if %ERRORLEVEL% NEQ 0 (
	echo Failed to DEL !!! - Path : [%COPY_TO_CPP_PROJECT_PATH%] !!!
	goto ERROR
)

del %COPY_TO_CSHARP_PROJECT_PATH% /q /f
if %ERRORLEVEL% NEQ 0 (
	echo Failed to DEL !!! - Path : [%COPY_TO_CSHARP_PROJECT_PATH%] !!!
	goto ERROR
)

del %COPY_TO_CSHARP_4_UNITY_PROJECT_PATH% /q /f
if %ERRORLEVEL% NEQ 0 (
	echo Failed to DEL !!! - Path : [%COPY_TO_CSHARP_4_UNITY_PROJECT_PATH%] !!!
	goto ERROR
)


rem 생성된 코드를 프로젝트별 지정 경로로 각각 복사 한다.

xcopy /e /y %CPP_OUT_PATH%*.h %COPY_TO_CPP_PROJECT_PATH%
if %ERRORLEVEL% NEQ 0 (
	echo Failed to XCOPY !!! - CopyTo : [%CPP_OUT_PATH%*.h] => [%COPY_TO_CPP_PROJECT_PATH%]
	goto ERROR
)

xcopy /e /y %CPP_OUT_PATH%*.cc %COPY_TO_CPP_PROJECT_PATH%
if %ERRORLEVEL% NEQ 0 (
	echo Failed to XCOPY !!! - CopyTo : [%CPP_OUT_PATH%*.cc] => [%COPY_TO_CPP_PROJECT_PATH%]
	goto ERROR
)

xcopy /e /y %CSHARP_OUT_PATH%*.cs %COPY_TO_CSHARP_PROJECT_PATH%
if %ERRORLEVEL% NEQ 0 (
	echo Failed to XCOPY !!! - CopyTo : [%CSHARP_OUT_PATH%*.cs] => [%COPY_TO_CSHARP_PROJECT_PATH%]
	goto ERROR
)

xcopy /e /y %CSHARP_4_UNITY_OUT_PATH%*.cs %COPY_TO_CSHARP_4_UNITY_PROJECT_PATH%
if %ERRORLEVEL% NEQ 0 (
	echo Failed to XCOPY !!! - CopyTo : [%CSHARP_4_UNITY_OUT_PATH%*.cs] => [%COPY_TO_CSHARP_4_UNITY_PROJECT_PATH%]
	goto ERROR
)



rem ===============================================================================================
rem 3. 복사된 모든 파일들을 프로젝트에 자동으로 반영 되도록 한다.
rem ===============================================================================================

%AUTO_UPDATE_FILES_TO_VS_PROJECT_BIN% "AutoUpdateFilesToProtoBuf-CPP.json"
%AUTO_UPDATE_FILES_TO_VS_PROJECT_BIN% "AutoUpdateFilesToProtoBuf-CSharp.json"
%AUTO_UPDATE_FILES_TO_VS_PROJECT_BIN% "AutoUpdateFilesToProtoBuf-Net-Unity.json"


rem 모든 처리 과정을 성공 했으면 종료 한다.
:OK
EXIT /B 0


rem 모든 처리 과정중에 오류가 발생했으면 즉시 스택된 이전 경로로 현재 경로를 되돌리고 종료 한다.
:ERROR
echo ERROR !!! - ProtoBuf Generation And Copy To Projects Failed !!! - ErrorCode : %ERRORLEVEL%
popd
EXIT /B %ERRORLEVEL%

