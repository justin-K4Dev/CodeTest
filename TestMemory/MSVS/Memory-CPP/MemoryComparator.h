#pragma once

namespace Util
{
	class MemoryComparator
	{
	protected:
		std::string m_strTitle;

		ULONGLONG m_startWorkingSetSizeOfProcess;
		ULONGLONG m_midWorkingSetSizeOfProcess;

		bool m_isEnd = false;

	public:
		MemoryComparator(const char* title);
		virtual~MemoryComparator();

		void CompareNow(bool updateMiddleTime = false);

		void End();
	};
}