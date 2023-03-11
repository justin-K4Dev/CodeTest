using Microsoft.Win32.SafeHandles;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.ComponentModel;
using System.Runtime.InteropServices;


namespace AdvancedStep
{
	// IDisposable 상속 받은 객체
	public class LargeDataClassWithDisposableFinalizer : IDisposable
	{
		private IntPtr m_handle; // 외부 비관리 리소스 핸들
		private Component m_component = new Component(); // 관리 리소스
		private List<IDisposable> m_managed_dispoables = new List<IDisposable>(); // IDisposable 로 관리하기로 한 객체들

		private bool m_disposed = false; // Dispose 가 호출되었는지 확인한다.
		private bool m_is_call_suppress_finalize = true;

		// memory = 4 * 1,000,000 = 4M
		private int[] m_data = new int[1000000];

		public LargeDataClassWithDisposableFinalizer(bool isCallSuppressFinalize)
		{
			m_is_call_suppress_finalize = isCallSuppressFinalize;
		}

		// C# finalizer는 비관리 리소스만 해제 해야한다.
		~LargeDataClassWithDisposableFinalizer()
		{
			Dispose(disposing: false);
		}

		public void Set(int index, int value)
		{
			m_data[index] = value;
		}

		public void Dispose()
		{
			Dispose(disposing: true);

			if(true == m_is_call_suppress_finalize)
			{
				// Finalizer 중복 호출을 방지 한다.
				GC.SuppressFinalize(this);
			}
		}

		protected virtual void Dispose(bool disposing)
		{
			// 이미 리소스가 해제 되었는지 확인
			if (m_disposed == true)
			{
				return;
			}

			try
			{
				// 실제로 사용자가 호출한 경우에만 
				// 관리 리소스를 호출한다.
				if (disposing)
				{
					m_component.Dispose();

					IDisposable[] targets = new IDisposable[m_managed_dispoables.Count];
					m_managed_dispoables.CopyTo(targets);
					foreach (IDisposable each in targets)
					{
						try { each.Dispose(); }
						catch (Exception ex) { /* 예외 로직 구현 */ }
						finally { /* 정리 로직 구현 */}
					}
					m_managed_dispoables.Clear();
				}

				// 비관리 리소스를 해제하기 위해
				// 올바른 함수를 호출한다.
				CloseHandle(m_handle);
				m_handle = IntPtr.Zero;

				// 이제 해당 인스턴스는 모두 해제되었다.
				m_disposed = true;
			}
			finally { /* 정리 로직 구현 */ }
		}

		// Unmanaged 리소스를 해제하는 닷넷의 Interop 인터페이스를 사용한다.
		[System.Runtime.InteropServices.DllImport("Kernel32")]
		private extern static Boolean CloseHandle(IntPtr handle);
	}

	class DerivedLargeDataClass : LargeDataClassWithDisposableFinalizer
	{
		// Flag: Has Dispose already been called?
		private bool m_disposed = false;
		// Instantiate a SafeHandle instance.
		private SafeHandle m_handle = new SafeFileHandle(IntPtr.Zero, true);

		public DerivedLargeDataClass(bool isCallSuppressFinalize)
			: base(isCallSuppressFinalize)
		{

		}

		// Protected implementation of Dispose pattern.
		protected override void Dispose(bool disposing)
		{
			if (true == m_disposed)
			{
				return;
			}

			if (disposing)
			{
				m_handle.Dispose();
				// Free any other managed objects here.
				//
			}

			// Free any unmanaged objects here.
			//

			m_disposed = true;
			// Call base class implementation.
			base.Dispose(disposing);
		}
	}

	// 대량 데이타 필드를 가진 클래스
	class LargeDataClassWithIDisposable : IDisposable
	{
		private Component m_component = new Component(); // 관리 리소스
		private List<IDisposable> m_managed_dispoables = new List<IDisposable>(); // IDisposable 로 관리하기로 한 객체들

		private bool m_disposed = false; // Dispose 가 호출되었는지 확인한다.
		private bool m_is_call_suppress_finalize = true;

		// memory = 4 * 1,000,000 = 4M
		private int[] m_data = new int[1000000];

		public LargeDataClassWithIDisposable(bool isCallSuppressFinalize)
		{
			m_is_call_suppress_finalize = isCallSuppressFinalize;
		}

		public void Set(int index, int value)
		{
			m_data[index] = value;
		}

