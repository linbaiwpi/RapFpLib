#include <doctest/doctest.h>
#include <rapfplib/rap_int.h>

#include <iostream>

TEST_CASE("RAP_INT_1") {
  using namespace rap;
  rap_int<5, true> test_int;
  test_int.set_data(5);
  CHECK(test_int.get_data() == 5);
}

TEST_CASE("RAP_INT_2") {
  using namespace rap;
  rap_int<5, true> test_int;
  test_int.set_data(31);
  CHECK(test_int.get_data() == 15);
}
