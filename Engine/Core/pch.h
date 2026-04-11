#pragma once

#include<tchar.h>
#include<xstring>

#include<vector>
#include<memory>
#include<stdint.h>
#include<set>
#include<random>
#include<limits>
#include<vector>
#include<string>
#include<bitset>
#include<cassert>
#include<assert.h>
#include<sstream>
#include<istream>
#include<fstream>
#include<algorithm>
#include<functional>
#include<unordered_map>
#include<unordered_set>
#include<queue>
#include<map>
#include<stack>
#include<variant>
#include<mutex>

#if _DEBUG
    #include<iostream>
#endif

#if ON_VI_ENGINE
	#if DYNAMIC_BUILD
		#ifdef _MSC_VER
			#define VI_API __declspec(dllexport)
		#else
			#define VI_API __attribute__((visibility("default")))
		#endif
	#else
		#define VI_API
	#endif
#else
	#if DYNAMIC_IMPORT
		#ifdef _MSC_VER
			#define VI_API __declspec(dllimport)
		#else
			#define VI_API
		#endif
	#else
		#define VI_API
	#endif
#endif

// Runtime assert
#define VI_ASSERT assert

// Static assert
#if defined(__clang__) || defined(__gcc__)
	#define VI_STATIC_ASSERT _Static_assert
#else
	#define VI_STATIC_ASSERT static_assert
#endif

#define VI_BASE_CLASS_ASSERT(baseClass, derivedClass, message) VI_STATIC_ASSERT(std::is_base_of<baseClass, derivedClass>::value && message)

#if defined(__clang__) || defined(_gcc__)
	#define VI_FORCE_INLINE __attribute__((always_inline)) inline
	#define VI_NOINLINE __attribute__((noinline))
#elif defined(_MSC_VER)
	#define VI_FORCE_INLINE __forceinline
	#define VI_NOINLINE __declspec(noinline)
#else
	#define VI_FORCE_INLINE inline
	#define VI_NOINLINE
#endif

#define VI_FREE_MEMORY(memory) if (memory != nullptr) { delete memory; memory = nullptr; }

#define BIND_EVENT_FUNCTION(function) [this](auto&... args) -> decltype(auto)\
	{ return this->function(std::forward<decltype(args)>(args)...); }