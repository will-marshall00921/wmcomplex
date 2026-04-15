// wmcomplex -- multiops.hpp
// Author: Will Marshall
// Created: 4/14/2026, 8:44:55 PM

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

#ifndef WM_COMPLEX_MULTIOPS_HPP
#define WM_COMPLEX_MULTIOPS_HPP

#include "config.hpp"
#include "complex.hpp"
#include <utility>

namespace wm {
  namespace complex {
    using ComplexPair = std::pair<Complex,Complex>;

    /**
     * @brief Add pairs of Complex values
     * @param a The first Complex in the left-hand-side pair
     * @param b The second Complex in the left-hand-side pair
     * @param c The first Complex in the right-hand-side pair
     * @param d The second Complex in the right-hand-side pair
     * @returns A pair of Complex values. The first contains a+c, the second
     *          contains b+d
     */
    WMCOMPLEX_API ComplexPair addx2 (
      const Complex& a,
      const Complex& b,
      const Complex& c,
      const Complex& d
    ) noexcept;

    /**
     * @brief Add pairs of Complex values
     * @param ab The left-hand-side pair
     * @param cd The right-hand-side pair
     * @returns A pair of Complex values. The first contains a+c, the second
     *          contains b+d
     */
    inline ComplexPair addx2 (
      const ComplexPair& ab, 
      const ComplexPair& cd
    ) noexcept {
      return addx2(ab.first,ab.second,cd.first,cd.second);
    }

    /**
     * @brief Subtract pairs of Complex values
     * @param a The first Complex in the left-hand-side pair
     * @param b The second Complex in the left-hand-side pair
     * @param c The first Complex in the right-hand-side pair
     * @param d The second Complex in the right-hand-side pair
     * @returns A pair of Complex values. The first contains a-c, the second
     *          contains b-d
     */
    WMCOMPLEX_API ComplexPair subx2 (
      const Complex& a,
      const Complex& b,
      const Complex& c,
      const Complex& d
    ) noexcept;

    /**
     * @brief Subtract pairs of Complex values
     * @param ab The left-hand-side pair
     * @param cd The right-hand-side pair
     * @returns A pair of Complex values. The first contains a-c, the second
     *          contains b-d
     */
    inline ComplexPair subx2 (
      const ComplexPair& ab,
      const ComplexPair& cd
    ) noexcept {
      return subx2(ab.first, ab.second, cd.first, cd.second);
    }

    /**
     * @brief Multiply pairs of Complex values
     * @param a The first Complex in the left-hand-side pair
     * @param b The second Complex in the left-hand-side pair
     * @param c The first Complex in the right-hand-side pair
     * @param d The second Complex in the right-hand-side pair
     * @returns A pair of Complex values. The first contains a*c, the second
     *          contains b*d
     */
    WMCOMPLEX_API ComplexPair mulx2 (
      const Complex& a,
      const Complex& b,
      const Complex& c,
      const Complex& d
    ) noexcept;

    /**
     * @brief Multiply pairs of Complex values
     * @param ab The left-hand-side pair
     * @param cd The right-hand-side pair
     * @returns A pair of Complex values. The first contains a*c, the second
     *          contains b*d
     */
    inline ComplexPair mulx2 (
      const ComplexPair& ab,
      const ComplexPair& cd
    ) noexcept {
      return mulx2(ab.first, ab.second, cd.first, cd.second);
    }
  }
}

#endif // WM_COMPLEX_MULTIOPS_HPP