		public void Dispose()
		{
			Dispose(disposing: true);

			if (true == m_is_call_suppress_finalize)
			{
				// Finalizer 중복 호출을 방지 한다.
				GC.SuppressFinalize(this);
			}
		}

		protected virtual void Dispose(bool disposing)
		{
			// 이미 리소스가 해제 되었는지 확인
			if (m_disposed == true)
			{
				return;
			}

			try
			{
				// 실제로 사용자가 호출한 경우에만 
				// 관리 리소스를 호출한다.
				if (disposing)
				{
					m_component.Dispose();

					IDisposable[] targets = new IDisposable[m_managed_dispoables.Count];
					m_managed_dispoables.CopyTo(targets);
					foreach (IDisposable each in targets)
					{
						try { each.Dispose(); }
						catch (Exception ex) { /* 예외 로직 구현 */ }
						finally { /* 정리 로직 구현 */}
					}
					m_managed_dispoables.Clear();
				}

				// 비관리 리소스를 해제하기 위해
				// 올바른 함수를 호출한다.

				// 이제 해당 인스턴스는 모두 해제되었다.
				m_disposed = true;
			}
			finally { /* 정리 로직 구현 */ }
		}
	}

	// 대량 데이타 필드를 가진 클래스
	class LargeDataClass
    {
        // memory = 4 * 1,000,000 = 4M
        private int[] m_data = new int[1000000];

        public void Set(int index, int value)
        {
			m_data[index] = value;
        }
    }

	public class RefA
	{
		public RefB m_instanceB;
		public int m_a;
	}

	public class RefB
	{
		public RefA m_instanceA;
		public int m_b;
	}

	public class EventPublisher
	{
		public delegate void FireEvent();
		public event FireEvent Fire;

		protected void OnFire()
		{
			if (Fire != null)
			{
				Fire();
			}
		}

		~EventPublisher()
		{
			Console.WriteLine("~EventPublisher() Called");
		}
	}

	public class EventSubscriber
	{
		public void DoFire()
		{
		}

		~EventSubscriber()
		{
			Console.WriteLine("~EventSubscriber() Called");
		}
	}

	public class LeakTimer : IDisposable
	{
		private System.Timers.Timer m_timer = null;

		public LeakTimer(double intervalMSec)
		{
			m_timer = new System.Timers.Timer() { Interval = intervalMSec };
			m_timer.Elapsed += onElapsed;	
			m_timer.Start();
		}

		~LeakTimer()
		{
			Console.WriteLine("~LeakTimer() Called");
			Dispose();
			Console.ReadLine();
		}

		public void Dispose()
		{
			Console.WriteLine("LeakTimer.Dispose() Called");
			m_timer.Dispose();
		}

		// static funtion 으로 변경하면 => private static void onElapsed(), ~LeakTimer() 함수가 호출된다. !!!
		// static funtion 으로 변경하지 않으면 ~LeakTimer() 함수가 호출되지 않는다. !!!
		private static void onElapsed(object sender, System.Timers.ElapsedEventArgs e)
		{
			Console.WriteLine("System.Timers.Timer Elapsed !!!");
		}
	}

	public class NoLeakTimer
	{
		private System.Threading.Timer m_timer = null;

		public NoLeakTimer(Int32 intervalMSec)
		{
			m_timer = new System.Threading.Timer(onElapsed, null, 0, intervalMSec);
		}

		~NoLeakTimer()
		{
			Console.WriteLine("~NoLeakTimer() Called");
			Dispose();
			Console.ReadLine();
		}

		public void Dispose()
		{
			Console.WriteLine("NoLeakTimer.Dispose() Called");
			m_timer.Dispose();
		}

		private void onElapsed(object state)
		{
			Console.WriteLine("System.Threading.Timer Elapsed !!!");
		}
	}

	public class Memory
    {
		static EventPublisher m_publisher = new EventPublisher();

