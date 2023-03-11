#pragma once

#include "stdafx.h"

namespace Pool
{

	/*
	///////////////////////////////////////////////////////////////////////////////
	/// @file MemoryPool.hpp
	/// @class MemoryPoolTemplate
	/// @brief
	/// 
	/// @author justin
	/// @date 3/23/2006 21:20:23
	///////////////////////////////////////////////////////////////////////////////
	class MemoryPool
	{
	protected:
		std::unordered_map<_TPoolKeyType, IObjectPool<_TPoolKeyType>*> m_objectPoolList;

	public:
		virtual ~ObjectPoolFactory()
		{
			this->ClearObjectPoolList();
		}

		void ClearObjectPoolList()
		{
			for (const auto &pair : m_objectPoolList) {
				delete pair.second;
			}
		}

		template<typename _TObjectType>
		bool CreateObjectPool(unsigned int maxObjectCount)
		{
			auto itFound = m_objectPoolList.find(ObjectPool<_TPoolKeyType, _TObjectType>::TypeID);
			if (m_objectPoolList.end() != itFound) {
				return false;
			}

			ObjectPool<_TPoolKeyType, _TObjectType>* pObjPool = new ObjectPool<_TPoolKeyType, _TObjectType>();
			if (nullptr == pObjPool) {
				return false;
			}

			if (true != pObjPool->InitObjectPool(maxObjectCount)) {
				delete pObjPool;
				return false;
			}

			m_objectPoolList.emplace(ObjectPool<_TPoolKeyType, _TObjectType>::TypeID, pObjPool);
			return true;
		}

		void DestroyObjectPool(_TPoolKeyType key)
		{
			auto itFound = m_objectPoolList.find(key);
			if (m_objectPoolList.end() == itFound) {
				return;
			}

			IObjectPool<_TPoolKeyType>* pObjPool = itFound->second;
			m_objectPoolList.erase(itFound);
			delete pObjPool;
		}

		template<typename _TObjectType, typename... _TArgs>
		_TObjectType* CreateObject(_TArgs&&... tArgs)
		{
			auto itFound = m_objectPoolList.find(ObjectPool<_TPoolKeyType, _TObjectType>::TypeID);
			if (m_objectPoolList.end() == itFound) {
				return nullptr;
			}

			ObjectPool<_TPoolKeyType, _TObjectType>* pPool = (ObjectPool<_TPoolKeyType, _TObjectType>*)itFound->second;
			return pPool->CreateObject(tArgs...);
		}

		void GetUsingObjectListAll(OUT std::vector<IObject<_TPoolKeyType>*> &objectList)
		{
			for (const auto &pair : m_objectPoolList) {
				pair.second->GetUsingObjectList(OUT objectList);
			}
		}
	};
	*/

}