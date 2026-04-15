// wm -- complex.hpp
// Author: Will Marshall
// Created: 4/14/2026, 5:56:28 PM

/*  
 *  A lightweight C++ complex value library designed around SIMD operations
 *  Copyright (C) 2026  William Marshall
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 * USA
 */

#ifndef WM_COMPLEX_COMPLEX_HPP
#define WM_COMPLEX_COMPLEX_HPP

#include <type_traits>
#include "config.hpp"

namespace wm {
  /**
   * @brief A simple data structure for complex values
   */
  class WMCOMPLEX_API Complex {
    protected:
      /// @brief The contained values
      alignas(16) double m_data[2];

      /**
       * @brief Get the cached magnitude
       * @returns The cached magnitude, which may be calculated when the cache
       *          is determined to be out of date
       */
      inline const double& cached_mag() const noexcept {
        return (m_is_cached) 
          ? (m_cached_mag) 
          : (this->update_cache().m_cached_mag);
      }
      
      /**
       * @brief Get the cached square-magnitude
       * @returns The cached square-magnitude, which may be calculated when the
       *          cache is determined to be out of date
       */
      inline const double& cached_mag2() const noexcept {
        return (m_is_cached) 
          ? (m_cached_mag2) 
          : (this->update_cache().m_cached_mag2);
      }

      /**
       * @brief Update the cached values
       * @returns A reference to the Complex containing the updated cache values
       */
      const Complex& update_cache() const noexcept;

    private:
      /// @brief The cached magnitude
      mutable double m_cached_mag;
      /// @brief The cached square-magnitude 
      mutable double m_cached_mag2;
      /// @brief The cache state flag
      mutable bool m_is_cached;

    public:
      /**
       * Default constructor
       */
      inline Complex() noexcept
        : m_data { 0.0, 0.0 }
        , m_cached_mag { 0.0 }
        , m_cached_mag2 { 0.0 }
        , m_is_cached { true }
      {}
      /**
       * @brief Value constructor
       * @param re The real part of the complex value. The default is 0
       * @param im The imaginary part of the complex value. The default is 0
       */
      template <
        typename _ReTp,
        typename _ImTp,
        typename = std::enable_if_t<
          (std::is_arithmetic_v<_ReTp>)
          && (std::is_arithmetic_v<_ImTp>)
        >
      >
      inline Complex (
        _ReTp re,
        _ImTp im = 0
      ) noexcept
        : m_data {
          static_cast<double>(re),
          static_cast<double>(im)
        }
        , m_cached_mag2 { 0.0 }
        , m_cached_mag { 0.0 }
        , m_is_cached { false } 
      {}

      /**
       * @brief Copy constructor
       * @param other The Complex instance to copy
       */
      inline Complex (const Complex& other) noexcept = default;

      /**
       * @brief Move constructor
       * @param other The Complex instance to move
       */
      inline Complex(Complex&& other) noexcept = default;

      /**
       * @brief Deconstructor
       */
      inline ~Complex() noexcept = default;

      /**
       * @brief Copy-assignment operator
       * @param rhs The Complex instance to copy
       * @returns A reference to the original instance updated with the copied
       *          values
       */
      inline Complex& operator = (const Complex& rhs) noexcept = default;
      
      /**
       * @brief Move-assignment operator
       * @param rhs The Complex instance to move
       * @returns A reference to the original instance updated with the moved
       *          data
       */
      inline Complex& operator = (Complex&& rhs) noexcept = default;

      /**
       * @brief Get the real part of the complex value
       * @returns A reference to the contained real value
       */
      inline const double& creal() const noexcept { return m_data[0]; }

      /**
       * @copydoc creal() const
       * @details Resets the cache of the instance when returning a mutable
       *          reference
       */
      double& real() noexcept;

      /**
       * @brief Get the imaginary part of the complex value
       * @returns A reference to the contained imaginary value
       */
      inline const double& cimag() const noexcept { return m_data[1]; }

      /**
       * @copydoc cimag() const
       * @details Resets the cache of the instance when returning a mutable
       *          reference
       */
      double& imag() noexcept;

      /**
       * @brief Get the underlying data storage
       * @returns A pointer to the underlying data storage of the Complex instance
       */
      inline const double* cdata() const noexcept { return m_data; }
      /**
       * @copydoc cdata() const
       * @details Resets the cache of the instance when returning a mutable
       *          reference
       */
      double* data() noexcept;

      /**
       * @brief Get the square-magnitude of the Complex value
       * @returns The square-magnitude, the components of the Complex added in
       *          quadrature
       */
      inline double mag2() const noexcept { return cached_mag2(); }
      
