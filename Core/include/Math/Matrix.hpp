//
// Created by ianpo on 01/06/2024.
//

#pragma once

#include "Vector.hpp"
#include <cstdint>
#include <cmath>
#include <cstring>
#include <stdexcept>

namespace Math {

   template<typename T, uint64_t C, uint64_t R>
   class Matrix {
   public:
      using Col = Vector<T, C>;
      using Row = Vector<T, R>;
   public:
      Matrix();
      Matrix(const Matrix<T,C,R>&) = default;
      Matrix<T,C,R>& operator =(const Matrix<T,C,R>&) = default;
      ~Matrix() = default;

      template<typename OT, uint64_t OC, uint64_t OR>
      explicit Matrix(const Matrix<OT,OC,OR>& other);
      Matrix(const std::array<T, R * C> &values);

      static Matrix<T,C,R> Identity();

      T& operator()(uint64_t row, uint64_t col) {return rows[row][col];}
      const T& operator()(uint64_t row, uint64_t col) const  {return rows[row][col];}

      Col& operator[](uint64_t row) {return rows[row];}
      const Col& operator[](uint64_t row) const {return rows[row];}

      T* get() {return rows.front().get();}
      const T* get() const {return rows.front().get();}

      Matrix<T,C,R>& operator+=(const Matrix<T,C,R>& other);
      Matrix<T,C,R>& operator-=(const Matrix<T,C,R>& other);

      template<uint64_t OC>
      [[nodiscard]] Matrix<T,OC,R> operator*(const Matrix<T,OC,C>& other) const;
      [[nodiscard]] Vector<T,R> operator*(const Vector<T,C>& other) const;

      Matrix<T,C,R>& operator*=(const T& other);
   public:
      [[nodiscard]] Matrix<T, R, C> Transpose() const;
      [[nodiscard]] Matrix<T, std::min(C,R), std::min(C,R)> Inverse() const;
      [[nodiscard]] bool CanBeInverse() const;
      [[nodiscard]] T Determinant() const;
   private:
      union  {
         std::array<Col, R> rows;
         std::array<T, R*C> values;
      };
   };

   template<typename T, uint64_t C, uint64_t R>
   bool Matrix<T, C, R>::CanBeInverse() const {
      static_assert(C == R, "Only square matrices can be inversed");
      T det = this->Determinant();
      return (fabs(det) >= 1e-9);
   }

   template<typename T, uint64_t C, uint64_t R>
   T Matrix<T, C, R>::Determinant() const {
      static_assert(C == R, "The determinant can only be calculated for square matrices.");
      if(C != R) {
         return 0;
      }

      // Base case for 2x2 matrix
      if (R == 2)
         return (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);

      T det = 0;
      for (uint64_t p = 0; p < R; p++) {
         Matrix<T, R-1, R-1> subMatrix;

         for (uint64_t i = 1; i < R; i++) {
            uint64_t k = 0;
            for (uint64_t j = 0; j < R; j++) {
               if (j == p)
                  continue;

               subMatrix(i-1, k) = (*this)(i, j);
               k++;
            }
         }

         T factor = (*this)(0, p);
         if (p % 2 == 1)
            factor = -factor;

         det += factor * subMatrix.Determinant();
      }

      return det;
   }

   template<typename T, uint64_t C, uint64_t R>
   Matrix<T, C, R>::Matrix(const std::array<T, R * C> &values) {
      std::memcpy(this->values.data(), values.data(), sizeof(T) * R * C);
   }

   template<typename T, uint64_t C, uint64_t R>
   Matrix<T, C, R>::Matrix() {
      std::memset(rows, 0, sizeof(T) * C * R);
      if(C == R) {
         for (int i = 0; i < std::min(C, R); ++i) {
            rows[i][i] = 1;
         }
      }
   }

   template<typename T, uint64_t C, uint64_t R>
   template<typename OT, uint64_t OC, uint64_t OR>
   Matrix<T,C,R>::Matrix(const Matrix<OT,OC,OR>& other)
   {
      std::memset(rows, 0, sizeof(T) * C * R);
      for (int r = 0; r < std::min(OR, R); ++r) {
         for (int c = 0; c < std::min(OC, C); ++c) {
            rows[r][c] = other(r, c);
         }
      }
   }

