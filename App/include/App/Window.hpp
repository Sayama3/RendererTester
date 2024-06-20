//
// Created by ianpo on 01/06/2024.
//

#pragma once

#include <cstdint>
#include <string>

namespace App {
   struct WindowParameters
   {
      std::string Title = "Application";
      uint32_t Width = 900, Height = 600;
   };
   class Window {
   public:
      Window(const WindowParameters& parameters);
      ~Window();
      Window(const Window&) = delete;
      Window& operator=(const Window&) = delete;
   public:
      [[nodiscard]] bool ShouldClose() const;
      void Close();
      void PollEvents();
      void SwapBuffers();

	  [[nodiscard]] uint32_t GetWidth() const;
	  [[nodiscard]] uint32_t GetHeight() const;
   public:
      template<typename T>
      T* GetNativeWindow() {return reinterpret_cast<T*>(m_Window);}
      template<typename T>
      const T* GetNativeWindow() const {return reinterpret_cast<T*>(m_Window);}
   private:
      WindowParameters m_Parameters;
      void* m_Window = nullptr;
   };

} // App
