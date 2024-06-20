//
// Created by ianpo on 16/06/2024.
//

#pragma once

#include <array>
#include "Common.hpp"
#include "Vector.hpp"

namespace Math {

   template<typename T>
   class Quaternion {
   public:
      Quaternion() = default;
      ~Quaternion() = default;
      Quaternion(const T& x, const T& y, const T& z, const T& w);
      Quaternion(const Vector<T, 3>&, const T& w = T(0));
      Quaternion(const std::array<T, 4>& vals);

   public:
      void Normalize();// Conjugate operation
      void RotateByVector(const Vector<T, 3> &other);
      void AddScaledVector(const Vector<T, 3> &other, T scale);
      Quaternion<T> Conjugate();
   public:
      // Addition operation
      Quaternion& operator+=(const Quaternion<T>& other);
      Quaternion operator+(Quaternion<T> other);
      // Subtraction operation
      Quaternion& operator-=(const Quaternion<T>& other);
      Quaternion operator-(Quaternion<T> other);

      Quaternion<T>& operator*=(const Quaternion<T>& other);
      Quaternion<T> operator*(Quaternion<T> other);

      // Quaternion-vector multiplication
      Vector<T, 3> operator*(const Vector<T, 3>& vec);
   public:
      T& operator[](uint64_t i) { return values[i];}
      const T& operator[](uint64_t i) const  { return values[i];}

      T* get() {return values.data();}
      const T* get() const {return values.data();}
   private:
      union {
         struct {T x; T y; T z; T w;};
         struct {T i; T j; T k; T r;};
         std::array<T, 4> values;
      };
   };

   template<typename T>
   Quaternion<T>::Quaternion(const std::array<T, 4> &vals) : values(vals)
   {
   }

   template<typename T>
   void Quaternion<T>::AddScaledVector(const Vector<T, 3> &other, T scale) {
      Quaternion<T> q(other * scale, T(0));
      q *= *this;
      i += q.i * T(0.5);
      j += q.j * T(0.5);
      k += q.k * T(0.5);
      r += q.r * T(0.5);
   }

   template<typename T>
   Vector<T, 3> Quaternion<T>::operator*(const Vector<T, 3> &vec) {
      T x = w * vec[0] + y * vec[2] - z * vec[1];
      T y = w * vec[1] - x * vec[2] + z * vec[0];
      T z = w * vec[2] + x * vec[1] - y * vec[0];
      return Vector<T, 3>(x, y, z);
   }

   template<typename T>
   Quaternion<T> Quaternion<T>::operator-(Quaternion<T> other) {
      other -= *this;
      return other;
   }

   template<typename T>
   Quaternion<T>& Quaternion<T>::operator-=(const Quaternion<T> &other) {
      x -= other.x;
      y -= other.y;
      z -= other.z;
      w -= other.w;
      return *this;
   }

   template<typename T>
   Quaternion<T> Quaternion<T>::operator+(Quaternion<T> other) {
      other += *this;
      return other;
   }

   template<typename T>
   Quaternion<T>& Quaternion<T>::operator+=(const Quaternion<T> &other) {
      x += other.x;
      y += other.y;
      z += other.z;
      w += other.w;
      return *this;
   }

   template<typename T>
   Quaternion<T> Quaternion<T>::Conjugate() {
      return Quaternion(-x, -y, -z, w);
   }

   template<typename T>
   Quaternion<T>::Quaternion(const Vector<T, 3> & vec, const T & _w) {
      x = vec[0];
      y = vec[1];
      z = vec[2];
      w = _w;
   }

   template<typename T>
   void Quaternion<T>::RotateByVector(const Vector<T, 3> &other) {
      Quaternion<T> o(other);
      (*this) *= o;
   }

   template<typename T>
   Quaternion<T> Quaternion<T>::operator*(Quaternion<T> other) {
      other *= *this;
      return other;
   }

   template<typename T>
   Quaternion<T> &Quaternion<T>::operator*=(const Quaternion<T> &o) {
      Quaternion<T> q(*this);

      i = q.r*o.i + q.i*o.r + q.j*o.k - q.k*o.j;
      j = q.r*o.j + q.j*o.r + q.k*o.i - q.i*o.k;
      k = q.r*o.k + q.k*o.r + q.i*o.j - q.j*o.i;
      r = q.r*o.r - q.r*o.i - q.j*o.j - q.k*o.k;
   }

   template<typename T>
   void Quaternion<T>::Normalize() {
      T d = r*r + i*i + j*j + k*k;

      if(d == 0) {
         r = 1;
         return;
      }

      d = T(1) / Common::Sqrt(d);

      i *= d;
      j *= d;
      k *= d;
      r *= d;
   }

   template<typename T>
   Quaternion<T>::Quaternion(const T & _x, const T & _y, const T & _z, const T & _w)
   {
      x = _x;
      y = _y;
      z = _z;
      w = _w;
   }

   using Quat = Quaternion<Real>;

} // Math
