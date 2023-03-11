using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;


using Amazon.Runtime;
using Amazon.DynamoDBv2;
using Amazon.DynamoDBv2.Model;
using Amazon.DynamoDBv2.DataModel;
using Amazon.DynamoDBv2.DocumentModel;


using Profiler;


namespace AWSDynamoDB
{
    public class PerformanceCheck
    {
		static void print_profile_all()
		{
			var infos = new List<IInfo>();
			var info_profile = new ProfileInfo();
			infos.Add(info_profile);

			ScopedProfileHelper.fillupMonitor(ref info_profile);
			NamedProfileHelper.fillupMonitor(ref info_profile);

			var sb = new StringBuilder();
			{
				foreach (var each in infos)
				{
					if (each.hasInfo())
					{
						sb.AppendLine("\n========================================================================");
						sb.AppendLine(each.GetType().Name);
						sb.AppendLine("==========================================================================");
						sb.AppendLine($"{each.toString()}");
					}
				}

				Console.Write(sb.ToString());
			}
		}



		public static void Test()
        {
			PerformanceMonitor.start(10, print_profile_all);


			PerformanceMonitor.stop();
		}
    }
}