		static void GC_what()
		{
			/*
				1. CLR(Common Language Runtime)의 Heap 관리

			      1.1. GC(Garbage Collector)의 메모리 관리

			        URL : http://www.simpleisbest.net/post/2011/04/01/Review-NET-Garbage-Collection.aspx

			        1.1.1. GC의 메모리 할당 방식 
			          * 선형 메모리 할당 방식(Linear Memory Allocation)을 사용 한다.
			          * GC는 메모리 영역에 VirtualAlloc()을 이용해 예약하고 이 한 개의 단위를 Segment라 한다.
			          * Segment라 불리는 메모리의 크기는 시스템 환경에 따라 다르다. 
			          * GC는 필요한 만큼 Segment를 할당할 수 있고, 필요 없어지면 VirtualFree()로 OS에 반납 한다.
			          * C/C++와 다른점은 메모리 첫영역부터 차례대로 할당하게 되고 할당이 가능한 부분의 첫 주소에 포인터로 가르키게 된다.
			            다음에 또 객체를 생성하면 할당 가능한 메모리의 포인터 영역부터 메모리를 할당하고
			            다시 해당 포인터는 할당된 사이즈 만큼 증가하게 된다.
			          * 이렇게 하면 Heap에 메모리 할당이 가능한 영역을 찾을 필요가 없어 C/C++ 보다 훨씬 더 빠르다.
			          * 메모리 할당시 메모리 조각 현상(메모리 단편화)이 발생하지 않는다.
			        
			        1.1.2. GC의 메모리 해제 방식 
			          * Root Reference(static, stack, register 등등) 메모리 영역에서 사용하는 메모리 영역을 관리하게 되고, 객체에서 할당한 객체도 존재 한다. 
			            Root Reference를 탐색하여 할당된 객체들 찾아 낸다.
			          * 메모리를 해제할 경우 GC 모드에 따라 Thread의 수행/중단 되는 방식이 다르다.
			          * 메모리가 해제된 후 남은 Heap의 빈 공간은 사용중인 메모리로 채워진다.(메모리 조각 현상이 발상해지 않는 이유 !!!)
			            - 객체를 제거하는 것을 스웹(Sweap), 객체를 붙여 빈 공간을 늘이는 것을 재배치(Compaction)라고 한다.
                      * 사용중인 객체를 찾기 위해 RRG(Root Reference Graph)를 만든다.
                        - 각 Thread가 수행중인 메서드의 스택 변수, 전역 변수, CPU 레지스터 변수, 클래스의 정적 필드 등을 이용하여 만든다.
                        - 해당 그래프에 포함되지 않는 객체는 GC의 대상으로 표시(Mark) 된다.

			        1.1.3. GC의 기본 동작 방식
			          * GC가 수행되기 전, GC를 발생시킨 스레드를 제외한 다른 모드 스레드들은 정지 합니다.
			          * 소멸자(finalizer)가 정의된 객체가 생성된 경우
			            - 특별히 종료 큐(Finalization Queue)에 객체를 함께 등록합니다.
			            - 그와 함께 해당 객체는 다음 세대로 살아남는 효과가 적용됩니다.
			              왜냐하면, 그 객체에 대한 참조를 종료 큐에서 가지고 있는 것과 같기 때문입니다.
			              (따라서, GC 생존을 결정하는 것은 "Stack roots, Garbage Collection Handles, Static data" 뿐만 아니라 종료 큐도 체크 대상이 됩니다.)
			          * 종료 큐 이외의 참조가 없어진 경우
			            - GC는 종료 큐로부터 객체를 꺼내 Freachable 큐에 다시 객체를 보관합니다. 
			          * 그리고 Freachable 큐에 보관된 객체는 CLR이 미리 생성해 둔 스레드에 의해 꺼내지고 소멸자가 호출 됩니다.
			          * 이런 과정이 완료되고서야 마침내 다음 GC 수행이 되었을 때 비로소 Managed Heap에서 객체가 삭제 됩니다.
			          * CLR은 응용 프로그램의 working set 메모리가 너무 크지 않게, GC의 동작 시간이 너무 길지 않게 조정하는 역할을 한다.
                      * GC는 생존 개체에 대한 결정을 "Stack roots", "GC Handles", "Static data"를 근간으로 판단하는데,
                        - Stack roots: Stack variables provided by the just-in-time (JIT) compiler and stack walker.
                        - Garbage collection handles: Handles that point to managed objects and that can be allocated by user code or by the common language runtime.
                        - Static data: Static objects in application domains that could be referencing other objects.
			                           Each application domain keeps track of its static objects.
			          * .NET 3.5 이하에서는 다음과 같은 2가지 모드의 GC가 있었다.
			            - Workstation Non-Concurrent GC
			            - Workstation Concurrent GC
			          
			          
			      1.2. GC(Garbage Collector)의 작동

			        * 객체를 할당하여 할당하는 임계치가 넘어갈 때
			          - 각 세대에는 할당 임계치(Budget)가 있다.
			        * GC.Collect() 메서드를 호출할 때
			        * 시스템의 메모리가 부족할 때
			        
			      1.3. 세대별 GC(Generational Garbage Collection)

                    * CLR의 GC 처리의 최적화 기법
                    * 관리되는 Heap의 객체를 객체들의 생존시간에 따라 세대로 구분하여 GC를 수행하는 것을 의미 한다.
					* Heap에 할당할 공간이 부족하거나(메모리 부족) GC 명령어로 동작시킬 수 있다.
                    * 객체를 할당될 때 0세대가 된다.
                    * GC가 실행되고 해제되지 않은 메모리는 세대가 하나 올라간다
                      - 0세대에서 해제되지 않은 메모리 -> 1세대로 상승
                    * GC는 0세대부터 2세대까지 순서대로 발생한다.

			        1.3.1. 0세대 작동 절차
			          1.3.1.1. 메모리 할당 발생
			          1.3.1.2. 0세대 GC 작동 조건이 충족되면 작동
			          1.3.1.3. 메모리 해제 대상 객체 탐색 및 표시(Mark)
			          1.3.1.4. 표시된 객체들을 스웹(Sweap), Heap 내의 빈 공간을 채우는 재배치(Compaction) 진행
			          1.3.1.5. 0세대에 유지되고 있는 객체들은 1세대로 상승
			        
			        1.3.2. 1세대 작동 절차
			          - 객체가 지속적으로 할당되고 해제가 된다면 0세대 객체를 할당할 수 있는 공간은 줄어들고,
			            1세대 객체가 차지하는 공간은 점점 늘어나게 된다.
			          1.3.2.1. 1세대 객체가 늘어나며 Heap의 크기가 줄어든다면 1세대 GC 작동
			          1.3.2.2. 메모리 해제 대상 객체 탐색 및 표시(Mark)
			          1.3.2.3. 표시된 객체들을 스웹(Sweap), Heap 내의 빈 공간을 채우는 재배치(Compaction) 진행
                      1.3.2.4. 1세대에 유지되고 있는 객체들은 2세대로 상승

			        1.3.3. 2세대 작동 절차
			          1.3.3.1. 1세대 GC 수행 후 0세대의 메모리 공간에 여유가 없을 경우 2세대 GC 작동
			          1.3.3.2. 메모리 해제 대상 객체 탐색 및 표시(Mark)
			          1.3.3.3. 표시된 객체들을 스웹(Sweap), Heap 내의 빈 공간을 채우는 재배치(Compaction) 진행
			            - 2세대 GC의 작동은 사실상 전체 Heap 을 접근하게 되므로 많은 비용을 소모할 가능성이 있다.
			          
			      1.4. SOH(Small Object Heap) : 85K 미만의 용량이 작은 객체 할당
			        - 각 세대별 GC(Garbage Collector)에 의해서 메모리 할당과 해제가 처리 된다.
               
			      1.5. LOH(Large Object Heap) : 85K 이상의 용량이 큰 객체 할당
			        * C/C++ 에서 동적 메모리 할당(malloc, new), 해제(free, delete)와 유사한 방식으로 처리 된다.
			        * C/C++ 메모리 관리와 유사한 방식으로 처리 하는 이유는
			          용량이 큰 객체들의 Heap 내의 메모리 재배치(Compaction) 처리 비용이 너무 비싸기 때문에
			          메모리 할당을 요청하면 Heap 있는 빈 공간을 찾아 할당하고,
			          해제를 요청하면 해제만 할 뿐 기본적으로 재배치(Compaction)를 실행하지 않는다.
			        * .NET 4.5.1 이후 GCSettings.LargeObjectHeapCompactionMode 속성을 이용해 재배치(Compaction)가 가능하게 되었다.
                    * SOH는 0 ~ 2세대가 존재하지만 LOH는 2세대만 존재 한다.
			        * LOH에 많은 할당이 이루어지면 2세대 GC가 작동 한다.
			          - 2세대 GC가 작동하면 처리가 지연 된다.
			        * LOH는 GCSettings.LargeObjectHeapCompactionMode 를 활성화 하지 않을 경우 메모리 조각 현상(단편화)이 발생 한다.
			          
			
				2. Workstation GC
				  * GC Managed Heap은 EXE 프로세스 당 1개가 생성 된다.
                    당연히 EXE 프로세스 내의 모든 스레드는 그 하나의 Heap에 관리 개체를 할당하게 됩니다.

				  2.1. Workstation GC의 경우 다시 Concurrent 기능 유무에 따라 다음과 같이 나뉜다.
				    2.1.1. Workstation Non-Concurrent GC : 1 heap
			          * GC가 수행되기 전, GC를 발생시킨 Thread를 제외한 모든 Thread를 정지(Suspend)시킨다.
			          * GC을 유발한 Thread에서 GC를 수행한다.
			          * GC를 실행하는 동안 모든 Thread가 정지되기 때문에 GC가 길어질수록 프로그램이 멈춰있는 시간이 길다.
			          * N-Core CPU가 일반적인 현재 서버에는 거의 사용하지 않는 방식 이다.

                    2.1.2. Workstation Concurrent GC : 1 heap and 1 Dedicated GC Thread
			          * 윈폼/윈도우 서비스 프로그램을 위한 기본 설정값 이다.
			          * Thread들의 중단 시간을 최소화하여 프로그램의 응답 시간을 향상시키기 위해 사용 한다.
			          * 0, 1, 2세대와 상관없이 GC 작업이 수행되면 다른 모든 Thread의 수행을 중지 되지만,
                        0, 1세대에 대해서만 GC를 유발한 Thread가 GC 작업을 수행하다가
			            2세대 Heap 메모리를 GC하는 동안에는 다른 모든 Thread의 실행을 제개하고 별도의 Dedicated GC Thread로 넘겨 GC 작업을 처리한다.
			          * Dedicated GC Thread가 2세대 힙 영역을 정리하는 동안, 다른 Thread들이 0,1 세대에 객체를 할당하다 보면
			            다시 수명이 짧은 객체들의 용량을 모두 소비할 수도 있는 상황이 올 수 있고, 그럼 어쩔 수 없이 모든 Thread들이 중지 된다.
			            Workstation-Concurrent-GC.png 와 같은 상황이 발생할 수 있다 !!!.
			          * .NET 4.0이 등장하며 Background GC가 도입 및 기본설정이 되었다.

			        2.1.3. Workstation Background GC : 1 heap and 1 Dedicated GC Thread
			          * .NET 4.0에서 도입되었다. 기존의 Workstation Concurrent GC 를 대체 한다.
					  * Dedicated GC Thread가 2세대 Heap 공간을 정리하는 동안 0 ~ 1세대의 객체를 할당하여 공간이 다시 차게 된다면,
                        2세대의 Heap 정리를 멈추고 다시 0 ~ 1세대를 Heap 정리를 한 후 2세대 정리를 재개 하게 된다.
			          * Background GC에서 새롭게 "Foreground GC"라는 용어가 생기는데, 이것은 2세대 Heap을 정리하는 동안 수행되는 0,1세대 Heap의 정리를 하는 GC를 의미 한다.
                      * Concurrent GC에 비해 프로그램의 응답시간이 좋아질 수 있지만, Thread들의 중단이 좀 더 자주 발생할 수 있다.

				  2.2. Workstation GC 모드 설정 방법
				    - app.config 파일에 하기와 같이 설정 한다.
						<configuration>
							<runtime>
								<gcServer enabled="false" />
								<gcConcurrent enabled="true"/> <= Non-Concurrent : enabled="false"
							</runtime>
						</configuration>


				3. Server GC
			      * 다중 프로세서에서만 허용 되고, 단일 프로세서일 경우 Workstation Non-Concurrent GC 가 허용 된다.
			      * Server GC는 Workstation GC보다 메모리 할당 Segment 크기를 더 늘릴 수 있다.
				  * 논리 프로세서 1개당 1개의 Dedicated GC Thread, Managed Heap 생성 된다.
                    - 예를 들어, "쿼드 코어"에서 "Hyper Threading"이 활성화 되어 있다면 총 8개의 논리 프로세서가 있으므로 8개의 Dedicated GC Thread, Managed Heap 생성 한다.
                      일단 힙이 n개 생성되면, 이후 프로세스가 종료하는 동안 그 수는 변경되지 않는다.
                  * 주의할 점은, Server GC가 프로세서 당 Dedicated GC 스레드를 갖기 때문에
                    시스템에 Server GC를 사용하는 EXE 프로세스가 많은 경우 자원 소비가 클 수 있다.
			        예를 들어, 4-Core에 Server GC를 사용하는 12개의 EXE 프로세스가 있다면
			        총 48개의 Dedicated GC Thread가 생성되고, 전체적인 시스템 메모리 부족 현상으로 진입하게 되는 경우
			        자칫 48개의 Decaited GC Tread가 구동되며 더욱 큰 부하를 가져오게 된다.
                  * Dedicated GC Thread는 THREAD_PRIORITY_HIGHEST 우선 순위로 설정 되어 있다.

                  * Heap 간의 참조 가능
                    - 예를 들어, 1번 Heap에 있는 객체는 2번 Heap에 있는 객체를 참조하는 것이 가능 하다.

                  * GC Heap에 대한 정리 작업이 동시에 수행 된다.
                    - Workstation GC 모드에서는 2개의 Thread가 객체를 할당할 때 한 개의 Thread가 할당하는 동안 다른 Thread는 멈춰 있어야 했다.
			          하지만 Server GC는 병렬적으로 할당이 가능하며 Thread의 중단이 발생하지 않는다.
                      예를들어 2개의 GC Thread, Managed Heap이 있고 그것들의 총 용량이 100MB일 때 이상적인 경우 각각 50MB씩 GC 수행 작업이 동시에 수행 된다.
                      따라서, Workstation GC라면 100MB GC 작업에 10초가 걸렸다면 Server GC는 5초만에 완료 가능 하다.
			        - GC가 실행되면 모든 Thread를 중단하고 GC Thread를 불러와 작업을 수행한다.
			          작업을 수행하는 시간이 약간씩 차이가 있으며, 모든 Thread의 작업이 완료되어야 프로그램이 재개된다.
                      Heap을 빠르게 정리할 수 있지만 32bit 운영체제에서는 가상 메모리 부족 현상이 발생할 수도 있다.
			      
			      3.1. Server Non-Concurrent GC : 1 heap and 1 Dedicated GC Thread Processor Core or Hyper Threading
			        * Server GC는 .NET 4.5 미만에서는 "Non-Concurrent" 유형만 제공되는데,
			          Workstation Non-Concurrent GC와 다른 점은 논리 프로세서마다 GC Heap과 Dedicated GC Thread가 생성되므로,
			          GC 수행시 모든 Dedicated GC Thread가 함께 각각 맡은 GC Heap을 정리하며,
			          그 외의 다른 모든 Thread들은 정지시킨다는 특징이 있다.

			      3.2. Server Background GC : 1 heap and 1 Dedicated GC Thread Processor or Hyper Threading
			        * .NET 4.5에서 도입되었다.
					* GC Thread가 2세대 Heap 공간을 정리하는 동안 0 ~ 1세대의 객체를 할당하여 공간이 다시 차게 된다면,
                      2세대의 Heap 정리를 멈추고 0 ~ 1세대를 정리 한 후 2세대를 정리 한다.
                    * Concurrent GC에 비해 프로그램의 응답시간이 좋아질 수 있지만, Thread들의 중단이 좀 더 자주 발생할 수 있다.
                  
				  3.3. Server GC 모드 설정 방법				
				    - app.config 파일에 하기와 같이 설정 한다.
						<configuration>
							<runtime>
								<gcServer enabled="true" /> <= Non-Concurrent : enabled="false"
							</runtime>
						</configuration>

			*/
		}

