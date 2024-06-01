//
// Created by ianpo on 01/06/2024.
//

#pragma once

#include "Vector.hpp"
#include "Matrix.hpp"
#include <cstdint>
#include <cmath>

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

} // Math
