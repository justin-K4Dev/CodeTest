#pragma once

namespace DesignPattern
{
	template<class T>
	class ISingleton
	{
	protected:
		static T m_singeton;
		ISingleton() {}

	public:
		ISingleton(ISingleton const&) = delete;
		virtual ~ISingleton() {}

		static T& GetInstance()
		{
			return m_singeton;
		}

		void operator=(ISingleton const&) = delete;
	};
	template<class T> T ISingleton<T>::m_singeton;
}