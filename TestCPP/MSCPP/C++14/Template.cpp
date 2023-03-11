#include "stdafx.h"

#include <chrono>
#include <memory>
#include <new>
#include <array>
#include <vector>
#include <map>
#include <type_traits>
#include <utility>
#include <functional>
#include <tuple>

#include <typeinfo>
#include <typeindex>

namespace Template
{
	template<typename... Targs>
	constexpr auto make_array(Targs&&... tArgs) -> std::array<std::common_type_t<Targs...>, sizeof...(tArgs)>
	{
		return { std::forward<Targs>(tArgs)... };
	}

	void make_array()
	{
		auto b = make_array( 1, 2, 3 );
		std::cout << b.size() << '\n';
		for (auto i : b) {
			std::cout << i << ',';
		}
		
		std::cout << std::endl;

		system("pause");

		/*
		output:
			3,
			1,2,3
		*/
	}


	void PrintFormat(const char* format) // base function
	{
		std::cout << format;
	}

	// variadic template
	template<typename T, typename... Targs>
	void PrintFormat(const char* format, T value, Targs... tArgs) // recursive variadic function
	{
		// sizeof... : get operator size of Parameter Pack
		// std::cout << sizeof...(Targs);
		// std::cout << sizeof...(tArgs);

		for (; *format != '\0'; ++format) {
			if (*format == '%') {
				std::cout << value;

				// if you put ... after the pack, you can pass it to other functions.
				PrintFormat(format + 1, tArgs...); // recursive call
				return;
			}

			std::cout << *format;
		}
	}

	struct CustomInfo
	{ };

	class ParameterChecker
	{
	public:
		std::vector<std::type_index> parameterTypeList;

		template <typename... ParamList>
		void SetParams()
		{
			parameterTypeList.insert(parameterTypeList.begin(), { typeid(ParamList)... });
		}

		template <typename... ParamList>
		bool IsMatchedParams()
		{
			std::vector<std::type_index> typeList;
			typeList.insert(typeList.begin(), { typeid(ParamList)... });

			return parameterTypeList == typeList;
		}
	};

	void variadic_template_typeid()
	{
		ParameterChecker params;

		params.SetParams<int, float, CustomInfo>();

		std::cout << params.IsMatchedParams<int, float, CustomInfo>() << std::endl;
		std::cout << params.IsMatchedParams<int, float, std::string>() << std::endl;

		system("pause");

		/*
		output:
			1
			0
		*/
	}


	void variadic_template_1()
	{
		// variadic template - Parameter pack
		{
			PrintFormat( "CharName:%, ClassType:%, Level:%\n"
				       , "jason", "human", 45 );

			system("pause");

			/*
			output:
				CharName:jason, ClassType:human, Level:45
			*/
		}
	}


	template <class T1, class T2>
	bool isOneOf(T1&& a, T2&& b)
	{
		printf("Call isOneOf(%d, %d)\n", a, b);
		return a == b;
	}
	template <class T1, class T2, class... Ts>
	bool isOneOf(T1&& a, T2&& b, Ts&& ... vs)
	{
		printf("Call isOneOf(%d, %d ...)\n", a, b);
		return a == b || isOneOf(a, vs...);
	}

	void variadic_template_2()
	{
		// variadic template
		{
			bool res;

			res = isOneOf(1, 2, 3, 4, 5, 6);
			res = isOneOf(1, 1);

			system("pause");

			/*
			output:
				Call isOneOf(1, 2 ...)
				Call isOneOf(1, 3 ...)
				Call isOneOf(1, 4 ...)
				Call isOneOf(1, 5 ...)
				Call isOneOf(1, 6)
				Call isOneOf(1, 1)
			*/
		}
	}


	int f(int a) { return a + 1; }

	template <typename... Types>
	void func1(Types... args)
	{
		std::cout << "func1" << std::endl;
	}

	void func2(int a, int b, int c)
	{
		std::cout << "func2 " << a << b << c << std::endl;
	}