      /**
       * @brief Get the magnitude of the Complex value
       * @returns The magnitude, the square-root of the square-magnitude
       */
      inline double mag() const noexcept { return cached_mag(); }
      
      /**
       * @brief Multiplication assignment operator
       * @param rhs The value to mutliply by
       * @returns A reference to the original Complex value after performing
       *          the assignment
       */
      Complex& operator *= (const Complex& rhs) noexcept;
      /**
       * @copydoc operator *= (const Complex&)
       */
      Complex& operator *= (double rhs) noexcept;
      /**
       * @copydoc operator *= (const Complex&)
       */
      template <
        typename _Tp,
        typename = std::enable_if_t<
          std::is_arithmetic_v<_Tp>
        >
      >
      inline Complex& operator *= (_Tp rhs) noexcept {
        return ((*this) *= static_cast<double>(rhs));
      }

      /**
       * @brief Division assignment operator
       * @param rhs The value to divide by
       * @returns A reference to the original Complex value after performing the
       *          assignment
       */
      Complex& operator /= (const Complex& rhs) noexcept;
      /**
       * @copydoc operator /= (const Complex&)
       */
      Complex& operator /= (double rhs) noexcept;
      /**
       * @copydoc operator /= (const Complex&)
       */
      template <
        typename _Tp,
        typename = std::enable_if_t<
          std::is_arithmetic_v<_Tp>
        >
      >
      inline Complex& operator /= (_Tp rhs) noexcept {
        return ((*this) /= static_cast<double>(rhs));
      }

      /**
       * @brief Addition assignment operator
       * @param rhs The value to sum with
       * @returns A reference to the original Complex value after performing the
       *          assignment
       */
      Complex& operator += (const Complex& rhs) noexcept;
      /**
       * @copydoc operator += (const Complex&)
       */
      Complex& operator += (double rhs) noexcept;
      /**
       * @copydoc operator += (const Complex&)
       */
      template <
        typename _Tp,
        typename = std::enable_if_t<
          std::is_arithmetic_v<_Tp>
        >
      >
      inline Complex& operator += (_Tp rhs) noexcept {
        return ((*this) += static_cast<double>(rhs));
      }

      /**
       * @brief Subtraction assignment operator
       * @param rhs The value to subtract by
       * @returns A reference to the original Complex value after performing the
       *          assignment
       */
      Complex& operator -= (const Complex& rhs) noexcept;
      /**
       * @copydoc operator -= (const Complex&)
       */
      Complex& operator -= (double rhs) noexcept;
      /**
       * @copydoc operator -= (const Complex&)
       */
      template <
        typename _Tp,
        typename = std::enable_if_t<
          std::is_arithmetic_v<_Tp>
        >
      >
      inline Complex& operator -= (_Tp rhs) noexcept {
        return ((*this) -= static_cast<double>(rhs));
      }

      /**
       * @brief Get the complex conjugate
       * @returns A Complex containing the conjugate of the original Complex
       */
      inline Complex conj() const noexcept {
        return Complex(m_data[0],-1*m_data[1]);
      }
  };

  inline Complex operator * (Complex lhs,const Complex& rhs) noexcept {
    return (lhs *= rhs);
  }
  template <
    typename _Tp,
    typename = std::enable_if_t<
      std::is_arithmetic_v<_Tp>
    >
  >
  inline Complex operator * (Complex lhs, _Tp rhs) noexcept {
    return (lhs *= rhs);
  }

  inline Complex operator / (Complex lhs,const Complex& rhs) noexcept {
    return (lhs /= rhs);
  }
  template <
    typename _Tp,
    typename = std::enable_if_t<
      std::is_arithmetic_v<_Tp>
    >
  >
  inline Complex operator / (Complex lhs, _Tp rhs) noexcept {
    return (lhs /= rhs);
  }

  inline Complex operator + (Complex lhs,const Complex& rhs) noexcept {
    return (lhs += rhs);
  }
  template <
    typename _Tp,
    typename = std::enable_if_t<
      std::is_arithmetic_v<_Tp>
    >
  >
  inline Complex operator + (Complex lhs, _Tp rhs) noexcept {
    return (lhs += rhs);
  }

  inline Complex operator - (Complex lhs,const Complex& rhs) noexcept {
    return (lhs -= rhs);
  }
  template <
    typename _Tp,
    typename = std::enable_if_t<
      std::is_arithmetic_v<_Tp>
    >
  >
  inline Complex operator - (Complex lhs, _Tp rhs) noexcept {
    return (lhs -= rhs);
  }
}

#endif // WM_COMPLEX_COMPLEX_HPP