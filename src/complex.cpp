// wm -- complex.cpp
// Author: Will Marshall
// Created: 4/14/2026, 6:09:10 PM

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

#include <immintrin.h>
#include <wm/complex/complex.hpp>
#include <cmath>

inline double intrinsic_mag2(__m128d x) noexcept {
  __m128d prod_vec = _mm_mul_pd(x, x);
    return _mm_cvtsd_f64(
      _mm_add_pd(
        prod_vec, 
        _mm_permute_pd(prod_vec, _MM_SHUFFLE2(0, 1))
      )
    );
}

namespace wm {
  const Complex& Complex::update_cache() const noexcept {
    m_cached_mag2 = intrinsic_mag2(_mm_load_pd(m_data));
    m_cached_mag = std::sqrt(m_cached_mag2);
    m_is_cached = true;
    return *this;
  }

  double& Complex::real() noexcept {
    m_is_cached = false; // set the cache flag to false since this is a mutable reference
    return m_data[0];
  }

  double& Complex::imag() noexcept {
    m_is_cached = false; // set the cache flag to false since this is a mutable reference
    return m_data[1];
  }

  double* Complex::data() noexcept {
    m_is_cached = false; // set the cache flag to false since the data is mutable through the pointer
    return m_data;
  }

  Complex& Complex::operator *= (const Complex& rhs) noexcept {
    __m128d rhs_vec = _mm_load_pd(rhs.m_data);
    // GOAL: A. get [Re{lhs}*Re{rhs}, Re{lhs},Im{rhs}]
    //       B. get [Im{lhs}*Im{rhs}, Im{lhs}*Re{rhs}]
    //       C. get addsub(A, B)
    //       D. write C to cache
    __m128d re_lhs = _mm_set1_pd(m_data[0]);
    __m128d prod_vec_1 = _mm_mul_pd(re_lhs, rhs_vec); // A
    __m128d im_lhs = _mm_set1_pd(m_data[1]);
    __m128d rhs_reversed = _mm_permute_pd(rhs_vec, _MM_SHUFFLE2(0, 1));
    __m128d prod_vec_2 = _mm_mul_pd(im_lhs, rhs_reversed); // B
    _mm_store_pd(
      m_data,
      _mm_addsub_pd(prod_vec_1, prod_vec_2) // C
    ); // D
    return (*this);
  }

  Complex& Complex::operator /= (const Complex& rhs) noexcept {
    // operation:
    // Re{lhs} -> (Re{lhs}*Re{rhs} + Im{lhs}*Im{rhs} ) / ||rhs||
    // Im{lhs} -> (Re{rhs}*Im{lhs} - Re{lhs}*Im{rhs}) / ||rhs||
    // GOAL:
    //  A. get [Im{lhs}, Re{lhs}]*Re{rhs}
    //  B. get [Re{lhs}, Im{lhs}]*Im{rhs}
    //  C. get addsub(A, B)
    //  D. get [||rhs||, ||rhs||]
    //  E. get C / D
    //  F. write E to cache
    __m128d lhs_vec = _mm_load_pd(m_data); // [Re{lhs}, Im{lhs}]
    __m128d lhs_reversed = _mm_permute_pd(lhs_vec, _MM_SHUFFLE2(0, 1)); // [Im{lhs}, Re{lhs}]
    __m128d a_vec = _mm_mul_pd(
      lhs_reversed,
      _mm_set1_pd(rhs.m_data[0])
    ); // A
    __m128d b_vec = _mm_mul_pd(
      lhs_vec,
      _mm_set1_pd(rhs.m_data[1])
    ); // B
    __m128d c_vec = _mm_addsub_pd(a_vec, b_vec); // C
    __m128d d_vec = _mm_set1_pd(rhs.cached_mag2()); // D
    _mm_store_pd(
      m_data,
      _mm_div_pd(c_vec, d_vec) // E
    ); // F
    return (*this);
  }

  Complex& Complex::operator += (const Complex& rhs) noexcept {
    _mm_store_pd(
      m_data,
      _mm_add_pd(
        _mm_load_pd(m_data),
        _mm_load_pd(rhs.m_data)
      )
    );
    return (*this);
  }

  Complex& Complex::operator -= (const Complex& rhs) noexcept {
    _mm_store_pd(
      m_data,
      _mm_sub_pd(
        _mm_load_pd(m_data),
        _mm_load_pd(rhs.m_data)
      )
    );
    return (*this);
  }
}