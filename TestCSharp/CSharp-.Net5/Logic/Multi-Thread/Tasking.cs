using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


using System.Threading;
using System.Threading.Tasks;


namespace MultiThread
{
	public class Tasking
	{
		static void UserClicksTheCancelButton(CancellationTokenSource cts)
		{
			// Wait between 150 and 500 ms, then cancel.
			// Adjust these values if necessary to make
			// cancellation fire while query is still executing.
			Random rand = new();
			System.Threading.Thread.Sleep(rand.Next(150, 500));
			cts.Cancel();
		}

		static void Task_with_cancel_with_PLINQ_query()
		{
			int[] source = Enumerable.Range(1, 10000000).ToArray();
			using CancellationTokenSource cts = new();

			// Start a new asynchronous task that will cancel the
			// operation from another thread. Typically you would call
			// Cancel() in response to a button click or some other
			// user interface event.
			Task.Factory.StartNew(() =>
			{
				UserClicksTheCancelButton(cts);
			});

			int[] results = null;
			try
			{
				results = ( from num in source.AsParallel().WithCancellation(cts.Token)
					        where num % 3 == 0
					        orderby num descending
					        select num ).ToArray();
			}
			catch (OperationCanceledException e)
			{
				Console.WriteLine(e.Message);
			}
			catch (AggregateException ae)
			{
				if (ae.InnerExceptions != null)
				{
					foreach (Exception e in ae.InnerExceptions)
					{
						Console.WriteLine(e.Message);
					}
				}
			}

			foreach (var item in results ?? Array.Empty<int>())
			{
				Console.WriteLine(item);
			}

			Console.WriteLine();

			Console.ReadLine();
		}


		public static void Test()
		{
			//Task_with_cancel_with_PLINQ_query();
		}
	}
}