		static void GC_generation()
		{
			object obj1 = new object();   // Gen 0에 객체 할당
			Console.WriteLine("Allocation obj1 ..............................\n");
			Console.WriteLine("Generation of obj1 : {0}", GC.GetGeneration(obj1)); 
			 
			GC.Collect(0);	// Gen 0 Collection (default GC behavior)
			Console.WriteLine("GC 0 ---------------------");  
			Console.WriteLine("Generation of obj1 : {0}", GC.GetGeneration(obj1));
			 
			GC.Collect(1);	// Gen 1 Collection
			Console.WriteLine("GC 1 ---------------------");
			Console.WriteLine("Generation of obj1 : {0}", GC.GetGeneration(obj1));
			 
			GC.Collect(2);	// Gen 2 Collection (full collection)
			Console.WriteLine("GC 2 ---------------------");  
			Console.WriteLine("Generation of obj1 : {0}", GC.GetGeneration(obj1));

			Console.ReadLine();
			/*
				Allocation obj1 ..................................
				
				Generation of obj1 : 0
				GC 0 ---------------------
				Generation of obj1 : 1
				GC 1 ---------------------
				Generation of obj1 : 2
				GC 2 ---------------------
				Generation of obj1 : 2			 
			*/
		}

		static void Run()
        {
            var obj = new LargeDataClass();
            obj.Set(1, 10);
        }

