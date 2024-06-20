//
// Created by ianpo on 01/06/2024.
//

#pragma once

#include <cstdint>
#include <cmath>
#include <cstring>
#include <cassert>
#include <array>
#include <stdexcept>
#include "Common.hpp"

namespace Math {

   template<typename T, uint64_t N>
   class Vector
   {
   public:
      Vector();
      Vector(const Vector<T, N>&) = default;
      Vector<T, N>& operator=(const Vector<T, N>&) = default;
      ~Vector() = default;

      template<typename OT, uint64_t ON>
      explicit Vector(const Vector<OT, ON>& vec);

      template<typename OT, uint64_t ON>
      Vector(const Vector<OT, ON>& vec, const std::array<T, N-ON>& fill);
      Vector(const std::array<T, N>&);
      Vector(const T&);

      Vector<T, N>& operator+=(const Vector<T, N>& other);
      Vector<T, N>& operator-=(const Vector<T, N>& other);
      Vector<T, N>& operator+=(const T& scalar);
      Vector<T, N>& operator-=(const T& scalar);
      Vector<T, N>& operator*=(const T& scalar);

      T& operator[](uint64_t i) {return values[i];}
      const T& operator[](uint64_t i) const {return values[i];}

      T* get() {return values.data();}
      const T* get() const {return values.data();}
   public:
      T SqrMagnitude();
      T Magnitude();
      void Normalize();
   private:
      std::array<T, N> values;
   };

   template<typename T, uint64_t N>
   Vector<T, N>::Vector(const T & val) {
      for (int i = 0; i < N; ++i) {
         values[i] = val;
      }
   }

   template<typename T, uint64_t N>
   T Vector<T, N>::SqrMagnitude() {
      T sqrMagnitude = 0;

      // Calculate the magnitude (length) of the vector
      for (uint64_t i = 0; i < N; ++i) {
         sqrMagnitude += this->values[i] * this->values[i];
      }

      return sqrMagnitude;
   }
   template<typename T, uint64_t N>
   T Vector<T, N>::Magnitude() {
      return Common::Sqrt(SqrMagnitude());
   }

   template<typename T, uint64_t N>
   void Vector<T, N>::Normalize() {
      T magnitude = Magnitude();

      // Check if magnitude is zero
      if (Common::Abs(magnitude) < 1e-9) {
         throw std::runtime_error("Can't normalize a zero vector");
      }

      // Divide each component by the magnitude
      for (uint64_t i = 0; i < N; ++i) {
         this->values[i] /= magnitude;
      }
   }

   template<typename T, uint64_t N>
   Vector<T, N> &Vector<T, N>::operator+=(const Vector<T, N> &other) {
      for (uint64_t i = 0; i < N; ++i) {
         values[i] += other[i];
      }
      return *this;
   }

   template<typename T, uint64_t N>
   Vector<T, N> &Vector<T, N>::operator-=(const Vector<T, N> &other) {
      for (uint64_t i = 0; i < N; ++i) {
         values[i] -= other[i];
      }
      return *this;
   }

   template<typename T, uint64_t N>
   Vector<T, N> &Vector<T, N>::operator+=(const T& scalar) {
      for (uint64_t i = 0; i < N; ++i) {
         values[i] += scalar;
      }
      return *this;
   }

   template<typename T, uint64_t N>
   Vector<T, N> &Vector<T, N>::operator-=(const T& scalar) {
      for (uint64_t i = 0; i < N; ++i) {
         values[i] -= scalar;
      }
      return *this;
   }

   template<typename T, uint64_t N>
   Vector<T, N> &Vector<T, N>::operator*=(const T& scalar) {
      for (uint64_t i = 0; i < N; ++i) {
         values[i] *= scalar;
      }
      return *this;
   }

   template<typename T, uint64_t N>
   template<typename OT, uint64_t ON>
   Vector<T, N>::Vector(const Vector<OT, ON> &vec, const std::array<T, N-ON> &fill) {
      for (int i = 0; i < ON; ++i) {
         values[i] = reinterpret_cast<T>(vec[i]);
      }
      for(int i = 0; i < N-ON; ++i) {
         values[ON + i] = fill[i];
      }
   }

   template<typename T, uint64_t N>
   template<typename OT, uint64_t ON>
   Vector<T, N>::Vector(const Vector<OT, ON>& vec) {
      std::memset(values.data(), 0, N * sizeof(T));
      for (int i = 0; i < Common::Min(N, ON); ++i) {
         values[i] = reinterpret_cast<T>(vec[i]);
      }
   }

   template<typename T, uint64_t N>
   Vector<T, N>::Vector() {
      std::memset(values.data(), 0, N * sizeof(T));
   }


   template<typename T, uint64_t N>
   Vector<T,N>::Vector(const std::array<T, N>& other) : values(other)
   {
   }


   template<typename T, uint64_t N>
   Vector<T, N> operator-(Vector<T, N> lft, const T& scalar) {
      lft -= scalar;
      return lft;
   }

   template<typename T, uint64_t N>
   Vector<T, N> operator+(Vector<T, N> lft, const T& scalar) {
      lft += scalar;
      return lft;
   }

   template<typename T, uint64_t N>
   Vector<T, N> operator*(Vector<T, N> lft, const T& scalar) {
      lft *= scalar;
      return lft;
   }

   template<typename T, uint64_t N>
   Vector<T, N> operator-(Vector<T, N> lft, const Vector<T, N>& other) {
      lft -= other;
      return lft;
   }
   template<typename T, uint64_t N>
   Vector<T, N> operator-(const Vector<T, N>& lft) {
	   Vector<T, N> other (0);
	   other -= lft;
	   return other;
   }

   template<typename T, uint64_t N>
   Vector<T, N> operator+(Vector<T, N> lft, const Vector<T, N>& other) {
      lft += other;
      return lft;
   }

   using Vec4 = Vector<Real, 4>;
   using Vec3 = Vector<Real, 3>;
   using Vec2 = Vector<Real, 2>;

} // Math
