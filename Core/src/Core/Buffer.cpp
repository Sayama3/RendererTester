//
// Created by ianpo on 01/06/2024.
//

#include "Core/Buffer.hpp"

namespace Core {
   void Buffer::Allocate(uint64_t s) {
      Release();
      size = s;
      data = reinterpret_cast<uint8_t*>(malloc(s));
   }

   void Buffer::Release() {
      free(data);
      data = nullptr;
      size = 0;
   }
} // Core