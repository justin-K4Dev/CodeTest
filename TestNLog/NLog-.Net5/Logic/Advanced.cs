using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


using NLog;


namespace NLogDotNet
{
	public class Advanced
	{
		static void log_to_mail()
		{
			LogManager.Configuration = new NLog.Config.XmlLoggingConfiguration(@".\\Config\\nlog.config.advanced");
			LogManager.ReconfigExistingLoggers();

			{
				var logger = LogManager.GetLogger("MailLogger");
				logger.Debug($"Output {logger.Name} !!!");
			}

			Console.ReadLine();
		}

		static void log_to_slack()
		{
			LogManager.Configuration = new NLog.Config.XmlLoggingConfiguration(@".\\Config\\nlog.config.advanced");
			LogManager.ReconfigExistingLoggers();

			{
				var logger = LogManager.GetLogger("SlackBasicLogger");
				logger.Debug($"Output {logger.Name} !!!");
			}

			{
				var logger = LogManager.GetLogger("SlackCustomFieldLogger");
				logger.Debug($"Output {logger.Name} !!!");
			}

			Console.ReadLine();
		}

		public static void Test()
		{
			//log_to_slack();

			//log_to_mail();
		}
	}
}
