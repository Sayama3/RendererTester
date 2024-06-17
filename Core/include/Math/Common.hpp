//
// Created by ianpo on 16/06/2024.
//

#pragma once

#include <cmath>

typedef float Real;

namespace Math::Common
{
   template<typename T>
   static inline constexpr T Sqrt(const T& val)
   {
      return std::sqrt(val);
   }

   template<typename T>
   static inline constexpr T Min(const T& val0, const T& val1)
   {
      return std::min(val0, val1);
   }

   template<typename T>
   static inline constexpr T Max(const T& val0, const T& val1)
   {
      return std::max(val0, val1);
   }

   template<typename T>
   static inline constexpr T Abs(const T& val0)
   {
      return val0 < 0 ? -val0 : val0;
   }
}
