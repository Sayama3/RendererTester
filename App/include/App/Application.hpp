//
// Created by ianpo on 01/06/2024.
//

#pragma once

#include "App/Window.hpp"

namespace App {

   class Application {
   public:
      Application(const WindowParameters& parameters);
      ~Application();
      Application(const Application&) = delete;
      Application& operator=(const Application&) = delete;
   public:
      void Run();
   private:
      Window m_Window;
   };

} // App