        static void memory_GC()
        {
			/*
                특정 메서드나 특정 코드 블럭이 얼마만큼의 메모리를 사용하는 지를 체크하기 위해서는
                Garbage Collector (GC) 클래스의 보조 메서드들을 사용할 수 있다.
                GC 클래스의 GetTotalMemory() 메서드는 현재 프로세스가 사용하는 Managed Memory의 메모리 용량을 리턴한다.
                따라서, 특정 코드 블력 실행 전과 실행 후의 메모리를 구하여 해당 코드 블럭이 사용한 메모리를 구할 수 있다.
                또한, 더 이상 사용하지 않는 객체들을 GC가 즉시 메모리에서 없애게 하기 위해
                GC.Collect()를 사용할 수 있다 (이는 주로 메모리 테스팅에 사용한다).
                아래 예제는 특정 메서드를 호출하기 전과 후의 메모리 용량을 출력해 주고,
                강제로 메모리 해제를 실행한 후 남는 메모리 용량을 출력해 준다.
            */
			{
				// 초기 메모리
				long mem = GC.GetTotalMemory(false);
                Console.WriteLine("memory_GC() => Initial Memory: {0}", mem);

				System.Diagnostics.Stopwatch watch = new System.Diagnostics.Stopwatch();
				watch.Start();

				for (var i = 0; i < ALLOC_COUNT; i++)
				{
					// 특정 함수 호출
					Run();
				}

				// 함수 호출후 메모리
				mem = GC.GetTotalMemory(false);
				Console.WriteLine("Current Memory: {0}", mem);

				watch.Stop();
				Console.WriteLine("memory_GC() => Allocated ElapsedTime {0}", watch.Elapsed.ToString());

				watch.Start();
				// 메모리 Clean Up 
				GC.Collect();
				GC.WaitForPendingFinalizers();
				GC.Collect();
				watch.Stop();
				Console.WriteLine("GC clean up ElapsedTime {0}", watch.Elapsed.ToString());

				// 메모리 Clean Up 후 
				mem = GC.GetTotalMemory(false);
                Console.WriteLine("After GC Memory: {0}", mem);

				Console.ReadLine();

				/*
					memory_GC() => Initial Memory: 4066656
					Current Memory: 4058536
					memory_GC() => Allocated ElapsedTime 00:00:05.8373610
					GC clean up ElapsedTime 00:00:05.8375140
					After GC Memory: 66712
				*/
			}
		}