	template <typename... Types>
	void foo(Types... args)
	{
		//1. sizeof...() 키워드
		std::cout << sizeof...(Types) << std::endl;
		std::cout << sizeof...(args) << std::endl;

		//2. parameter pack을 다른 함수로 보내는 코드 (...이 이름 뒤에 따라 붙음)
		func1(args...);

		//3. pack expansion - parameter pack에 있는 내용을 풀어서 전달
		func2(args...);
		func2(f(args)...); //< func2(f(1), f(2), f(3))
	}

	void variadic_template_3()
	{
		foo(1, 2, 3);

		system("pause");

		/*
		output:
			3
			3
			func1
			func2 123
			func3 234
		*/
	}


	template<typename T, typename className, typename... Args>
	struct RuntimeClass
	{
		T(className::*m_pfnFunction)(Args... args);
	};

	#define DECL_RUNTIMECLASS(T, className, ...)												\
		static RuntimeClass<T, className, __VA_ARGS__> class_##className;

	#define IMPL_RUNTIMECLASS(T, className, pfnFunc, ...)										\
		RuntimeClass<T, className, __VA_ARGS__> className::class_##className = { (pfnFunc) };

	class TestClass
	{
	public:
		int TestFunc(int v);
		DECL_RUNTIMECLASS(int, TestClass, int)
	};

	int TestClass::TestFunc(int v)
	{
		return v;
	}

	IMPL_RUNTIMECLASS(int, TestClass, &TestClass::TestFunc, int)

	void variadic_template_4()
	{
		TestClass b;
		std::cout << (b.*b.class_TestClass.m_pfnFunction)(100) << std::endl;

		system("pause");

		/*
		output:
			100
		*/
	}


	template <typename T, typename... ParamList>
	class AA
	{
	public:
		//virtual void func1(const T& p, ParamList... params) <- compile error !!!
		//{
			//std::cout << "AA:func1()" << std::endl;
		//}
	};

	template <typename T, typename... ParamList>
	class BB : public AA<T, ParamList...>
	{
	public:
		virtual void func1(const T& p)
		{
			std::cout << "BB:func1() : " << p << std::endl;
		}
	};

	void variadic_template_override()
	{
		//typename... ParamList 템플리트는 override 함수 정의를 않됨 !!!
	}


	static std::map<std::type_index, std::string> SystemTypeStringList =
	{
			{ typeid(bool)					, "bool"	 }
		,	{ typeid(bool*)					, "bool*"    }
		,	{ typeid(short)					, "short"	 }
		,	{ typeid(short*)				, "short*"   }
		,	{ typeid(unsigned short)		, "ushort"	 }
		,	{ typeid(unsigned short*)		, "ushort*"	 }
		,	{ typeid(int)					, "int"		 }
		,	{ typeid(int*)					, "int*"	 }
		,	{ typeid(unsigned int)			, "uint"	 }
		,	{ typeid(unsigned int*)			, "uint*"	 }
		,	{ typeid(__int64)				, "int64"	 }
		,	{ typeid(__int64*)				, "int64*"	 }
		,	{ typeid(unsigned __int64)		, "uint64"	 }
		,	{ typeid(unsigned __int64*)		, "uint64*"	 }
		,	{ typeid(float)					, "float"	 }
		,	{ typeid(float*)				, "float*"	 }
		,	{ typeid(double)				, "double"	 }
		,	{ typeid(double*)				, "double*"	 }
	};

	std::string GetTypeString(std::type_index index)
	{
		auto foundPos = SystemTypeStringList.find(index);
		if (foundPos != SystemTypeStringList.end()) {
			return foundPos->second;
		}

		return index.name();
	}

	template <typename Return, typename... ParamList>
	class Callback
	{
	public:
		virtual Return invoke(ParamList... params) = 0;
	};

	template <typename Return, typename... ParamList>
	class StaticFunctionCallback : public Callback<Return, ParamList...>
	{
	private:
		Return(*m_func)(ParamList...);

	public:
		StaticFunctionCallback(Return(*func)(ParamList...))
			: m_func(func)
		{}

