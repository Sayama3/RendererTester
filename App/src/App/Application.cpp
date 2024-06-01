//
// Created by ianpo on 01/06/2024.
//

#include "App/Application.hpp"
#include "App/Renderer.hpp"
#include "Core/Core.hpp"
namespace App {
   Application::Application(const WindowParameters &parameters) : m_Window(parameters) {

   }

   void Application::Run() {
      Renderer::SetClearColor({{0.8f, 0.2f, 0.1f}});
      while (!m_Window.ShouldClose())
      {
         CORE_FRAME_START();
         m_Window.PollEvents();

         Renderer::Clear();

         m_Window.SwapBuffers();
         CORE_FRAME_END();
      }

   }

   Application::~Application()
   {
   }
} // App