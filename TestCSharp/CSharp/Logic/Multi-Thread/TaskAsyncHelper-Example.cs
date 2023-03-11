using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;



namespace MultiThread
{
	public class TaskAsyncHelperExample
	{
		static async Task TaskAsyncHelper_basic()
		{



			Console.ReadLine();
		}


		public static void Test()
		{
			TaskAsyncHelper_basic().Wait();
		}
	}
}
