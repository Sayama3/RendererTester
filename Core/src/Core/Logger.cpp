//
// Created by ianpo on 01/06/2024.
//

#include "Core/Logger.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include <memory>

namespace Core {
   std::shared_ptr<spdlog::logger> Logger::s_CoreLogger;

   void Logger::Init()
   {
      // Setting Pattern
      spdlog::set_pattern("%^[%T] [%l] %n (%s:%#->%!): %v%$");

      // Creating core logger
      std::array<spdlog::sink_ptr, 2> core_sinks;
      core_sinks[0] = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
      core_sinks[1] = std::make_shared<spdlog::sinks::basic_file_sink_mt>("application.log");

      s_CoreLogger = std::make_shared<spdlog::logger>("APP", core_sinks.begin(), core_sinks.end());
      s_CoreLogger->set_level(spdlog::level::trace);

      s_Init = true;
   }

   void Logger::Destroy() {
      s_CoreLogger = nullptr;
      s_Init = false;
   }

   std::shared_ptr<spdlog::logger>& Logger::GetLogger() {
      if(!s_Init) Init();
      return s_CoreLogger;
   }
} // Core