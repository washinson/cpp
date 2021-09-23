//
// Created by sanya112001 on 9/23/21.
//
#include "../../gtest/googletest/include/gtest/gtest.h"
#include "../long-alg_lib/big_integer.h"

TEST(big_integer, normal_create) {
    big_integer bigInteger("10000000");
    ASSERT_EQ(std::string(bigInteger), "10000000");
}

TEST(big_integer, normal_create_big) {
    big_integer bigInteger("123456789123456789123456789123456789000123000");
    ASSERT_EQ(std::string(bigInteger), "123456789123456789123456789123456789000123000");
}

TEST(big_integer, check_sum) {
    big_integer bigInteger1("123456789123456789123456789123456789000123000");
    big_integer bigInteger2("123456789123456789123456789123456789000123000");
    ASSERT_EQ(std::string(bigInteger1 + bigInteger2), "246913578246913578246913578246913578000246000");
}

TEST(big_integer, check_sum_0) {
    big_integer bigInteger1("0");
    big_integer bigInteger2("0");
    ASSERT_EQ(std::string(bigInteger1 + bigInteger2), "0");
}

TEST(big_integer, check_sum_minus) {
    big_integer bigInteger1("-1");
    big_integer bigInteger2("1");
    ASSERT_EQ(std::string(bigInteger1 + bigInteger2), "0");
}

TEST(big_integer, check_less) {
    big_integer bigInteger1("2");
    big_integer bigInteger2("3");
    ASSERT_LT(bigInteger1, bigInteger2);
}

TEST(big_integer, check_less_eq) {
    big_integer bigInteger1("3");
    big_integer bigInteger2("3");
    ASSERT_LE(bigInteger1, bigInteger2);
}

TEST(big_integer, check_greater) {
    big_integer bigInteger1("4");
    big_integer bigInteger2("3");
    ASSERT_GT(bigInteger1, bigInteger2);
}

TEST(big_integer, check_greater_eq) {
    big_integer bigInteger1("3");
    big_integer bigInteger2("3");
    ASSERT_GE(bigInteger1, bigInteger2);
}

TEST(big_integer, check_eq) {
    big_integer bigInteger1("3");
    big_integer bigInteger2("3");
    ASSERT_EQ(bigInteger1, bigInteger2);
}