		virtual Return invoke(ParamList... params)
		{
			return (*m_func)(params...);
		}
	};

	template <typename T, typename Method, typename Return, typename... ParamList>
	class MethodCallback : public Callback<Return, ParamList...>
	{
	private:
		void* m_object;
		Method m_method;

	public:
		MethodCallback(void *object, Method method)
			: m_object(object)
			, m_method(method)
		{}

		virtual Return invoke(ParamList... params)
		{
			T* obj = static_cast<T*>(m_object);
			return (obj->*m_method)(params...);
		}
	};

	template <typename Return, typename... ParamList>
	class Delegate
	{
	private:
		Callback<Return, ParamList...>* m_callback = nullptr;

		std::vector<std::type_index> params_;
		std::string func_name_;

	public:
		Delegate(Return(*func)(ParamList...))
		: m_callback(new StaticFunctionCallback<Return, ParamList...>(func))
		{}

		template <typename T, typename Method>
		Delegate(T* object, Method method)
		: m_callback(new MethodCallback<T, Method, Return, ParamList...>(object, method))
		{
			//this->SetParams<ParamList...>();
		}

		Delegate(Delegate<Return, ParamList...>& refObj)
		{
			if (nullptr != m_callback) {
				delete m_callback;
				m_callback = nullptr;
			}

			if (nullptr != refObj.m_callback) {
				m_callback = refObj.m_callback;
				refObj.m_callback = nullptr;
			}
		}

		~Delegate(void)
		{
			if (nullptr != m_callback) {
				delete m_callback;
				m_callback = nullptr;
			}
		}

		template <typename... ParamTypeList>
		void SetParams()
		{
			params_.insert(params_.begin(), { typeid(ParamTypeList)... });
		}
		std::vector<std::type_index>& GetParams() { return params_; }

		template <typename... ParamTypeList>
		bool IsMatchedParams()
		{
			std::vector<std::type_index> typeList;
			typeList.insert(typeList.begin(), { typeid(ParamTypeList)... });

			return params_ == typeList;
		}

		void SetFuncName(std::string strName) { func_name_ = strName; }
		std::string& GetFuncName() { return func_name_; }

		Delegate<Return, ParamList...>& operator=(const Delegate<Return, ParamList...>& refObj)
		{
			if (nullptr != m_callback) {
				delete m_callback;
				m_callback = nullptr;
			}

			if (nullptr != refObj.m_callback) {
				this->m_callback = refObj.m_callback;
				refObj.m_callback = nullptr;
			}
		}

		void Invoke(ParamList... params)
		{
			m_callback->invoke(params...);
		}
	};

	template<typename T, typename return_type, typename... params>
	struct DelegateMaker
	{
		template<return_type(T::*func)(params...)>
		inline static Delegate<return_type, params...> Bind(T* o)
		{
			return Delegate<return_type, params...>(o, func);
		}
	};

	template<typename T, typename return_type, typename... params>
	DelegateMaker<T, return_type, params...> makeDelegate(return_type(T::*)(params...))
	{
		return DelegateMaker<T, return_type, params...>();
	}

	#define DELEGATE(func, object) (makeDelegate(func).Bind<func>(object))


	class A
	{
	public:
		virtual int foo(int p)
		{
			std::cout << "A::foo(" << p << ")" << std::endl;
			return p;
		}
	};

	class B : public A
	{
	public:
		virtual int foo(int p)
		{
			std::cout << "B::foo(" << p << ")" << std::endl;
			return p;
		}
	};

	class C
	{
	};

	class D : public C, public A
	{
	public:
		virtual int foo(int p)
		{
			std::cout << "D::foo(" << p << ")" << std::endl;
			return p;
		}
	};

	int foo2(int x)
	{
		std::cout << "foo(" << x << ")" << std::endl;
		return x;
	}

	void variadic_template_delegate_1()
	{
		A a;

		auto z = DELEGATE(&A::foo, &a);
		z.Invoke(100);

		system("pause");

		/*
		output:
			A::foo(100)
		*/
	}


