//
// Created by ianpo on 01/06/2024.
//

#include "App/Window.hpp"
#include "Core/Core.hpp"

#include <glad/glad.h>

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE 1
#endif

#include <GLFW/glfw3.h>

namespace App {

   static void glfw_error_callback(int error, const char* description)
   {
      CORE_ERROR("GLFW Error {}: {}", error, description);
   }

   Window::Window(const WindowParameters &parameters) {
      CORE_PROFILE_FUNCTION();
      CORE_TRACE("Creating window {}", m_Parameters.Title);
      glfwSetErrorCallback(glfw_error_callback);

      if (!glfwInit()) {
         CORE_ERROR("GLFW could not be initialized.");
         return;
      }

      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

      // Create window with graphics context
      m_Window = glfwCreateWindow(m_Parameters.Width, m_Parameters.Height, m_Parameters.Title.c_str(), nullptr, nullptr);
      if (m_Window == nullptr) {
         CORE_ERROR("GLFW could not create the window {}.", m_Parameters.Title);
         return;
      }

      glfwMakeContextCurrent(GetNativeWindow<GLFWwindow>());

      int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

      printf("glad loading status: %d\n", status);
      printf("OpenGL Info:\n");
      printf("  Vendor: %s\n", (const char*)glGetString(GL_VENDOR));
      printf("  Renderer: %s\n", (const char*)glGetString(GL_RENDERER));
      printf("  Version: %s\n", (const char*)glGetString(GL_VERSION));

      glfwSwapInterval(1); // Enable vsync
   }

   Window::~Window() {
      CORE_TRACE("Destroying window {}", m_Parameters.Title);
      if(m_Window) {
         glfwDestroyWindow(GetNativeWindow<GLFWwindow>());
         glfwTerminate();
         m_Window = nullptr;
      }
   }

   bool Window::ShouldClose() const {
      CORE_PROFILE_FUNCTION();
      return glfwWindowShouldClose(const_cast<GLFWwindow*>(GetNativeWindow<GLFWwindow>()));
   }

   void Window::Close() {
      CORE_PROFILE_FUNCTION();
      glfwSetWindowShouldClose(GetNativeWindow<GLFWwindow>(), true);
   }

   void Window::PollEvents() {
      CORE_PROFILE_FUNCTION();
      glfwPollEvents();
   }

   void Window::SwapBuffers() {
      CORE_PROFILE_FUNCTION();
      glfwSwapBuffers(GetNativeWindow<GLFWwindow>());
   }

	uint32_t Window::GetWidth() const {
		return m_Parameters.Width;
	}

	uint32_t Window::GetHeight() const {
		return m_Parameters.Height;
	}
} // App