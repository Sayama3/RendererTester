
#pragma once

#ifndef SPDLOG_ACTIVE_LEVEL
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif

#include "spdlog/spdlog.h"

namespace Core {

   class Logger {
   public:
      static void Init();
      static void Destroy();
      static std::shared_ptr<spdlog::logger>& GetLogger();

   private:
      static std::shared_ptr<spdlog::logger> s_CoreLogger;
      static inline bool s_Init = false;
   };
}

#ifndef CORE_DONT_LOG

#define CORE_TRACE(...)       ::Core::Logger::GetLogger()->log(spdlog::source_loc{__FILE__, __LINE__, CORE_FUNC}, spdlog::level::trace, __VA_ARGS__)
#define CORE_INFO(...)        ::Core::Logger::GetLogger()->log(spdlog::source_loc{__FILE__, __LINE__, CORE_FUNC}, spdlog::level::info, __VA_ARGS__)
#define CORE_WARNING(...)     ::Core::Logger::GetLogger()->log(spdlog::source_loc{__FILE__, __LINE__, CORE_FUNC}, spdlog::level::warn, __VA_ARGS__)
#define CORE_WARN(...)        ::Core::Logger::GetLogger()->log(spdlog::source_loc{__FILE__, __LINE__, CORE_FUNC}, spdlog::level::warn, __VA_ARGS__)
#define CORE_ERROR(...)       ::Core::Logger::GetLogger()->log(spdlog::source_loc{__FILE__, __LINE__, CORE_FUNC}, spdlog::level::err, __VA_ARGS__)
#define CORE_CRITICAL(...)    ::Core::Logger::GetLogger()->log(spdlog::source_loc{__FILE__, __LINE__, CORE_FUNC}, spdlog::level::critical, __VA_ARGS__)

#else

#define CORE_TRACE(...)
#define CORE_INFO(...)
#define CORE_WARNING(...)
#define CORE_WARN(...)
#define CORE_ERROR(...)
#define CORE_CRITICAL(...)

#endif