	template <typename T> class delegate;

	template<class R, class ...A>
	class delegate<R(A...)>
	{
	protected:
		using stub_ptr_type = R(*)(void*, A&&...);

	public:
		delegate() = default;
		delegate(delegate const&) = default;
		delegate(delegate&&) = default;

		delegate(void* const o, stub_ptr_type const m) noexcept
		: object_ptr_(o)
		, stub_ptr_(m)
		{
			this->SetParams<A...>();
		}

		template< typename T, typename = typename std::enable_if< !std::is_same< delegate
			                                                                   , typename std::decay<T>::type>{} >::type >
		delegate(T&& f)
		{
			object_ptr_ = f.GetObjectPtr();
			stub_ptr_ = f.GetStubPtr();
			params_ = f.GetParams();
		}

		virtual ~delegate()
		{
			//std::cout << "Call delegate::~delegate()" << std::endl;
		}

		void* GetObjectPtr() { return object_ptr_; }

		stub_ptr_type GetSubPtr() { return stub_ptr_; }

		template <typename... ParamTypeList>
		void SetParams()
		{
			params_.insert(params_.begin(), { typeid(ParamTypeList)... });
		}
		std::vector<std::type_index>& GetParams() { return params_; }

		template <typename... ParamTypeList>
		bool IsMatchedParams()
		{
			std::vector<std::type_index> typeList;
			typeList.insert(typeList.begin(), { typeid(ParamTypeList)... });

			return params_ == typeList;
		}

		void SetFuncName(std::string strName) { func_name_ = strName; }
		std::string& GetFuncName() { return func_name_; }

		template< typename T, typename = typename std::enable_if< !std::is_same< delegate
			                                                                   , typename std::decay<T>::type>{}>::type >
		delegate& operator=(T&& f)
		{
			object_ptr_ = f.GetObjectPtr();
			stub_ptr_ = f.GetStubPtr();
			params_ = f.GetParams();

			return *this;
		}

		template <R(* const function_ptr)(A...)>
		static delegate* Create() noexcept
		{
			return new delegate( nullptr, function_stub<function_ptr> );
		}

		template <class C, R(C::* const method_ptr)(A...)>
		static delegate* Create(C* const object_ptr) noexcept
		{
			return new delegate( object_ptr, method_stub<C, method_ptr> );
		}

		delegate& operator=(delegate& rhs) { rhs.swap(*this); return *this; }

		R operator()(A... args) const
		{
			return stub_ptr_(object_ptr_, std::forward<A>(args)...);
		}

		R Invoke(A... args) const
		{
			return stub_ptr_(object_ptr_, std::forward<A>(args)...);
		}

	private:
		void* object_ptr_;
		stub_ptr_type stub_ptr_;

		std::vector<std::type_index> params_;
		std::string func_name_;

		template<R(*function_ptr)(A...)>
		static R function_stub(void* const, A&&... args)
		{
			return function_ptr(std::forward<A>(args)...);
		}

		template<class C, R(C::*method_ptr)(A...)>
		static R method_stub(void* const object_ptr, A&&... args)
		{
			return (static_cast<C*>(object_ptr)->*method_ptr)(std::forward<A>(args)...);
		}
	};

	class EventProxy
	{
	public:
		class ErrorCapture
		{
		public:
			ErrorCapture(EventProxy* proxy)
			{
				m_proxy = proxy;
				proxy->SetErrorCapture(this);
			}
			~ErrorCapture()
			{
				if (nullptr != m_proxy) {
					m_proxy->SetErrorCapture(nullptr);
					m_proxy = nullptr;
				}
			}

			bool IsEmpty() { return notMatchedDelegateList.size() == 0; }

			std::vector<std::string>& GetErrorStringList() { return notMatchedDelegateList; }

		protected:
			std::vector<std::string> notMatchedDelegateList;

		private:
			EventProxy* m_proxy = nullptr;
		};

	public:
		std::multimap<int, std::shared_ptr<void>> m_delegateList;

