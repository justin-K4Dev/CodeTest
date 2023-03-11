using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MultiThread
{
	public class Parallel
	{
		static async Task mathSQRT(Int32 num)
		{
			await Task.Run(() =>
			{
				double d = Math.Sqrt(num);
				Console.WriteLine("{0} on {1}", d, System.Threading.Thread.CurrentThread.ManagedThreadId);
			});
		}


		static async void Parallel_with_Async()
		{
			int[] nums = Enumerable.Range(0, 100).ToArray();
			var cts = new System.Threading.CancellationTokenSource();
			var token = cts.Token;

			// Use ParallelOptions instance to store the CancellationToken
			ParallelOptions po = new ParallelOptions();
			po.MaxDegreeOfParallelism = System.Environment.ProcessorCount;
			Console.WriteLine("Press any key to start");
			Console.ReadLine();

			System.Threading.Tasks.Parallel.ForEach(nums, po, async (num, cts) => {
				await mathSQRT(num);
			});
	
			Console.ReadLine();
		}

		public static void Test()
		{
			//Parallel_with_Async();
		}
	}
}
