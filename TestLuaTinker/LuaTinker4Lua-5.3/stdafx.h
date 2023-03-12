// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "CRT_MemoryCheck.h"

#include "targetver.h"

#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

///////////////////////////////////////////////////////////////////////////////
/// @file Header TestFunction.h
/// @brief C 함수 호출을 위한 선언
/// 
/// @author justin
/// @date 8-30-2012 11:28:46
///////////////////////////////////////////////////////////////////////////////

extern "C"
{
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
};

#include <lua_tinker.h>
