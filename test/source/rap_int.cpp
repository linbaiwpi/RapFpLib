#include <doctest/doctest.h>
#include <rapfplib/rap_int.h>

#include <iostream>

TEST_CASE("RAP_INT_1") {
  using namespace rap;
  rap_int<5, true> test_int;
  test_int.set_data(5);
  CHECK(test_int.get_data() == 5);
  CHECK(test_int.get_rawdata() == 5);
}

TEST_CASE("RAP_INT_2") {
  using namespace rap;
  rap_int<5, true> test_int;
  test_int.set_data(31);
  CHECK(test_int.get_data() == -1);
  CHECK(test_int.get_rawdata() == 0x1F);
}

TEST_CASE("RAP_INT_3") {
  using namespace rap;
  rap_int<5, true> test_int;
  test_int.set_data(-12);
  CHECK(test_int.get_data() == -12);
  CHECK(test_int.get_rawdata() == 0b10100);
}

TEST_CASE("RAP_INT_4") {
  using namespace rap;
  rap_int<5, true> test_int;
  test_int.set_data(-17);
  rap_int<5, true> test_int2(test_int);
  CHECK(test_int2.get_data() == 15);
  CHECK(test_int2.get_rawdata() == 0b01111);
}

// copy constructor
TEST_CASE("RAP_INT_5") {
  using namespace rap;
  rap_int<5, true> test_int;
  test_int.set_data(-12);
  rap_int<5, true> test_int2 = test_int;
  CHECK(test_int2.get_data() == -12);
  CHECK(test_int2.get_rawdata() == 0b10100);
}

// operator override =
TEST_CASE("RAP_INT_6") {
  using namespace rap;
  rap_int<5, true> test_int = -12;
  rap_int<5, true> test_int2 = test_int;
  CHECK(test_int2.get_data() == -12);
  CHECK(test_int2.get_rawdata() == 0b10100);
}

// operator override +
TEST_CASE("RAP_INT_7") {
  using namespace rap;
  rap_int<5, true> test_int = -5;
  rap_int<5, true> test_int2 = -5;
  test_int = test_int2 + test_int2;
  CHECK(test_int.get_data() == -10);
}

TEST_CASE("RAP_INT_8") {
  using namespace rap;
  rap_int<5, true> test_int = -12;
  rap_int<5, true> test_int2 = -12;
  test_int = test_int2 + test_int2;
  CHECK(test_int.get_data() == 8);
}

// operator override *
TEST_CASE("RAP_INT_9") {
  using namespace rap;
  rap_int<5, true> test_int = -2;
  rap_int<5, true> test_int2 = -3;
  test_int = test_int * test_int2;
  CHECK(test_int.get_data() == 6);
}

TEST_CASE("RAP_INT_10") {
  using namespace rap;
  rap_int<5, true> test_int = -6;
  rap_int<5, true> test_int2 = -4;
  test_int = test_int * test_int2;
  CHECK(test_int.get_data() == -8);
}

// operator override <<
TEST_CASE("RAP_INT_11") {
  using namespace rap;
  rap_int<5, true> test_int = -2;
  rap_int<5, true> test_int2 = -4;
  test_int2 = test_int << 2;
  CHECK(test_int2.get_data() == -8);
}

TEST_CASE("RAP_INT_12") {
  using namespace rap;
  rap_int<5, true> test_int = -6;
  rap_int<5, true> test_int2 = -4;
  test_int2 = test_int << 2;
  CHECK(test_int2.get_data() == 8);
}

// operator override <<
TEST_CASE("RAP_INT_13") {
  using namespace rap;
  rap_int<5, true> test_int = -2;
  rap_int<5, true> test_int2 = -4;
  test_int2 = test_int >> 2;
  CHECK(test_int2.get_data() == -1);
}

TEST_CASE("RAP_INT_14") {
  using namespace rap;
  rap_int<5, true> test_int = -8;
  rap_int<5, true> test_int2 = -4;
  test_int2 = test_int >> 2;
  CHECK(test_int2.get_data() == -2);
}