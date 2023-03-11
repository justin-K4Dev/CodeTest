using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;


using System.Threading;
using System.Threading.Tasks;



namespace MultiThread
{
	public class TaskScheduler
	{
		//첫번째 실행
		private static async Task FirstCoroutine()
		{
			Console.WriteLine("Starting - Zone #1");
			Console.WriteLine($"CurrentThreadId:{System.Threading.Thread.CurrentThread.ManagedThreadId}");
			Console.WriteLine("Yielding - Zone #1");

			//배타 실행 스케줄에서 Task가 실행 됨으로 다음 Task에 실행 수행을 넘긴다.
			await Task.Yield();

			Console.WriteLine("Returned - Zone #1");
			Console.WriteLine($"CurrentThreadId:{System.Threading.Thread.CurrentThread.ManagedThreadId}");
			Console.WriteLine("Yielding again - Zone #1");

			//배타 실행 스케줄에서 Task가 실행 됨으로 다음 Task에 실행 수행을 넘긴다.
			await Task.Yield();

			Console.WriteLine("Returned - Zone #1");
			Console.WriteLine($"CurrentThreadId:{System.Threading.Thread.CurrentThread.ManagedThreadId}");
			Console.WriteLine("Finished - Zone #1");
		}

		//두번째 실행
		private static async Task SecondCoroutine()
		{
			Console.WriteLine("\tStarting - Zone #2");
			Console.WriteLine($"\tCurrentThreadId:{System.Threading.Thread.CurrentThread.ManagedThreadId}");
			Console.WriteLine("\tYielding - Zone #2");

			//배타 실행 스케줄에서 Task가 실행 됨으로 다음 Task에 실행 수행을 넘긴다.
			await Task.Yield();

			Console.WriteLine("\tReturned - Zone #2");
			Console.WriteLine($"\tCurrentThreadId:{System.Threading.Thread.CurrentThread.ManagedThreadId}");
			Console.WriteLine("\tYielding again - Zone #2");

			//배타 실행 스케줄에서 Task가 실행 됨으로 다음 Task에 실행 수행을 넘긴다.
			await Task.Yield();

			Console.WriteLine("\tReturned - Zone #2");
			Console.WriteLine($"\tCurrentThreadId:{System.Threading.Thread.CurrentThread.ManagedThreadId}");
			Console.WriteLine("\tYielding again - Zone #2");

			//배타 실행 스케줄에서 Task가 실행 됨으로 다음 Task에 실행 수행을 넘긴다.
			await Task.Yield();

			Console.WriteLine("\tReturned again - Zone #2");
			Console.WriteLine($"\tCurrentThreadId:{System.Threading.Thread.CurrentThread.ManagedThreadId}");
			Console.WriteLine("\tFinished - Zone #2");
		}

		//세번째 실행
		private static async Task ThirdCoroutine()
		{
			Console.WriteLine("\t\tStarting - Zone #3");
			Console.WriteLine($"\t\tCurrentThreadId:{System.Threading.Thread.CurrentThread.ManagedThreadId}");
			Console.WriteLine("\t\tYielding - Zone #3");

			//배타 실행 스케줄에서 Task가 실행 됨으로 다음 Task에 실행 수행을 넘긴다.
			await Task.Yield();

			Console.WriteLine("\t\tReturned - Zone #3");
			Console.WriteLine($"\t\tCurrentThreadId:{System.Threading.Thread.CurrentThread.ManagedThreadId}");
			Console.WriteLine("\t\tFinished - Zone #3");
		}

		private static async Task runCoroutineAsync(TaskFactory taskFactory, Func<Task> coroutine)
		{
			//배타 실행 스케줄로 세팅된 TaskFactory
			//StartNew로 만들어진 Task를 배타 실행되는 스케줄로 관리가 되도록 컨트롤 한다.
			await await taskFactory.StartNew(coroutine);
		}

		static async Task doCoroutinesAsync(TaskFactory taskFactory)
		{
			var coroutines = new[]
			{
				runCoroutineAsync(taskFactory, FirstCoroutine)
			,	runCoroutineAsync(taskFactory, SecondCoroutine)
			,	runCoroutineAsync(taskFactory, ThirdCoroutine)
			};

			//모두 완료가 될 때가지 대기 한다.
			await Task.WhenAll(coroutines);
		}

		static async void Task_with_yield()
		{
			var coroutineFactory = new TaskFactory(new ConcurrentExclusiveSchedulerPair().ExclusiveScheduler);

			var task = doCoroutinesAsync(coroutineFactory);
			task.Wait();

			Console.ReadLine();
		}

		public class CustomTaskScheduler : System.Threading.Tasks.TaskScheduler
		{
			/// <summary>연결된 쓰레드에서 동기 Task 제공해 준다</summary>
			/// <param name="task">큐에 대기할 Task입니다.</param>
			protected override void QueueTask(Task task)
			{
				TryExecuteTask(task);
			}

