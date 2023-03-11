using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;

using System.Threading;
using System.Threading.Tasks;



namespace MultiThread
{
	public class AsyncAwait
	{
		static async Task myAsyncVoidFunc()
		{
			// caller 스레드 1
			Console.WriteLine($"myAsyncVoidFunc() Start - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

			// do nothing !!!

			// caller 스레드 1
			Console.WriteLine($"myAsyncVoidFunc() End - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

			// return caller 스레드 1
		}

		static async Task myAsyncVoidFuncDelay()
		{
			// caller 스레드 1
			Console.WriteLine($"myAsyncVoidFuncDelay() Start - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

			// caller 스레드 1
			Console.WriteLine($"\tStart myAsyncVoidFuncDelay >> Task.Delay(1000) 1 - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");
			// caller 스레드 1
			var t1 = Task.Delay(1000);
			// caller 스레드 1
			Console.WriteLine($"\tEnd myAsyncVoidFuncDelay >> Task.Delay(1000) 1 - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

			// caller 스레드 1
			Console.WriteLine($"\tStart myAsyncVoidFuncDelay >> await Task.Delay(1000) 2 - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");
			
			// return caller 스레드 1
			await Task.Delay(1000);
			// pop caller 스레드 4 from ThreadPool

			// caller 스레드 4
			Console.WriteLine($"\tEnd myAsyncVoidFuncDelay >> await Task.Delay(1000) 2 - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

			// caller 스레드 4
			Console.WriteLine($"\tStart myAsyncVoidFuncDelay >> Task.ContinueWith() 1 - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");
			var t2 = t1.ContinueWith((arg) =>
			{
				// pop caller 스레드 5 from ThreadPool

				// caller 스레드 5
				Console.WriteLine($"\tEnd myAsyncVoidFuncDelay >> Task.ContinueWith() 1 - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

				// caller 스레드 5 push to ThreadPool
			});

			// caller 스레드 4
			Console.WriteLine($"\tStart myAsyncVoidFuncDelay >> await Task.Delay(1000) 3 - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

			// return caller 스레드 4
			await Task.Delay(1000); 
			// pop caller 스레드 5 from ThreadPool

			// caller 스레드 5
			Console.WriteLine($"\tEnd myAsyncVoidFuncDelay >> await Task.Delay(1000) 3 - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

			// caller 스레드 5
			Console.WriteLine($"\tStart myAsyncVoidFuncDelay >> Task.ContinueWith() 2 - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");
			var t3 = t2.ContinueWith((arg) =>
			{
				// pop caller 스레드 6 from ThreadPool

				// caller 스레드 6
				Console.WriteLine($"\tEnd myAsyncVoidFuncDelay >> Task.ContinueWith() 2 - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

				// return caller 스레드 6 to ThreadPool
			});

			// caller 스레드 5
			Console.WriteLine($"myAsyncVoidFuncDelay() End - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

			// return caller 스레드 5
		}

		static async Task myAsyncTaskFunc()
		{
			// caller 스레드 1
			Console.WriteLine($"myAsyncTaskFunc() Start - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

			// caller 스레드 1
			Console.WriteLine($"\tStart myAsyncTaskFunc >> Task.Factory.StartNew() - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");
			Task.Factory.StartNew(() =>
			{
				// pop caller 스레드 3 from ThreadPool
								
				Console.WriteLine($"\tEnd myAsyncTaskFunc >> Task.Factory.StartNew() - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

				// return caller 스레드 3 to ThreadPool
			});

			// caller 스레드 1
			Console.WriteLine($"\tStart myAsyncTaskFunc >> await Task.Factory.StartNew() - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

			// return caller 스레드 1
			await Task.Factory.StartNew(() =>
			{
				// pop caller 스레드 5 from ThreadPool

				Console.WriteLine($"\tEnd myAsyncTaskFunc >> await Task.Factory.StartNew() - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

				// push caller 스레드 5 to ThreadPool
			});
			// pop caller 스레드 5 from ThreadPool

			// caller 스레드 5
			Console.WriteLine($"\tStart myAsyncTaskFunc >> var t1 = Task.Factory.StartNew() - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");
			var t1 = Task.Factory.StartNew(() =>
			{
				// pop caller 스레드 4 from ThreadPool

				Console.WriteLine($"\tEnd myAsyncTaskFunc >> var t1 = Task.Factory.StartNew() - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

				// push caller 스레드 4 to ThreadPool
			});

			// caller 스레드 5
			Console.WriteLine($"\t\tStart myAsyncTaskFunc >> Task.ContinueWith() 1 - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");
			var t2 = t1.ContinueWith((arg) =>
			{
				// pop caller 스레드 4 from ThreadPool

				Console.WriteLine($"\t\tEnd myAsyncTaskFunc >> Task.ContinueWith() 1 - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

				// push caller 스레드 4 to ThreadPool
			});

			// caller 스레드 5
			Console.WriteLine($"\t\t\tStart myAsyncTaskFunc >> Task.ContinueWith() 2 - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

			// push caller 스레드 5 to ThreadPool
			await t2.ContinueWith((arg) =>
			{
				// pop caller 스레드 4 from ThreadPool

				Console.WriteLine($"\t\t\tEnd myAsyncTaskFunc >> Task.ContinueWith() 2 - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

				// push caller 스레드 4 to ThreadPool
			});
			// pop caller 스레드 4 from ThreadPool

			// caller 스레드 4
			Console.WriteLine($"myAsyncTaskFunc() End - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

			// push caller 스레드 4 to ThreadPool
		}

		static async Task<Int32> myAsyncTaskInt32Func()
		{
			// caller 스레드 1
			Console.WriteLine($"myAsyncTaskInt32Func() Start - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

			// caller 스레드 1
			Console.WriteLine($"\tStart myAsyncTaskInt32Func >> Task.Factory.StartNew() 1 - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

			// return caller 스레드 1
			var result_1 = await Task<Int32>.Factory.StartNew(() =>
			{
				// pop caller 스레드 3 from ThreadPool

				var result = 10;
				Console.WriteLine($"\tEnd myAsyncTaskInt32Func >> Task.Factory.StartNew() 1 : result:{result} - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");
				return result;

				// push caller 스레드 3 to ThreadPool
			});
			// pop caller 스레드 3 from ThreadPool

			// caller 스레드 3
			Console.WriteLine($"\tStart myAsyncTaskInt32Func >> Task.Factory.StartNew() 2 - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");
			Task.Factory.StartNew(() =>
			{
				// pop caller 스레드 4 from ThreadPool

				Console.WriteLine($"\tEnd myAsyncTaskInt32Func >> Task.Factory.StartNew() 2 - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

				// push caller 스레드 4 to ThreadPool
			});
			// pop caller 스레드 3 from ThreadPool

			// caller 스레드 3
			Console.WriteLine($"\tStart myAsyncTaskInt32Func >> Task.Factory.StartNew() 3 - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");
			// push caller 스레드 3 to ThreadPool
			await Task.Factory.StartNew(() =>
			{
				// pop caller 스레드 6 from ThreadPool

				Console.WriteLine($"\tEnd myAsyncTaskInt32Func >> Task.Factory.StartNew() 3 - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

				// push caller 스레드 6 to ThreadPool
			});
			// pop caller 스레드 6 from ThreadPool

			// caller 스레드 6
			Console.WriteLine($"myAsyncTaskInt32Func() End - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

			// return 스레드 6
			return result_1;
		}

		public class MyResult
		{
			public MyResult(bool isSuccess)
			{
				IsSuccess = isSuccess;
			}

			public MyResult(string userId)
			{
				UserId = userId;
			}

			public bool IsSuccess { get; set; }

			public string UserId { get; set; }
		}

		static async Task<MyResult> myAsyncTaskCustomResultFunc()
		{
			// caller 스레드 1
			Console.WriteLine($"myAsyncTaskCustomResultFunc() Start - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");
			// caller 스레드 1
			Console.WriteLine($"\tStart myAsyncTaskCustomResultFunc >> Task.Factory.StartNew() - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

			// return caller 스레드 1
			var result = await Task<MyResult>.Factory.StartNew(() =>
			{
				// pop caller 스레드 3 from ThreadPool

				var value = new MyResult("Hi justin");
				Console.WriteLine($"\tEnd myAsyncTaskCustomResultFunc >> Task.Factory.StartNew() : result:{value} - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

				return value;

				// push caller 스레드 3 to ThreadPool
			});
			// pop caller 스레드 3 from ThreadPool

			// caller 스레드 3
			Console.WriteLine($"myAsyncTaskCustomResultFunc() End - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

			// return 스레드 3
			return new MyResult(true);
		}

		static async Task<MyResult> myAsyncTaskCustomResultLamdaFunc()
		{
			// caller 스레드 1
			Console.WriteLine($"myAsyncTaskCustomResultLamdaFunc() Start - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

			var result = new MyResult(true);

			// caller 스레드 1
			Console.WriteLine($"\tStart myAsyncTaskCustomResultLamdaFunc >> Task<MyResult>.Run() - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

			// return caller 스레드 1
			result = await Task<MyResult>.Run(async delegate
			{
				// pop caller 스레드 3 from ThreadPool

				Console.WriteLine($"\t\tStart await myAsyncTaskInt32Func() - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");
				var task_result = await myAsyncTaskInt32Func();
				if (task_result == 1)
				{
					result.UserId = "Justin Best !!!";
					result.IsSuccess = true;
				}
				Console.WriteLine($"\t\tEnd await myAsyncTaskInt32Func() - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

				Console.WriteLine($"\tEnd myAsyncTaskCustomResultLamdaFunc >> Task<MyResult>.Run() - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

				// push caller 스레드 5 to ThreadPool
				return result;
			});
			// pop caller 스레드 5 from ThreadPool

			// caller 스레드 5
			Console.WriteLine($"myAsyncTaskCustomResultLamdaFunc() End - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

			// return 스레드 5
			return result;
		}

		static async Task async_and_await_what()
		{
			/*
				C# 5.0부터 새로운 C# 키워드로 async와 await가 추가되었다.
				이 키워드들은 기존의 비동기 프로그래밍 (asynchronous programming)을 보다
				손쉽게 지원하기 위해 C# 5.0에 추가된 중요한 기능이다.

				C# async는 컴파일러에게 해당 메서드가 await를 가지고 있음을 알려주는 역활을 한다.
				async 라고 표시된 메서드는 await를 1개 이상 가질 수 있는데, 하나도 없는 경우라도 컴파일은 가능하지만 Warning 메시지를 표시한다.
				async를 표시한다고 해서 자동으로 비동기 방식으로 프로그램을 수행하는 것은 아니고,
				일종의 보조 역활을 하는 컴파일러 지시어로 볼 수 있다.

				실제 핵심 키워드는 await인데, 이 await는 일반적으로 Task 혹은 Task<T> 객체와 함께 사용된다.
			    Task 이외의 클래스도 사용 가능한데, awaitable 클래스, 즉 GetAwaiter() 라는 메서드를 갖는 클래스이면 함께 사용 가능하다.

				UI 프로그램에서 await는 Task와 같은 awaitable 클래스의 객체가 완료되기를 기다리는데,
				여기서 중요한 점은 UI 쓰레드가 정지되지 않고 메시지 루프를 계속 돌 수 있도록
				필요한 코드를 컴파일러가 await 키워드를 만나면 자동으로 추가한다는 점이다.
				메시지 루프가 계속 돌게 만든다는 것은 마우스 클릭이나 키보드 입력 등과 같은 윈도우 메시지들을 계속 처리할 수 있다는 것을 의미한다.
				await는 해당 Task가 끝날 때까지 기다렸다가 완료 후, await 바로 다음 실행문부터 실행을 계속한다.
				await가 기다리는 Task 혹은 실행 메서드는 별도의 Worker Thread에서 돌 수도 있고, 또는 UI Thread에서 돌 수도 있다.

				Caller 스레드가 await로 작성된 Callee 함수를 만날 경우 다음과 같이 구분하여 처리 한다.
				
			    1. Callee 함수 내부에서 Task 생성 및 실행을 하는 경우
				  1.1. Callee 함수가 Task 반환일 경우 (리턴값 없음) 
				     - Caller 스레드는 Callee 함수 내부에 Task 생성 및 실행 함수를 처리 하게되면
			           ThreadPool 에서 대기중 스레드를 꺼내어 Task 에 등록된 함수를 실행 시키고,
			           함수 처리가 완료 되면 ThreadPool 에 스레드를 반환 한다.			           
			           Callee 함수 처리가 완료 되면 Callee 함수가 반환해 준 스레드로 다음 로직을 실행 한다.
					   현재 Caller 함수에서 리턴된 Caller 스레드가 없는 경우 리턴하여 다음 로직을 실행하고,
			                                       Caller 스레드가 있는 경우 ThreadPool 에 반환 한다.			           
			        				
				  1.2. Callee 함수가 Task<T> 반환일 경우 (리턴값 있음)
				     1.2.1. 현재 함수를 호출한 Caller 함수가 로직에서 await + Callee 함수 + Task<T>값을 반환 받는 경우
			              - Caller 스레드는 Callee 함수 내부에 Task 생성 및 실행 함수를 처리 하게되면
			                ThreadPool 에서 대기중 스레드를 꺼내어 Task 에 등록된 함수를 실행 시켜주고,
						    함수 처리가 완료 되면 ThreadPool 에 스레드를 반환 한다.	
				            Callee 함수 처리가 완료될 때까지 대기 하고 처리가 완료 되면
			                ThreadPool 에서 대기중인 스레드를 꺼내어 다음 로직을 실행 한다. 
						    현재 Caller 함수에서 리턴된 Caller 스레드가 없는 경우 리턴 하고
			                                            Caller 스레드가 있는 경우 ThreadPool 에 반환 한다.
					      
				     1.2.2. 현재 함수를 호출한 Caller 함수가 await + Callee 함수 작성만 한 경우
			              - Caller 스레드는 Callee 함수 내부에 Task 생성 및 실행 함수를 처리 하게되면
			                ThreadPool 에서 대기중 스레드를 꺼내어 Task 에 등록된 함수를 실행 시켜주고,
							함수 처리가 완료 되면 ThreadPool 에 스레드를 반환 하고,
			                ThreadPool 에서 대기중인 스레드를 꺼내어 다음 로직을 실행 한다. 
						    현재 Caller 함수에서 리턴된 Caller 스레드가 없는 경우 리턴하여 다음 로직을 실행하고,
			                                            Caller 스레드가 있는 경우 ThreadPool 에 반환 한다.
			      
			         1.2.3. 현재 함수를 호출한 Caller 함수가 Callee 함수 작성만 한 경우
			              - Caller 스레드는 Callee 함수 내부에 Task 생성 및 실행 함수를 처리 하게되면
			                ThreadPool 에서 대기중 스레드를 꺼내어 Task 에 등록된 함수를 실행 시켜주고,
			                함수 처리가 완료 되면 ThreadPool 에 스레드를 반환 한다.	
			                현재 Caller 스레드로 다음 로직을 실행 한다.
						    현재 Caller 함수에서 리턴된 Caller 스레드가 없는 경우 리턴하여 다음 로직을 실행하고,
			                                            Caller 스레드가 있는 경우 ThreadPool 에 반환 한다.

			    2. Callee 함수 내부에서 Task 생성 및 실행을 하지 않는 경우
			     - 현재 Caller 스레드로 다음 로직을 실행 하고, 반환 한다.
			       
			*/
			{
				Console.WriteLine($"async_and_await_what() Start - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

				//await myAsyncVoidFunc();

				//await myAsyncVoidFuncDelay();

				//await myAsyncTaskFunc();

				//await myAsyncTaskInt32Func();

				//await myAsyncTaskCustomResultFunc();

				//await myAsyncTaskCustomResultLamdaFunc();

				Console.WriteLine($"async_and_await_what() End - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

				//Console.ReadLine();
			}
		}

		static async void async_await_schedule()
		{
			Task t = myAsyncTaskFunc();

			for (int i = 0; i < 10; i++)
			{
				System.Console.WriteLine("Do Something Before myAsyncTaskFunc");
			}

			await t;

			for (int i = 0; i < 10; i++)
			{
				System.Console.WriteLine("Do Something after myAsyncTaskFunc");
			}

			Console.ReadLine();
		}

		static async Task<MyResult> getUserId()
		{
			Console.WriteLine("Try call getUserId() from DB");
			await Task.Delay(5000);
			Console.WriteLine("completed getUserId()");

			return new MyResult("Justin Best !!!");
		}

		static async void async_await_transaction()
		{
			var result = await getUserId();

			Console.WriteLine("Waiting user id !!!");

			var user_id = result.UserId;

			Console.WriteLine("taken value - userId:{0}", user_id);

			Console.ReadLine();

			/*
				Try call getUserId() from DB
				Waiting user id !!!
				completed getUserId()
				taken value - userId:10000        
			*/
		}

		static void Task_or_async_method()
		{
			/*
				C# 5.0과 함께 선보인 .NET 4.5는 기존의 동기화(Synchronous) 메서드들과
				구분하여 C#의 await (혹은 VB의 Await)를 지원하기 위해 많은 Async 메서드들을 추가하였다.
				이 새 메서드들은 기본적으로 기존의 Synchronous 메서드명 뒤에 Async를 붙여 명명되었는데,
				만약 기존에 Async로 끝나는 함수가 이미 있었던 경우에는 TaskAsync를 메서드명에 붙여 명명하였다.

					System.IO.Stream.Read() : 기존 동기 메서드
					System.IO.Stream.ReadAsync() : 4.5 Async 메서드

					WebClient.DownloadStringAsync() : 기존 비동기 메서드
					WebClient.DownloadStringTaskAsync() : 4.5 TaskAsync 메서드
			*/
			{
				Console.ReadLine();
			}
		}

		static void doSleepSync(string caller)
		{
			System.Threading.Thread.Sleep(10000);

			Console.WriteLine($"return doSleepSync() - caller:{caller}");
		}

		static async Task doDelayAsync(string caller)
		{
			await Task.Delay(10000);

			Console.WriteLine($"return doDelayAsync() - caller:{caller}");
		}

		static void doTaskAwaitAfterBlockFunc(string caller)
		{
			var t = Task.Factory.StartNew(() => doSleepSync(caller));
			t.Wait();

			// Task.Wait은 Task가 끝날 때까지 기다리는 블로킹 방식 !!!
			// doSleepSync() 는 블로킹 함수라서 지연 시간 만큼 블록킹 된다.
		}

		static void doTaskAwaitAfterNonBlockFunc(string caller)
		{
			var t = Task.Factory.StartNew(() => doDelayAsync(caller));
			t.Wait();

			// Task.Wait은 Task가 끝날 때까지 기다리는 블로킹 동기화 방식 !!!
			// doDelayAsync() 는 논블로킹 함수라서 지연 시간 만큼 블록되지 않고 반환 된다.
			// 따라서 Task.Wait() 가 블로킹 함수이지만 doDelayAsync() 함수가 즉시 반환되어
			// Task.Wait() 도 바로 반환 하게 된다.
		}

		static async Task doAwaitAfterBlockFunc(string caller)
		{
			var t = Task.Factory.StartNew(() => doSleepSync(caller));
			await t;

			// await은 해당 Task가 완료될 때까지 다른 작업을 진행하다가 작업이 완료되면
			// 해당 작업 이후 남겨진 루틴을 처리하는 논블록킹 방식 !!!

			// doSleepSync() 가 블로킹 함수이지만 호출자 async 와 await 구문에 의해
			// await t 는 논블로킹으로 바로 반환 하게 된다.
		}

		static async Task doAwaitAfterNonBlockFunc(string caller)
		{
			var t = Task.Factory.StartNew(async () => await doDelayAsync(caller));
			await t;

			// await은 해당 Task가 완료될 때까지 다른 작업을 진행하다가 작업이 완료되면
			// 해당 작업 이후 남겨진 루틴을 처리하는 논블록킹 방식 !!!

			// 함수에 남겨진 루틴을 처리하기 위해 await 에 해당되는 작업이 완료되었을 때,
			// 해당 구문으로 돌아가라는 명령을 작업 항목 큐에 삽입하게 된다 !!!
		}

		static async Task TaskWait_vs_await()
		{
			https://stackoverflow.com/questions/9519414/whats-the-difference-between-task-start-wait-and-async-await

			doAwaitAfterNonBlockFunc("doAwaitAfterNonBlockFunc").Wait(); // 함수 내부에서 NonBlockFunc 함수를 호출 및 Task 를 await 하고 있어서 즉시 반환 된다 !!!
			Console.WriteLine("doAwaitAfterNonBlockFunc().Wait() completed");

			await doAwaitAfterNonBlockFunc("await doAwaitAfterNonBlockFunc");
			Console.WriteLine("await doAwaitAfterNonBlockFunc() completed");

			doTaskAwaitAfterNonBlockFunc("doTaskAwaitAfterNonBlockFunc");
			Console.WriteLine("doTaskAwaitAfterNonBlockFunc() completed");

			doAwaitAfterBlockFunc("doAwaitAfterBlockFunc");
			Console.WriteLine("doAwaitAfterBlockFunc() completed");

			doAwaitAfterBlockFunc("doAwaitAfterBlockFunc").Wait(); // 여기서 블록킹 처리 된다. !!!
			Console.WriteLine("doAwaitAfterBlockFunc().Wait() completed");

			doTaskAwaitAfterBlockFunc("doTaskAwaitSync"); // 여기서 블록킹 처리 된다. !!!
			Console.WriteLine("doTaskAwaitSync() completed");

			Console.ReadLine();
		}

		public static async void Test()
		{
			//Console.WriteLine($"AsyncAwait.Test() Start - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");

			//TaskWait_vs_await().Wait();

			//Task_or_async_method();

			//async_await_transaction();

			//async_await_schedule();

			//await async_and_await_what();

			//Console.WriteLine($"AsyncAwait.Test() End - TID:{System.Threading.Thread.CurrentThread.ManagedThreadId}");
		}
	}
}
