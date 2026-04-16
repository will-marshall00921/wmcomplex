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

static const TestLogger logger("wmcomplex_test_<NAME>"); // TODO: replace the name ...

inline std::pair<bool, std::string> test_logic() noexcept {
  std::string ret_str = "";
  bool ret_bool = true;

  try {
    /*
    * Test Logic goes here
    */
    // TODO: add test ...
  }
  catch (std::exception& e) {
    return {false, std::string("Caught exception, ").append(e.what())};
  }
  return {ret_bool, ret_str};
}

int main() {
  const std::string TEST_FRIENDLY_NAME = "<SOME NAME>"; // TODO: replace the friendly name ...

  logger.test_start(TEST_FRIENDLY_NAME.c_str());

  auto ret = test_logic();
  if (!ret.first) {
    logger.test_failed(ret.second.c_str(),TEST_FRIENDLY_NAME.c_str());
    return -1;
  }

  logger.test_passed(TEST_FRIENDLY_NAME.c_str());

  return 0;
}