			/// <summary>연결된 쓰레드에서 동기 Task 제공해 준다</summary>
			/// <param name="task">실행할 타스크</param>
			/// <param name="taskWasPreviouslyQueued">작업이 이전에 큐에 대기되었는지 여부를 나타내는 부울입니다.이 매개 변수가 True이면 작업이 이전에 큐에 대기된 것일 수 있습니다. False이면 작업이 큐에 대기되지 않은 것입니다. 작업을 큐에 대기하지 않고 인라인으로 실행하려면 이 호출을 수행합니다.</param>
			/// <returns>작업이 인라인으로 실행되었는지 여부를 나타내는 부울 값입니다. 성공적인 실행 시 True, 그 이외에 false</returns>
			/// <remarks>재진입으로 인한 오류를 방지하기 위해 작업 인라이닝은 관련된 스레드의 로컬 큐에서 대기 중인 대상이 있는 경우에만 발생합니다.</remarks>
			protected override bool TryExecuteTaskInline(Task task, bool taskWasPreviouslyQueued)
			{
				return TryExecuteTask(task);
			}

			/// <summary>디버거를 지원하기 위해 현재 스케줄러의 큐에 대기되어 실행을 기다리고 있는 Task 인스턴스의 열거 가능한 형식을 생성합니다.</summary>
			/// <returns>디버거가 현재 이 스케줄러의 큐에 대기된 작업을 트래버스할 수 있도록 허용하는 열거 가능한 형식입니다.</returns>
			protected override IEnumerable<Task> GetScheduledTasks()
			{
				return Enumerable.Empty<Task>();
			}

			/// <summary>이 TaskScheduler가 지원할 수 있는 최대 동시성 수준을 나타냅니다.</summary>
			public override int MaximumConcurrencyLevel { get { return 1; } }
		}

		static void Task_with_custom_schedule()
		{
			// 시간을 재기 위해서 사용
			Stopwatch sw = new Stopwatch();
			sw.Start();

			var myScheduler = new CustomTaskScheduler();
			// 기본 스케줄러
			// myScheduler = TaskScheduler.Default;
			// 동시 실행 갯수 확인
			// Console.WriteLine(myScheduler.MaximumConcurrencyLevel);

			// 커스터마이징 된 MyScheduler을 이용해 TaskFactory를 생성 하도록 한다.
			var factory = new TaskFactory(myScheduler);
			var tasks = new List<System.Threading.Tasks.Task>();

			// 동시 실행이 되도록 수행
			for (int j = 1; j <= 200; j++)
			{
				var task = factory.StartNew(() =>
				{
					for (int i = 0; i < 500; i++)
					{
						var tid = System.Threading.Thread.CurrentThread.ManagedThreadId;
						Console.WriteLine("{0} on Thread !!! - TID:{1}", i, tid);
					}
				});

				tasks.Add(task);
			}

			// 모두 완료가 될 때까지 대기
			System.Threading.Tasks.Task.WaitAll(tasks.ToArray());

			sw.Stop();
			Console.WriteLine(sw.ElapsedMilliseconds);

			Console.ReadLine();
		}

		internal sealed class SingleThreadTaskScheduler : System.Threading.Tasks.TaskScheduler
		{
			static System.Threading.Thread _thread;
			static BlockingCollection<WorkItem> _workItems;

			class WorkItem
			{
				Task _task;
				public Task Task => _task;
				Func<Task, bool> _func;
				public Func<Task, bool> Func => _func;

				internal WorkItem(Func<Task, bool> func, Task task)
				{
					_task = task;
					_func = func;
				}
			}

			static SingleThreadTaskScheduler()
			{
				_workItems = new BlockingCollection<WorkItem>();

				_thread = new System.Threading.Thread(doThreadFunc);
				_thread.IsBackground = true;
				_thread.Start();
			}

			static void doThreadFunc()
			{
				while (true)
				{
					var item = _workItems.Take();
					item.Func(item.Task); // Task.Factory.StartNew() 에 등록 함수가 호출 된다 !!!
				}
			}

			protected override void QueueTask(Task task)
			{
				_workItems.Add(new WorkItem(TryExecuteTask, task));
			}

			protected override bool TryExecuteTaskInline(Task task, bool taskWasPreviouslyQueued)
			{
				return false;
			}

			protected override IEnumerable<Task> GetScheduledTasks() => null;
			public override int MaximumConcurrencyLevel => 1;
		}

		static void Task_with_Thread_and_custom_schedule()
		{
			var single_thread_task_scheduler = new SingleThreadTaskScheduler();

			Console.WriteLine($"Main Thread !!! - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

			Task.Factory.StartNew(() =>
			{
				Console.WriteLine($"SingleThreadTaskScheduler StartNew !!! - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

			}, CancellationToken.None, TaskCreationOptions.None, single_thread_task_scheduler);

			Console.ReadLine();
		}

		public static void Test()
		{
			//Task_with_Thread_and_custom_schedule();

			//Task_with_custom_schedule();

			//Task_with_yield();
		}
	}
}
