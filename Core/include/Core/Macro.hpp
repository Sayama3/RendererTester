//
// Created by ianpo on 01/06/2024.
//

#pragma once

#define CORE_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#define CORE_CONCAT(x, y) x ## y
#define CORE_COMBINE(x, y) CORE_CONCAT(x, y)

#define CORE_BIT(X) (1 << X)

#define CORE_CHECK_BIT(var,pos) ((var) & (1<<(pos)))

#ifdef CORE_USE_SIMPLE_FUNCTION
   #define CORE_FUNC __FUNCTION__
#else
   #ifndef __FUNCSIG__
      #ifdef __PRETTY_FUNCTION__
         #define CORE_FUNC __PRETTY_FUNCTION__
      #else
         #define CORE_FUNC __FUNCTION__
      #endif
   #else
      #define CORE_FUNC __FUNCSIG__
   #endif
#endif

//TODO: Do something a bit better.
#if (_MSC_VER && !__INTEL_COMPILER) || (__MINGW32__ || __MINGW64__)
   #define CORE_BREAK() __debugbreak()
#elif _POSIX
   #include <signal.h>
   #define CORE_BREAK() std::raise(SIGTRAP)
#else
   #define CORE_BREAK()
#endif

#define EXPAND_MACRO(x) x
#define STRINGIFY_MACRO(x) #x