		ErrorCapture* m_errorCapture = nullptr;

		template<typename T, typename return_type, typename... ParamList>
		struct DelegateMaker
		{
			template<return_type(T::*func)(ParamList...)>
			inline static Delegate<return_type, ParamList...>* Bind(T* o)
			{
				return new Delegate<return_type, ParamList...>(o, func);
			}
		};

		template<typename T, typename return_type, typename... ParamList>
		static DelegateMaker<T, return_type, ParamList...> GetDelegateMaker(return_type(T::*)(ParamList...))
		{
			return DelegateMaker<T, return_type, ParamList...>();
		}

		#define BindDelegate(proxy, event_id, func, object)								\
		{																				\
			auto pDelegate = EventProxy::GetDelegateMaker(func).Bind<func>(object);		\
			if(nullptr != pDelegate) {													\
				pDelegate->SetFuncName(#func);											\
				proxy.RegisterDelegate(event_id, pDelegate);							\
			}																			\
		}

	public:
		template<typename D>
		bool RegisterDelegate(int eventID, D delegate)
		{
			if (nullptr == delegate) {
				return false;
			}

			std::shared_ptr<void> sharedPtr(delegate);

			m_delegateList.emplace(eventID, sharedPtr);
			return true;
		}

		void UnregisterDelegate(int eventID)
		{
			auto found = m_delegateList.find(eventID);
			if (m_delegateList.end() == found) {
				return;
			}
			m_delegateList.erase(found);
		}

		template<typename R, typename... ParamList>
		void NotifyAllStdFunction(int eventID, ParamList... params)
		{
			auto itFoundRange = m_delegateList.equal_range(eventID);

			for (auto itPos = itFoundRange.first;
				itPos != itFoundRange.second;
				++itPos) {

				if (nullptr != itPos->second) {
					auto delegator = static_cast<std::function<R(ParamList...)>*>( itPos->second.get() );
					(*delegator)(params...);
				}
			}
		}

		template<typename... ParamList>
		void NotifyAllDelegate(int eventID, ParamList... params)
		{
			auto itFoundRange = m_delegateList.equal_range(eventID);

			for (auto itPos = itFoundRange.first;
				itPos != itFoundRange.second;
				++itPos) {

				if (nullptr != itPos->second) {
					auto delegator = static_cast<Delegate<void, ParamList...>*>( itPos->second.get() );
					if(true != delegator->IsMatchedParams<ParamList...>()) {

						if (nullptr != m_errorCapture) {
							std::vector<std::string>& notMatchedDelegateList = m_errorCapture->GetErrorStringList();

							std::string funcInfo;
							funcInfo = delegator->GetFuncName() + "(";
							for ( auto pos = delegator->GetParams().begin();
								  pos != delegator->GetParams().end(); ) {

								funcInfo = funcInfo + GetTypeString(*pos);
								++pos;
								funcInfo = funcInfo + ((pos != delegator->GetParams().end()) ? ", " : "");
							}
							funcInfo = funcInfo + " )";

							notMatchedDelegateList.emplace_back(funcInfo);
						}
						continue;
					}

					delegator->Invoke(params...);
				}
			}
		}

		template<typename R, typename... ParamList>
		void NotifyAllDelegateRA(int eventID, ParamList... params )
		{
			auto itFoundRange = m_delegateList.equal_range(eventID);

			for (auto itPos = itFoundRange.first;
				itPos != itFoundRange.second;
				++itPos) {

				if (nullptr != itPos->second) {
					auto delegator = static_cast<delegate<void(ParamList...)>*>(itPos->second.get());
					if(true != delegator->IsMatchedParams<ParamList...>()) {

						if (nullptr != m_errorCapture) {
							std::vector<std::string>& notMatchedDelegateList = m_errorCapture->GetErrorStringList();

							std::string funcInfo;
							funcInfo = delegator->GetFuncName() + "( ";
							for ( auto pos = delegator->GetParams().begin();
								  pos != delegator->GetParams().end(); ) {

								funcInfo = funcInfo + GetTypeString(*pos);
								++pos;
								funcInfo = funcInfo + ( (pos != delegator->GetParams().end()) ? ", " : "" );
							}
							funcInfo = funcInfo + " )";

							notMatchedDelegateList.emplace_back(funcInfo);
						}
						continue;
					}

					delegator->Invoke(params...);
				}
			}
		}

		template<typename R, typename... A>
		struct Delegatee4Func
		{
			template<R(*func)(A...)>
			inline static delegate<R(A...)>* Bind()
			{
				return delegate<R(A...)>::Create<func>();
			}
		};

		template<typename R, typename... A>
		static Delegatee4Func<R, A...> makeDelegatee4Func(R(*)(A...))
		{
			return Delegatee4Func<R, A...>();
		}

		#define DELEGATE_FUNC_REGISTER(proxyObj, eventID, func)								\
		{																					\
			auto f = EventProxy::makeDelegatee4Func(func).Bind<func>();						\
			f->SetFuncName(#func);															\
			proxyObj.RegisterDelegate(eventID, f);											\
		}

		template<typename T, typename R, typename... A>
		struct Delegatee4MemberFunc
		{
			template<R(T::*func)(A...)>
			inline static delegate<R(A...)>* Bind(T* o)
			{
				return delegate<R(A...)>::Create<T, func>(o);
			}
		};

		template<typename T, typename R, typename... A>
		static Delegatee4MemberFunc<T, R, A...> makeDelegatee4MemberFunc(R(T::*)(A...))
		{
			return Delegatee4MemberFunc<T, R, A...>();
		}

		#define DELEGATE_MEMBER_FUNC_REGISTER(proxyObj, eventID, func, object)				\
		{																					\
			auto f = EventProxy::makeDelegatee4MemberFunc(func).Bind<func>(object);			\
			f->SetFuncName(#func);															\
			proxyObj.RegisterDelegate(eventID, f);											\
		}

		void SetErrorCapture(ErrorCapture* capture) { m_errorCapture = capture; }
	};


	struct Param
	{
		int v1 = 0;
		float v2 = 0.f;
	};

	void kookoo(int i)
	{
		std::cout << "kookoo(" << i << ")" << std::endl;
	}

	class E
	{
	public:
		
		auto foo(int p)
		{
			std::cout << "E::foo(" << p << ")" << std::endl;
		}

		void hoo(Param& param)
		{
			std::cout << "E::hoo(" << param.v1 << ", " << param.v2 << ")" << std::endl;
		}
	};

	class F
	{
	public:
		virtual int foo(int v1, int v2)
		{
			std::cout << "F::foo(" << v1 << ", " << v2 << ")" << std::endl;
			return v1 + v2;
		}
	};

	class G
	{
	public:
		void hoo(Param param)
		{

		}
	};

	void variadic_template_delegate_2()
	{
		{
			EventProxy proxy;

			auto f = EventProxy::makeDelegatee4Func(kookoo).Bind<kookoo>();
			delegate<void(int)> tf = *f;
			delete f;

			system("pause");
			/*
			output:
			*/
		}

		{
			EventProxy proxy;

			auto f = EventProxy::makeDelegatee4Func(kookoo).Bind<kookoo>();
			proxy.RegisterDelegate(10, f);

			proxy.NotifyAllDelegateRA<void, int>(10, 1000 );

			proxy.UnregisterDelegate(10);

			system("pause");
			/*
			output:
				kookoo(1000)
			*/
		}

		{
			EventProxy proxy;

			E e;

			Param param;
			param.v1 = 100;
			param.v2 = 0.5f;

			auto f = EventProxy::makeDelegatee4MemberFunc(&E::hoo).Bind<&E::hoo>(&e);
			proxy.RegisterDelegate(10, f);

			proxy.NotifyAllDelegateRA<void, Param>(10, param );

			system("pause");
			/*
			output:
				E::hoo(100, 0.5)
			*/
		}
	}

	void variadic_template_event_proxy()
	{
		{
			EventProxy proxy;

			E e;
			BindDelegate(proxy, 1, &E::foo, &e);
			proxy.NotifyAllDelegate(1, 10000);

			F f;
			BindDelegate(proxy, 2, &F::foo, &f);
			proxy.NotifyAllDelegate(2, 10000, 2000);

			Param param;
			param.v1 = 100;
			param.v2 = 0.8f;
			BindDelegate(proxy, 3, &E::hoo, &e);
			proxy.NotifyAllDelegate(3, &param);

			system("pause");
			/*
			output:
				E::foo(10000)
				A::foo(10000, 2000)
				E::foo(100, 0.8)
			*/
		}

		{
			EventProxy proxy;

			DELEGATE_FUNC_REGISTER(proxy, 11, kookoo);
			proxy.NotifyAllDelegateRA<void, int>( 11, 10 );

			A a;

			DELEGATE_MEMBER_FUNC_REGISTER(proxy, 12, &A::foo, &a);
			proxy.NotifyAllDelegateRA<void, int>( 12, 1000 );

			E e;

			Param param;
			param.v1 = 100;
			param.v2 = 0.5f;

			DELEGATE_MEMBER_FUNC_REGISTER(proxy, 13, &E::hoo, &e);

			proxy.NotifyAllDelegateRA<void, Param>( 13, param );

			EventProxy::ErrorCapture capture(&proxy);

			//Param 타입을 파라메터로 받는 함수에 int 타입값을 보내면 실패 처리 해준다 !!!
			int v = 1000;
			proxy.NotifyAllDelegateRA<void, int>( 13, v );

			if (true != capture.IsEmpty()) {
				std::vector<std::string>& errMsgList = capture.GetErrorStringList();
				for (auto& msg : errMsgList) {
					std::cout << "ErrFunc : " << msg << std::endl;
				}
			}

			system("pause");
			/*
			output:
				kookoo(10)
				A::foo(1000)
				E::foo(100, 0.5)
				ErrFunc : &E::hoo( struct Template::Param )
			*/
		}

		//compare performance !!!
		{
			EventProxy proxy;

			G g;
			
			Param param;
			param.v1 = 1000;
			param.v2 = 0.5f;

			uint32_t time;

			time = clock();
			for (auto i = 1; i < 100000; ++i) {
				std::function<void(Param)>* f1 = new std::function<void(Param)>;
				*f1 = [](Param param) { return; };
				proxy.RegisterDelegate(1, f1);
				proxy.NotifyAllStdFunction<void>(1, param);
				proxy.UnregisterDelegate(1);
			}
			uint32_t elpased_1 = clock() - time;
	
			time = clock();
			for (auto i = 1; i < 100000; ++i) {
				BindDelegate(proxy, 2, &G::hoo, &g);
				proxy.NotifyAllDelegate(2, param);
				proxy.UnregisterDelegate(2);
			}
			uint32_t elpased_2 = clock() - time;

			time = clock();
			for (auto i = 1; i < 100000; ++i) {
				DELEGATE_MEMBER_FUNC_REGISTER(proxy, 3, &G::hoo, &g);
				proxy.NotifyAllDelegateRA<void>(3, param);
				proxy.UnregisterDelegate(3);
			}
			uint32_t elpased_3 = clock() - time;

			std::cout << "std::function elapsed tick : " << elpased_1 << std::endl;
			std::cout << "Delegate<R,A> elapsed tick : " << elpased_2 << std::endl;
			std::cout << "delegate<R(A)> elapsed tick : " << elpased_3 << std::endl;

			system("pause");
			/*
			output:
				elapsed tick : 287, 274, 250
			*/
		}
	}


	void Test()
	{
		//variadic_template_event_proxy();

		//variadic_template_delegate_2();

		//variadic_template_delegate_1();

		//variadic_template_override();

		//variadic_template_4();

		//variadic_template_3();

		//variadic_template_2();

		//variadic_template_1();

		//variadic_template_typeid();

		//make_array();
	}

}// end of Template
