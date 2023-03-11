using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Configuration;
using System.Runtime.CompilerServices;
using System.Windows.Forms;
using Microsoft.Extensions.Configuration;



using NLog;



namespace NLogDotNet
{
	public class Basic
	{
		static void nlog_what()
		{
			/*
				NLog URL : https://github.com/NLog 
			
			    1. 주요 정의
			      * 로그 레벨 계층 관계
			        - Trace > Debug > Info > Warn > Error > Fatal
			        - 기본적으로 특정 레벨 지정시 해당 레벨과 하위 레벨들까지만 출력 가능 하다.
			        - 특정 레벨만 출력시 level, levels 설정을 사용 한다.
			       
				2. 특징
				  * 오픈소스 닷넷 플랫폼 로그 라이브러리
				  * .NET Compact, mono도 지원
				  * 사용이 쉽고, 설정은 설정 파일과 소스 코드를 통한 2가지 방법 제공.
				  * 옵션 지정으로 버퍼링, 비동기, 로드 밸런싱, 장애대처 등을 할 수 있다.
				  * 출력 옵션
					- Files - single file or multiple, with automatic file naming and archival
					- Event Log - local or remote
					- Database - store your logs in databases supported by .NET
					- Network - using TCP, UDP, SOAP, MSMQ protocols
					- Command-line console - including color coding of messages
					- E-mail - you can receive emails whenever application errors occur
					- ASP.NET trace 등등…
				  * NuGet 지원 : [http://www.nuget.org/packages/NLog]
				  * 로그 뷰어 : [https://github.com/nlog/nlog/wiki/Tools]
				                [https://github.com/yarseyah/sentinel]

				3. Config 속성
                  * Automatic reconfiguration
			        - autoReload = "true"
			          : Config 설정 변경시 읽어지도록 적용 된다.

			      * Troubleshooting logging
                    - throwConfigExceptions = "true"
                      : Config 설정 정보 오류시 예외가 발생되게 적용 한다.
                    - internalLogLevel = "Trace | Debug | Info | Warn | Error | Fatal"
                      : 내부 로그 수준을 결정한다. 수준이 높을수록 내부 로그 출력이 덜 장황해 진다.
				    - internalLogFile = "c:\target-path\nlog-log.txt"
				      : NLog 가 내부 디버깅 메시지를 지정된 파일에 쓴다. 여기에는 로깅 중에 발생할 수 있는 모든 예외가 포함 된다.
			        - internalLogToConsole = "false | true"
			          : 콘솔창에 내부 로깅 메시지를 출력 한다.
			        - internalLogToConsoleError = "false | true"
			          : 콘솔창에 오류 출력(stderr)으로 내부 로깅 메시지를 출력 한다.

                  * Layout Renderers 속성
			        - URL : https://nlog-project.org/config/?tab=layout-renderers

				3. 환경 설정 방법 3가지
                  * 실행 어셈블리와 같은 경로에 NLog.config 라는 이름의 파일로 XML형식으로 설정하는 방식
                  * 실행 바이너리의 config 파일 (App.config) 안에 <nlog>태그를 추가하는 방식
                  * 프로그램 안에서 C#코드로 설정하는 방식
                 
                4. 기타 참고 사이트
				  - https://github.com/nlog/nlog/wiki/when-filter#conditions
				  - https://github.com/nlog/nlog/wiki/filtering-log-messages
                  - https://github.com/nlog/nlog/wiki/configuration-file#rules
			*/
		}

		static void output_after_default_reconfigure_load()
		{
			/*
				nlog.config 파일은 기본적으로 출력 경로의 root 경로에서 로딩 하며,
				root 경로에 없을 경우 NLog.Config.XmlLoggingConfiguration(@".\\Config\\nlog.config")
				같이 별도로 로딩해 주어야 한다.

				* nlog.config 파일 속성 설정
				  솔루션 탐색기 > nlog.config 파일 선택 > 속성 정보 편집 : 고급 > 빌드 > 출력 디렉토리로 복사 : 항상 복사 선택 !!!
				
				//NLog Configuration Guide : https://github.com/NLog/NLog/wiki/Configuration-file#file-locations
			*/

			LogManager.Configuration = new NLog.Config.XmlLoggingConfiguration(@".\\Config\\nlog.config.default");
			LogManager.ReconfigExistingLoggers();

			var logger = LogManager.GetCurrentClassLogger();

			logger.Info("Reconfigured Default configure !!!");

			// 예외 발생
			try
			{
				int i = 0;
				i = 1 / i;
			}
			catch (Exception e)
			{
				// 예외 로그 출력
				logger.Error(e, "0 나누기 에러:");
			}

			Console.ReadLine();
		}

