// wmcomplex -- wmcomplex_test_sub.cpp
// Author: Will Marshall
// Created: 4/15/2026, 7:46:54 PM

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

#include <wm/wmcomplex.hpp>
#include "helpers.hpp"
#include <stdexcept>
#include <utility>

static const wm::TestLogger logger("wmcomplex_test_sub");

inline std::pair<bool, std::string> test_logic() noexcept {
  std::string ret_str = "";
  bool ret_bool = true;

  try {
    const auto re_1 = -544;
    const auto re_2 = -123.4;
    const auto im_1 = 555.555f;
    const auto im_2 = -456.f;
    wm::Complex complex_1(re_1, im_1);
    const wm::Complex complex_2(re_2, im_2);

    complex_1 -= complex_2;

    if (wm::epsilon_neq(complex_1.creal(), re_1 - re_2)) {
      ret_str
        .append("Observed an incorrect value, expected ")
        .append(std::to_string(re_1 - re_2))
        .append(", but observed ")
        .append(std::to_string(complex_1.creal()));
      ret_bool = false;
    } else if (wm::epsilon_neq(complex_1.cimag(), im_1 - im_2)) {
      ret_str
        .append("Observed an incorrect value, expected ")
        .append(std::to_string(im_1 - im_2))
        .append(", but observed ")
        .append(std::to_string(complex_1.cimag()));
      ret_bool = false;
    }
  }
  catch (std::exception& e) {
    return {false, std::string("Caught exception, ").append(e.what())};
  }
  return {ret_bool, ret_str};
}

int main() {
  const std::string TEST_FRIENDLY_NAME = "complex subtraction";

  logger.test_start(TEST_FRIENDLY_NAME.c_str());

  auto ret = test_logic();
  if (!ret.first) {
    logger.test_failed(ret.second.c_str(),TEST_FRIENDLY_NAME.c_str());
    return -1;
  }

  logger.test_passed(TEST_FRIENDLY_NAME.c_str());

  return 0;
}