		private static void callStaticEventFire()
		{
			EventSubscriber subscriber = new EventSubscriber();
			m_publisher.Fire += subscriber.DoFire;

			// memory leak 을 해결하려면 이벤트 체인을 분리해 준다 !!!
			m_publisher.Fire -= subscriber.DoFire;
		}

		private static void callEventFire()
		{
			EventPublisher publisher = new EventPublisher();
			EventSubscriber subscriber = new EventSubscriber();
			publisher.Fire += subscriber.DoFire;
		}

		private static void startLeakTimer()
		{
			var timer = new LeakTimer(1000);
			System.Threading.Thread.Sleep(10000);
		}

		private static void startNoLeakTimer()
		{
			var timer = new NoLeakTimer(1000);
			System.Threading.Thread.Sleep(10000);
		}

		static void memory_leak()
		{
			// System.Threading.Timer
			{
				startNoLeakTimer();

				// 메모리 Clean Up 
				GC.Collect();
				GC.WaitForPendingFinalizers();
				GC.Collect();

				Console.ReadLine();
				/*
					System.Threading.Timer Elapsed !!!
					~NoLeakTimer() Called
					NoLeakTimer.Dispose() Called
				*/
			}

			// System.Timers.Timer
			{
				startLeakTimer();

				// 메모리 Clean Up 
				GC.Collect();
				GC.WaitForPendingFinalizers();
				GC.Collect();

				Console.ReadLine();
				/*
				    System.Timers.Timer Elapsed !!!
					~LeakTimer() Called
					LeakTimer.Dispose() Called
				*/
			}

			{
				callEventFire();

				// 메모리 Clean Up 
				GC.Collect();
				GC.WaitForPendingFinalizers();
				GC.Collect();

				Console.ReadLine();
				/*
					~EventPublisher() Called
					~EventSubscriber() Called
				*/
			}

			// memory leak !!! : m_publisher.Fire
			{
				callStaticEventFire();

				// 메모리 Clean Up 
				GC.Collect();
				GC.WaitForPendingFinalizers();
				GC.Collect();

				Console.ReadLine();
				/*
					~EventSubscriber() Called
				*/
			}
		}