		static void output_after_advanced_reconfigure_load()
		{
			LogManager.Configuration = new NLog.Config.XmlLoggingConfiguration(@".\\Config\\nlog.config.advanced");
			LogManager.ReconfigExistingLoggers();

			var logger = LogManager.GetCurrentClassLogger();

			logger.Info("Reconfigured Advanced configure !!!");

			Console.ReadLine();
		}

		static void output_with_XML_config_include()
		{
			LogManager.Configuration = new NLog.Config.XmlLoggingConfiguration(@".\\Config\\nlog.config.override");
			LogManager.ReconfigExistingLoggers();

			var logger = LogManager.GetLogger("PerformanceLogger");

			logger.Trace($"Output {logger.Name} !!!");

			Console.ReadLine();
		}

		static void output_with_basic()
		{
			LogManager.Configuration = new NLog.Config.XmlLoggingConfiguration(@".\\Config\\nlog.config.advanced");
			LogManager.ReconfigExistingLoggers();

			var logger = LogManager.GetLogger("BasicLogger");
			logger.Debug($"Output {logger.Name} !!!");

			Console.ReadLine();
		}

		static void output_with_LogEventInfo( [CallerMemberName] string memberName = "",
			                                  [CallerFilePath] string sourceFilePath = "",
			                                  [CallerLineNumber] Int32 sourceLineNumber = 0 )
		{
			LogManager.Configuration = new NLog.Config.XmlLoggingConfiguration(@".\\Config\\nlog.config.advanced");
			LogManager.ReconfigExistingLoggers();

			var logger = LogManager.GetLogger("LogEventInfoLogger");

			LogEventInfo logEventInfo = new LogEventInfo(LogLevel.Debug, null, "Output Message by LogEventInfo !!!");
			logEventInfo.Properties["memberName"] = memberName;
			logEventInfo.Properties["filePath"] = sourceFilePath;
			logEventInfo.Properties["lineNumber"] = sourceLineNumber;

			logger.Debug(logEventInfo);

			Console.ReadLine();
		}

		static void output_with_vsdebugger([CallerFilePath] string sourceFilePath = "",
										   [CallerLineNumber] Int32 sourceLineNumber = 0)
		{
			LogManager.Configuration = new NLog.Config.XmlLoggingConfiguration(@".\\Config\\nlog.config.advanced");
			LogManager.ReconfigExistingLoggers();

			var logger = LogManager.GetLogger("DebugLogger");

			LogEventInfo logEventInfo = new LogEventInfo(LogLevel.Debug, null, "Output Message to VS Debug Window !!!");
			logEventInfo.Properties["filePath"] = sourceFilePath;
			logEventInfo.Properties["lineNumber"] = sourceLineNumber;

			logger.Debug(logEventInfo);

			Console.ReadLine();
		}

		public static void inputFromConsole()
		{
			while (true)
			{
				Console.WriteLine("Press 'c' + 'Enter' to exit");
				if (Console.ReadLine() == "c")
				{
					Application.Exit();
					Console.WriteLine("Exit LogForm");
					break;
				}

				System.Threading.Thread.Sleep(1000);
			}
		}

		static void output_with_win_ui_logger()
		{
			LogManager.Configuration = new NLog.Config.XmlLoggingConfiguration(@".\\Config\\nlog.config.advanced");
			LogManager.ReconfigExistingLoggers();

			var logger = LogManager.GetLogger("WinUILogger");

			logger.Debug($"Output {logger.Name} !!!");

			Thread t = new System.Threading.Thread(inputFromConsole);
			t.Start();

			Application.Run();

			Console.ReadLine();
		}

		static void output_with_filter_condition()
		{
			LogManager.Configuration = new NLog.Config.XmlLoggingConfiguration(@".\\Config\\nlog.config.advanced");
			LogManager.ReconfigExistingLoggers();

			var logger = LogManager.GetLogger("FilterLogger");

			// LogEventInfo.Properties 값 체크의 예
			{
				// nlog.config.advanced => <when condition = "contains('${event-properties:memberName}', 'justin')" action = "Log" /> 조건절로 출력된다.
				LogEventInfo logEventInfo = new LogEventInfo(LogLevel.Debug, null, "Output log by Filter & Condition !!!");
				logEventInfo.Properties["memberName"] = "justin";

				logger.Debug(logEventInfo);
			}

			// Exception 발생의 예
			{
				// nlog.config.advanced => <when condition="exception != null" action="Ignore" /> 조건절로 출력되지 않는다 !!!
				logger.Error(new Exception(), "This is an Exception message !!!");
			}

			logger.Trace($"Output {logger.Name} !!!");

			Console.ReadLine();
		}

		public static void Test()
		{
			//output_with_filter_condition();

			//output_with_win_ui_logger();

			//output_with_vsdebugger();

			//output_with_LogEventInfo();

			//output_with_basic();

			//output_with_XML_config_include();

			//output_after_default_reconfigure_load();

			//nlog_what();
		}
	}
}
