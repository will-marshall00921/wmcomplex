// wm -- multiops.cpp
// Author: Will Marshall
// Created: 4/14/2026, 8:54:38 PM

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

#include <wm/complex/multiops.hpp>
#include <immintrin.h>

namespace wm::complex {
  ComplexPair addx2(
    const Complex& a,
    const Complex& b,
    const Complex& c,
    const Complex& d
  ) noexcept {
    __m256d ab_vec = _mm256_set_m128d(
      _mm_load_pd(b.cdata()),
      _mm_load_pd(a.cdata())
    );
    __m256d cd_vec = _mm256_set_m128d(
      _mm_load_pd(c.cdata()),
      _mm_load_pd(d.cdata())
    );
    __m256d sum_vec = _mm256_add_pd(ab_vec, cd_vec);
    ComplexPair res;
    _mm_store_pd(res.first.data(), _mm256_castpd256_pd128(sum_vec));
    _mm_store_pd(res.second.data(), _mm256_extractf128_pd(sum_vec,1));
    return res;
  }

  ComplexPair subx2(
    const Complex& a,
    const Complex& b,
    const Complex& c,
    const Complex& d
  ) noexcept {
    __m256d ab_vec = _mm256_set_m128d(
      _mm_load_pd(b.cdata()),
      _mm_load_pd(a.cdata())
    );
    __m256d cd_vec = _mm256_set_m128d(
      _mm_load_pd(d.cdata()),
      _mm_load_pd(c.cdata())
    );
    __m256d sub_vec = _mm256_sub_pd(ab_vec, cd_vec);
    ComplexPair res;
    _mm_store_pd(res.first.data(), _mm256_castpd256_pd128(sub_vec));
    _mm_store_pd(res.second.data(), _mm256_extractf128_pd(sub_vec,1));
    return res;
  }

  ComplexPair mulx2(
    const Complex& a,
    const Complex& b,
    const Complex& c,
    const Complex& d
  ) noexcept {
    // The expected result is: [ 
    //          [Re{a}*Re{c} - Im{a}*Im{c}, Re{a}*Im{c} + Im{a}*Re{c}],
    //          [Re{b}*Re{d} - Im{b}*Im{d}, Re{b}*Im{d} + Im{b}*Re{d}]
    //      ]
    // GOAL: A. Get [Re{a}*Re{c}, Re{a}*Im{c}, Re{b}*Re{d}, Re{b}*Im{d}]
    //        A1. Get [Re{a}, Re{a}, Re{b}, Re{b}]
    //        A2. Get [Re{c}, Im{c}, Re{d}, Im{d}]
    //        A3. Get mul(A1, A2)
    //       B. Get [Im{a}*Im{c}, Im{a}*Re{c}, Im{b}*Im{d}, Im{b}*Re{d}]
    //        B1. Get [Im{a}, Im{a}, Im{b}, Im{b}]
    //        B2. Get [Im{c}, Re{c}, Im{d}, Re{d}]
    //        B3. Get mul(B1, B2)
    //       C. Get addsub(A3, B3)
    //       D. write C to cache
    //        D1. write low pair of C to first output
    //        D2. write hi pair of C to second output
    __m128d c_data_vec = _mm_load_pd(c.cdata());
    __m128d d_data_vec = _mm_load_pd(d.cdata());  

    __m256d a3_vec = _mm256_mul_pd(
      _mm256_set_m128d(
        _mm_set1_pd(b.creal()),
        _mm_set1_pd(a.creal())
      ), // A1
      _mm256_set_m128d(
        d_data_vec,
        c_data_vec
      ) // A2
    ); // A3

    __m256d b3_vec = _mm256_mul_pd(
      _mm256_set_m128d(
        _mm_set1_pd(b.cimag()),
        _mm_set1_pd(a.cimag())
      ), // B1
      _mm256_set_m128d(
        _mm_permute_pd(d_data_vec, _MM_SHUFFLE2(0, 1)),
        _mm_permute_pd(c_data_vec, _MM_SHUFFLE2(0, 1))
      ) // B2
    ); // B3

    __m256d c_vec = _mm256_addsub_pd(a3_vec, b3_vec); // C

    ComplexPair ret;

    _mm_store_pd(
      ret.first.data(),
      _mm256_castpd256_pd128(c_vec)
    ); // D1

    _mm_store_pd(
      ret.second.data(),
      _mm256_extractf128_pd(c_vec, 1)
    ); // D2

    return ret;
  }
}