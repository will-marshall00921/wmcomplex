// wmcomplex -- tests -- helpers.hpp
// Author: Will Marshall
// Created: 4/15/2026, 6:56:17 PM

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

#ifndef WMCOMPLEX_TESTS_HELPERS_HPP
#define WMCOMPLEX_TESTS_HELPERS_HPP

#include <string>
#include <iostream>
#include <type_traits>

namespace wm {
  class TestLogger {
    inline std::ostream& start_printout(std::ostream& _os) const noexcept {
      return _os << "[" << this->name << "]"; 
    } 

    public:
      const std::string name;

      inline TestLogger (const char* _name) noexcept
        : name { _name }
      {}

      inline void test_start(const char* test_name = "") const noexcept {
        start_printout(std::cout);
        std::cout << ": Starting" << ((*test_name != '\0') ? (" ") : (""))
          << test_name << "..." << std::endl;
      }

      inline void test_failed(
        const char* msg = "", 
        const char* test_name = ""
      ) const noexcept {
        std::ostream& _os = start_printout(std::cerr);
        if ((*test_name) != '\0') {
          _os << "[" << test_name << "]";
        }
        _os << "[" << "\x1b[31m" << "FAILED" << "\x1b[39m" << "]";
        if ((*msg) != '\0') {
          _os << ": " << msg;
        }
        _os << std::endl;
      }

      inline void test_passed(const char* test_name = "") const noexcept {
        std::ostream& _os = start_printout(std::cout);
        if ((*test_name) != '\0') {
          _os << "[" << test_name << "]";
        }
        _os << "[" << "\x1b[32m" << "PASSED" << "\x1b[39m" << "]" << std::endl;
      }
  };

  template <
    typename _Lhs,
    typename _Rhs,
    typename _Ep = double,
    typename = std::enable_if_t<
      (std::is_arithmetic_v<_Lhs>)
      && (std::is_arithmetic_v<_Rhs>)
      && (std::is_floating_point_v<_Ep>)
    >
  >
  inline constexpr bool epsilon_eq(_Lhs _lhs, _Rhs _rhs, _Ep _ep = 1E-3) noexcept {
    return (
      (static_cast<double>(_lhs) >= (static_cast<double>(_rhs) - static_cast<double>(_ep)))
      && (static_cast<double>(_lhs) <= (static_cast<double>(_rhs) + static_cast<double>(_ep)))
    );
  }

  template <
    typename _Lhs,
    typename _Rhs,
    typename _Ep = double,
    typename = std::enable_if_t<
      (std::is_arithmetic_v<_Lhs>)
      && (std::is_arithmetic_v<_Rhs>)
      && (std::is_floating_point_v<_Ep>)
    >
  >
  inline constexpr bool epsilon_neq(_Lhs _lhs, _Rhs _rhs, _Ep _ep = 1E-3) noexcept {
    return (
      (static_cast<double>(_lhs) < (static_cast<double>(_rhs) - static_cast<double>(_ep)))
      || (static_cast<double>(_lhs) > (static_cast<double>(_rhs) + static_cast<double>(_ep)))
    );
  }
}

#endif // WMCOMPLEX_TESTS_HELPERS_HPP