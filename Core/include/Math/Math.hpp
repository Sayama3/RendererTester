//
// Created by ianpo on 01/06/2024.
//

#pragma once

#include "Core/Macro.hpp"
#include "Core/Logger.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"
#include "Quaternion.hpp"
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
      return {{
            lft[1]*rgh[2] - lft[2]*rgh[1],
            lft[2]*rgh[0] - lft[0]*rgh[2],
            lft[0]*rgh[1] - lft[1]*rgh[0]
      }};
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
      return radians * RadToDeg<T>();
   }

   template<typename T>
   T DegToRad()
   {
      return (std::numbers::pi_v<T> / static_cast<T>(180));
   }

   template<typename T>
   T DegToRad(T degree)
   {
      return degree * DegToRad<T>();
   }

   template<typename T>
   Matrix<T, 4, 4> ToMat4(const Quaternion<T>& qua)
   {
      T x = qua[0];
      T y = qua[1];
      T z = qua[2];
      T w = qua[3];

      Matrix<T, 4, 4> matrix;

      matrix(0, 0) = 1 - 2*y*y - 2*z*z;
      matrix(0, 1) = 2*x*y - 2*z*w;
      matrix(0, 2) = 2*x*z + 2*y*w;

      matrix(1, 0) = 2*x*y + 2*z*w;
      matrix(1, 1) = 1 - 2*x*x - 2*z*z;
      matrix(1, 2) = 2*y*z - 2*x*w;

      matrix(2, 0) = 2*x*z - 2*y*w;
      matrix(2, 1) = 2*y*z + 2*x*w;
      matrix(2, 2) = 1 - 2*x*x - 2*y*y;

	   matrix(3, 3) = 1;

	   return matrix;
   }

   template<typename T>
   Matrix<T, 3, 3> ToMat3(const Quaternion<T>& qua)
   {
      T w = qua[0];
      T x = qua[1];
      T y = qua[2];
      T z = qua[3];

      Matrix<T, 3, 3> matrix;

      matrix(0, 0) = 1 - 2*y*y - 2*z*z;
      matrix(0, 1) = 2*x*y - 2*z*w;
      matrix(0, 2) = 2*x*z + 2*y*w;

      matrix(1, 0) = 2*x*y + 2*z*w;
      matrix(1, 1) = 1 - 2*x*x - 2*z*z;
      matrix(1, 2) = 2*y*z - 2*x*w;

      matrix(2, 0) = 2*x*z - 2*y*w;
      matrix(2, 1) = 2*y*z + 2*x*w;
      matrix(2, 2) = 1 - 2*x*x - 2*y*y;

      return matrix;
   }

   template<typename T>
   Matrix<T,3,3> LookAt(const Vector<T,3>& forward, const Vector<T,3>& up = {0,1,0})
   {
	   Matrix<T,3,3> result = {Math::Cross(up, forward), up, forward};
	   result[0].Normalize();

	   result[1] = Math::Cross(result[2], result[0]);
	   result[1].Normalize();

	   result[2].Normalize();

	   return result;
   }

   template<typename T>
   void LookAt(Matrix<T,3,3>* matrix, const Vector<T,3>& forward, const Vector<T,3>& up = {0,1,0})
   {
	   matrix[0] = Math::Cross(up, forward);
	   matrix[0].Normalize();

	   matrix[1] = Math::Cross(forward, matrix[0]);
	   matrix[1].Normalize();

	   matrix[2] = forward;
	   matrix[2].Normalize();
   }

   template<typename T>
   void Translate(Matrix<T, 4, 4>& matrix, Vector<T, 3> translation)
   {
      matrix(3, 0) += translation[0];
      matrix(3, 1) += translation[1];
      matrix(3, 2) += translation[2];
   }
   template<typename T>
   void Rotate(Matrix<T, 4, 4>& matrix, Quaternion<T> rotation)
   {
      matrix = matrix * ToMat4(rotation);
   }

} // Math
