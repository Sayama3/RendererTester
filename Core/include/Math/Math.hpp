//
// Created by ianpo on 01/06/2024.
//

#pragma once

#include "Vector.hpp"
#include "Matrix.hpp"
#include <cstdint>
#include <cmath>
#include <cstring>
#include <numbers>

namespace Math {

   template<typename T, uint64_t N>
   Matrix<T, 1, N> ToMatrix(const Vector<T, N> &vector) {
      Matrix<T, 1, N> matrix;

      for (uint64_t i = 0; i < N; ++i) {
         matrix(0, i) = vector[i];
      }

      return matrix;
   }

   template<typename T>
   Vector<T, 3> Cross(const Vector<T, 3> &lft, const Vector<T, 3> & rgh)
   {
      return {
            lft[1]*rgh[2] - lft[2]*rgh[1],
            lft[2]*rgh[0] - lft[0]*rgh[2],
            lft[0]*rgh[1] - lft[1]*rgh[0]
      };
   }

   template<typename T, uint64_t N>
   T Dot(const Vector<T, N> &lft, const Vector<T, N> & rgh)
   {
      T dotProduct = 0;
      for(uint64_t i = 0; i < N; ++i) {
         dotProduct += lft[i] * rgh[i];
      }
      return dotProduct;
   }

   template<typename T>
   Matrix<T, 4, 4> Perspective(T fovy, T aspect, T zNear, T zFar)
   {
      CORE_ASSERT(abs(aspect - std::numeric_limits<T>::epsilon()) > static_cast<T>(0), "Aspect Ratio is incorrect.");

      T const tanHalfFovy = std::tan(fovy / static_cast<T>(2));

      Matrix<T, 4, 4> res(static_cast<T>(0));
      res(0, 0) = static_cast<T>(1) / (aspect * tanHalfFovy);
      res(1, 1) = static_cast<T>(1) / (tanHalfFovy);
      res(2, 2) = - (zFar + zNear) / (zFar - zNear);
      res(2, 3) = - static_cast<T>(1);
      res(3, 2) = - (static_cast<T>(2) * zFar * zNear) / (zFar - zNear);
      return res;
   }

   template<typename T>
   T RadToDeg()
   {
      return (static_cast<T>(180) / std::numbers::pi_v<T>);
   }

   template<typename T>
   T RadToDeg(T radians)
   {
      return radians * (static_cast<T>(180) / std::numbers::pi_v<T>);
   }

   template<typename T>
   T DegToRad()
   {
      return (std::numbers::pi_v<T> / static_cast<T>(180));
   }

   template<typename T>
   T DegToRad(T degree)
   {
      return degree * (std::numbers::pi_v<T> / static_cast<T>(180));
   }

} // Math
