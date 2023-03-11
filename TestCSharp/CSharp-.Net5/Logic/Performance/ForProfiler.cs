using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


using Profiler;


namespace Performance
{
	public class ForProfiler
	{
		public static void print_profile_all()
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
						sb.AppendLine("\n==========================================================================");
						sb.AppendLine(each.GetType().Name);
						sb.AppendLine("==========================================================================");
						sb.AppendLine($"{each.toString()}");
					}
				}

				Console.Write(sb.ToString());
			}
		}

		static void check_scope_with_profiler()
		{
			ScopedProfileHelper.init(true);

			System.Threading.Tasks.Parallel.For(0, 5, i =>
			{
				using (var profiler = new ScopedProfileHelper.Scoped<DBProfiler4Scope>(new System.Diagnostics.StackFrame(true)
																					  , "profile-1", true))
				{
					profiler.getProfiler()?.incDBTransactCallCount();

					Thread.Sleep(100);
				}

				using (var profiler = new ScopedProfileHelper.Scoped<DBProfiler4Scope>(new System.Diagnostics.StackFrame(true)
																					  , "profile-2", true))
				{
					profiler.getProfiler()?.incDBTransactCallCount();

					Thread.Sleep(100);
				}
			});

			Console.ReadLine();
		}

		static void check_name_with_profiler()
		{
			NamedProfileHelper.init(true);

			System.Threading.Tasks.Parallel.For(0, 5, i =>
			{
				var profiler = NamedProfileHelper.begin<DBProfiler4Name>($"profile-{i}", $"{i}");

				profiler?.incDBTransactCallCount();

				Thread.Sleep(100);

				NamedProfileHelper.end($"profile-{i}", $"{i}");
			});

			Console.ReadLine();
		}

		public static void Test()
		{
			//PerformanceMonitor.start(10, print_profile_all);

			//check_name_with_profiler();

			//check_scope_with_profiler();

			//PerformanceMonitor.stop();
		}
	}
}
