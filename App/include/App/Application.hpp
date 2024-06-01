//
// Created by ianpo on 01/06/2024.
//

#pragma once

#include "App/Window.hpp"
#include "Core/SmartPointers.hpp"
#include "Render/Mesh.hpp"
#include "Render/Shader.hpp"

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
   private:
      //TODO: Remove as not clean.
      Core::Ref<Render::Shader> m_Shader = nullptr;
      Core::Ref<Render::Mesh> m_Mesh = nullptr;

   };

} // App
