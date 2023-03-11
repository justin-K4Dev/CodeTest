#pragma once

#include "stdafx.h"

namespace Pool
{
	///////////////////////////////////////////////////////////////////////////////
	/// @file ObjectPool.hpp
	/// @class IObject Interface
	/// @brief IObjectPool Interface Class
	/// 
	/// @author justin
	/// @date 3/23/2006 21:20:23
	///////////////////////////////////////////////////////////////////////////////
	template<class _Type>
	class IObject
	{
	public:
		typedef _Type Type;

		virtual unsigned int GetTypeID() = 0;
		virtual const char* GetTypeName() = 0;
	};

	///////////////////////////////////////////////////////////////////////////////
	/// @file ObjectPool.hpp
	/// @class IObjectPool Interface
	/// @brief
	/// 
	/// @author justin
	/// @date 3/23/2006 21:20:23
	///////////////////////////////////////////////////////////////////////////////
	template<class _Type>
	class IObjectPool
	{
	public:
		typedef _Type Type;

		IObjectPool() { return; }
		virtual ~IObjectPool() { return; }

		virtual void ReleaseObject(IObject<_Type>* pObject) = 0;

		virtual unsigned int ObjectCountInPool() = 0;

		virtual unsigned int GetObjectAllCount() = 0;

		virtual void GetPoolInfo(OUT unsigned int &objectCountInPool, OUT unsigned int &objectAllCount) = 0;
	
		virtual void GetUsingObjectList(OUT std::vector<IObject<_Type>*> &objectList) = 0;
	};

	///////////////////////////////////////////////////////////////////////////////
	/// @file ObjectPool.hpp
	/// @class ObjectPool Template
	/// @brief
	/// 
	/// @author justin
	/// @date 3/23/2006 21:20:23
	///////////////////////////////////////////////////////////////////////////////
	#define OBJECT_POOL_INIT_RESERVATION_POWER                                    2
	#define OBJECT_POOL_OVER_RESERVATION_POWER                                    2

	template <class _PoolKeyType, class _TObjectType>
	class ObjectPool : public IObjectPool<_PoolKeyType>
	{
	public:
		static const _PoolKeyType TypeID = _TObjectType::TypeID;

	protected:
		unsigned int m_maxObjectCount = 0;	// max object count

		std::vector<_TObjectType*> m_objectList;	// allocated object list

		std::stack<_TObjectType*> m_objectPool;	// object pool

		std::unordered_map<_TObjectType*, _TObjectType*> m_usingObjectList;	// using object list

	public:
		virtual ~ObjectPool()
		{
			ClearObjectPool();
		}

	private:
		bool AllocObject()
		{
			int j = m_maxObjectCount * OBJECT_POOL_OVER_RESERVATION_POWER;

			for (int i = m_maxObjectCount; i < j; ++i)
			{
				_TObjectType* pObj;

				try
				{
					pObj = new _TObjectType();
				}
				catch (const std::bad_alloc&)
				{
					return false;
				}

				m_objectList.push_back(pObj);
				m_objectPool.push(pObj);
			}

			m_maxObjectCount = j;
			return true;
		}

	public:
		// initialize object pool
		bool InitObjectPool(unsigned int maxObjectCount)
		{
			if (m_maxObjectCount > 0)
				return false;

			if (maxObjectCount <= 0)
				maxObjectCount = 1;

			m_maxObjectCount = maxObjectCount;
			m_objectList.reserve(m_maxObjectCount * OBJECT_POOL_INIT_RESERVATION_POWER);

			for (unsigned int i = 0; i < m_maxObjectCount; ++i)
			{
				_TObjectType* pObj;

				try
				{
					pObj = new _TObjectType();
				}
				catch (const std::bad_alloc&)
				{
					return false;
				}

				m_objectList.push_back(pObj);
				m_objectPool.push(pObj);
			}

			return true;
		}

		void ClearObjectPool()
		{
			for (const auto &v : m_objectList) {
				_TObjectType* pObj = (_TObjectType*)(v);
				if (nullptr != pObj) {
					delete pObj;
				}
			}

			m_objectList.clear();

			while (m_objectPool.empty() != true)
			{
				m_objectPool.pop();
			}

			m_maxObjectCount = 0;
		}

	public:
		bool IsEmptyPool()
		{ return m_objectPool.empty(); }

		unsigned int ObjectCountInPool()
		{ return (unsigned int)(m_objectPool.size()); }

		unsigned int GetObjectAllCount()
		{ return (unsigned int)(m_objectList.size()); }

		void GetPoolInfo(OUT unsigned int &objectCountInPool, OUT unsigned int &objectAllCount)
		{
			objectCountInPool = (unsigned int)m_objectPool.size();
			objectAllCount = (unsigned int)(m_objectList.size());
		}

		unsigned int GetMaxObjectCount() { return m_maxObjectCount; }

		template<typename... _TArgs>
		_TObjectType* CreateObject(_TArgs&&... tArgs)
		{
			if (m_objectPool.empty() == true) {
				bool bl = this->AllocObject();
				if (bl == false) {
					return nullptr;
				}
			}

			_TObjectType* pObj = m_objectPool.top();

			// passsing of variadic template arguments
			if (true != pObj->Init(std::forward<_TArgs>(tArgs)...)) {
				return nullptr;
			}

			m_objectPool.pop();

			m_usingObjectList.emplace(pObj, pObj);

			// new (pObj) TAllocObject(); // call constructor

			return pObj;
		}

		void ReleaseObject(IObject<_PoolKeyType>* pObject)
		{
			// (_Ty*)pObject->~_Ty(); // call destructor

			m_objectPool.push((_TObjectType*)pObject);

			auto itFound = m_usingObjectList.find((_TObjectType*)pObject);
			if (m_usingObjectList.end() != itFound) {
				m_usingObjectList.erase(itFound);
			}
		}

		void GetUsingObjectList(OUT std::vector<IObject<_PoolKeyType>*> &objectList)
		{
			for (const auto &pair : m_usingObjectList) {
				objectList.emplace_back (pair.second);
			}
		}
	};

	///////////////////////////////////////////////////////////////////////////////
	/// @file ObjectPool.hpp
	/// @class ObjectPoolFactory Template
	/// @brief
	/// 
	/// @author justin
	/// @date 3/23/2006 21:20:23
	///////////////////////////////////////////////////////////////////////////////

	template<class _TPoolKeyType>
	class ObjectPoolFactory
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
			for (const auto &pair : m_objectPoolList ) {
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

}