#pragma once

#include <exception>
#include <new>

///////////////////////////////////////////////////////////////////////////////
/// @file Header TBB_MemoryAllocator.h
/// @brief 
/// 
/// @author justin
/// @date 8-16-2012 20:51:03
///////////////////////////////////////////////////////////////////////////////

#ifdef DEF_TBB_MEMORY_ALLOCATOR_ON

void* operator new (size_t size) throw (...);

void* operator new [] (size_t size) throw (...);

void* operator new (size_t size, const std::nothrow_t &th) throw ();

void* operator new [] (size_t size, const std::nothrow_t &th) throw ();

void operator delete ( void *ptr) throw ();

void operator delete [] ( void *ptr) throw ();

void operator delete ( void *ptr, const std::nothrow_t &th) throw ();

void operator delete [] ( void *ptr, const std::nothrow_t &th) throw ();

#endif//DEF_TBB_MEMORY_ALLOCATOR_ON