		static void memory_IDisaposalWithUsing()
		{
			// 초기 메모리
			long mem = GC.GetTotalMemory(false);
			Console.WriteLine("memory_IDisaposalWithUsing() => Initial Memory: {0}", mem);

			System.Diagnostics.Stopwatch watch = new System.Diagnostics.Stopwatch();
			watch.Start();

			for (var i = 0; i < ALLOC_COUNT; i++)
			{
				using (var obj_with_IDisaposable = new LargeDataClassWithIDisposable(false))
				{
				}
			}

			// 함수 호출후 메모리
			mem = GC.GetTotalMemory(false);
			Console.WriteLine("Current Memory: {0}", mem);

			watch.Stop();
			Console.WriteLine("memory_IDisaposalWithUsing() => Allocated ElapsedTime {0}", watch.Elapsed.ToString());

			watch.Start();
			// 메모리 Clean Up 
			GC.Collect();
			GC.WaitForPendingFinalizers();
			GC.Collect();
			watch.Stop();
			Console.WriteLine("GC clean up ElapsedTime {0}", watch.Elapsed.ToString());

			// 메모리 using Block 을 벋어난 후 
			mem = GC.GetTotalMemory(false);
			Console.WriteLine("After GC Memory: {0}", mem);

			Console.ReadLine();

			/*
				memory_IDisaposalWithUsing() => Initial Memory: 4066488
				Current Memory: 40862760
				memory_IDisaposalWithUsing() => Allocated ElapsedTime 00:00:29.4667503
				GC clean up ElapsedTime 00:00:29.4668764
				After GC Memory: 4066656
			*/
		}


