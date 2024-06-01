//
// Created by ianpo on 01/06/2024.
//

#include "Render/Renderer.hpp"

#include "glad/glad.h"

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE 1
#endif

#include "GLFW/glfw3.h"

namespace Render {
   void Renderer::Initialize() {
      glEnable(GL_DEPTH);
   }

   void Renderer::SetClearColor(Math::Vec3 color) {
      CORE_PROFILE_FUNCTION();
      glClearColor(color[0], color[1], color[2], 1.0f);
   }

   void Renderer::Clear() {
      CORE_PROFILE_FUNCTION();
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   }
} // App