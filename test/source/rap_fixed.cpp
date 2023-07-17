#include <doctest/doctest.h>
#include <rapfplib/rap_fixed.h>

#include <iostream>

TEST_CASE("RAP_FIXED_1") {
  using namespace rap;
  rap_fixed<5, 2, true> test_fixed;
  test_fixed.set_data(5);
  CHECK_EQ(test_fixed.show_data(), 1.25);
}