		static Int32 ALLOC_COUNT = 100000;

		static void memory_IDisaposalFinalizerWithUsing()
		{
			// 초기 메모리
			long mem = GC.GetTotalMemory(false);
			Console.WriteLine("memory_IDisaposalFinalizerWithUsing() => Initial Memory: {0}", mem);

			System.Diagnostics.Stopwatch watch = new System.Diagnostics.Stopwatch();
			watch.Start();

			for (var i = 0; i < ALLOC_COUNT; i++)
			{
				using (var obj_with_IDisaposable = new DerivedLargeDataClass(true))
				{

				}
			}

			// 함수 호출후 메모리
			mem = GC.GetTotalMemory(false);
			Console.WriteLine("Current Memory: {0}", mem);

			watch.Stop();
			Console.WriteLine("memory_IDisaposalFinalizerWithUsing() => Allocated ElapsedTime {0}", watch.Elapsed.ToString());

			watch.Start();
			// 메모리 Clean Up 
			GC.Collect();
			GC.WaitForPendingFinalizers();
			GC.Collect();
			watch.Stop();
			Console.WriteLine("GC clean up ElapsedTime {0}", watch.Elapsed.ToString());

			// 메모리 using Block 을 벋어난 후 
			mem = GC.GetTotalMemory(false);
			Console.WriteLine("After GC Memory: {0}", mem);

			Console.ReadLine();

			/*
				memory_IDisaposalFinalizerWithUsing() => Initial Memory: 55928
				Current Memory: 40169744
				memory_IDisaposalFinalizerWithUsing() => Allocated ElapsedTime 00:00:23.0729517
				GC clean up ElapsedTime 00:00:23.0738474
				After GC Memory: 4066488
			*/
		}

		static void callCrossRef(ref WeakReference wrA, ref WeakReference wrB)
		{
			RefA a = new RefA();
			RefB b = new RefB();

			// 상호 약한 참조를 설정 한다.
			wrA = new WeakReference(a);
			wrB = new WeakReference(b);

			a.m_instanceB = b;
			a.m_a = 5;
			b.m_instanceA = a;
			b.m_b = 6;
		}

		static void memory_WeakReferene()
		{
			WeakReference wr_a = null;
			WeakReference wr_b = null;

			callCrossRef(ref wr_a, ref wr_b);

			// 메모리 Clean Up 
			GC.Collect();
			GC.WaitForPendingFinalizers();
			GC.Collect();

			// wr_a.Target & wr_b.Target is null
			// GC 에 의해 RefA, RefB 가 메모리 해제 되었다 !!!
			if (true == wr_a.IsAlive && true == wr_b.IsAlive)
			{
				Console.WriteLine((wr_a.Target as RefA).m_a);
				Console.WriteLine((wr_b.Target as RefB).m_b);
			}

			Console.ReadLine();
		}


		public static void Test()
        {
			//memory_WeakReferene();

			//memory_IDisaposalFinalizerWithUsing();

			//memory_IDisaposalWithUsing();

			//memory_leak();

			//memory_GC();

			//GC_generation();

			//GC_what();
		}
	}
}
