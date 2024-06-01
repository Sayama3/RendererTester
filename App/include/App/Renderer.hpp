//
// Created by ianpo on 01/06/2024.
//

#pragma once

#include "Core/Core.hpp"

namespace App {

   class Renderer {
   public:
      static void Initialize();
      static void SetClearColor(Math::Vec3 color = {{1.f, 1.f, 1.f}});
      static void Clear();
   };

} // App