   template<typename T, uint64_t C, uint64_t R>
   Matrix<T, C, R> Matrix<T, C, R>::Identity() {
      static_assert(C == R, "The matrix cannot be an identity one.");
      return Matrix<T, C, R>();
   }

   template<typename T, uint64_t C, uint64_t R>
   template<uint64_t OC>
   Matrix<T, OC, R> Matrix<T, C, R>::operator*(const Matrix<T, OC, C> &other) const {
      Matrix<T, OC, R> result {};

      for (uint64_t i = 0; i < R; ++i) {
         for (uint64_t j = 0; j < OC; ++j) {
            for (uint64_t k = 0; k < C; ++k) {
               result(i, j) += (*this)(i, k) * other(k, j);
            }
         }
      }

      return result;
   }

   template<typename T, uint64_t C, uint64_t R>
   Vector<T, R> Matrix<T, C, R>::operator*(const Vector<T, C>& other) const {
      Vector<T, R> result;

      for (uint64_t i = 0; i < R; ++i) {
         for (uint64_t j = 0; j < C; ++j) {
            result[i] += (*this)(i, j) * other[j];
         }
      }

      return result;
   }

   template<typename T, uint64_t C, uint64_t R>
   Matrix<T, C, R> &Matrix<T, C, R>::operator*=(const T &other) {
      for (auto& v : values) {
         v *= other;
      }
   }

   template<typename T, uint64_t C, uint64_t R>
   Matrix<T, C, R> &Matrix<T, C, R>::operator+=(const Matrix<T, C, R> &other) {
      for (uint64_t i = 0; i < R * C; ++i) {
         values[i] += other.values[i];
      }
      return *this;
   }

   template<typename T, uint64_t C, uint64_t R>
   Matrix<T, C, R> &Matrix<T, C, R>::operator-=(const Matrix<T, C, R> &other) {
      for (uint64_t i = 0; i < R * C; ++i) {
         values[i] -= other.values[i];
      }
      return *this;
   }

   template<typename T, uint64_t C, uint64_t R>
   Matrix<T, R, C> Matrix<T, C, R>::Transpose() const {
      Matrix<T, R, C> result;
      for (uint64_t i = 0; i < R; ++i) {
         for (uint64_t j = 0; j < C; ++j) {
            result(j, i) = (*this)(i, j);
         }
      }
      return result;
   }

   template<typename T, uint64_t C, uint64_t R>
   Matrix<T, std::min(C,R), std::min(C,R)> Matrix<T, C, R>::Inverse() const {
      const constexpr uint64_t N = std::min(C, R);
      Matrix<T, N, N> invMatrix = Matrix<T, N, N>::Identity();
      Matrix<T, N, N> tempMatrix = *this;

      static_assert(tempMatrix.CanBeInverse(), "The matrix cannot be inversed.");

      // Pivoting Phase
      for (uint64_t i = 0; i < N; ++i) {
         if (tempMatrix(i, i) == 0) {
            for (uint64_t j = i; j < N; ++j) {
               if (tempMatrix(j, i) != 0) {
                  std::swap(tempMatrix.data[i], tempMatrix.data[j]);
                  std::swap(invMatrix.data[i], invMatrix.data[j]);
                  break;
               }
            }
         }

         // Normalization Phase
         T div = tempMatrix(i, i);
         if(div == 0) {
            //TODO: See if I really want to throw.
            throw std::runtime_error("Matrix is not invertible.");
            return invMatrix;
         }
         for (uint64_t j = 0; j < N; ++j) {
            tempMatrix(i, j) /= div;
            invMatrix(i, j) /= div;
         }

         // Reduction Phase
         for (uint64_t j = 0; j < N; ++j) {
            if (i != j) {
               T mult = tempMatrix(j, i);
               for (uint64_t k = 0; k < N; ++k) {
                  tempMatrix(j, k) -= mult * tempMatrix(i, k);
                  invMatrix(j, k) -= mult * invMatrix(i, k);
               }
            }
         }
      }

      return invMatrix;
   }
   using Mat4 = Matrix<float, 4, 4>;
   using Mat3 = Matrix<float, 3, 3>;
   using Mat2 = Matrix<float, 2, 2>;

} // Math
