#include <gtest/gtest.h>

#include <array>

#include "./test.h"

TEST(ARRAY_CONSTR, case1) {
  s21::array<int, 5> s21_arr;
  EXPECT_EQ(s21_arr.size(), 5U);
}

TEST(ARRAY_CONSTR, case2) {
  s21::array<int, 5> s21_arr{1, 2, 3, 4, 5};
  std::array<int, 5> std_arr{1, 2, 3, 4, 5};
  for (size_t i = 0; i < 5; i++) EXPECT_EQ(s21_arr.at(i), std_arr.at(i));
}

TEST(ARRAY_CONSTR, case3) {
  s21::array<int, 5> a{1, 2, 3, 4, 5};
  s21::array<int, 5> b(a);
  for (size_t i = 0; i < 5; i++) EXPECT_EQ(a[i], b[i]);
}

TEST(ARRAY_CONSTR, case4) {
  s21::array<int, 5> a{1, 2, 3, 4, 5};
  s21::array<int, 5> b(std::move(a));
  EXPECT_EQ(b.size(), 5U);
  EXPECT_EQ(1, b[0]);
  EXPECT_EQ(2, b[1]);
  EXPECT_EQ(3, b[2]);
  EXPECT_EQ(4, b[3]);
  EXPECT_EQ(5, b[4]);
}

TEST(ARRAY_OPERATOReq, case1_copy) {
  s21::array<int, 5> a{1, 2, 3, 4, 5};
  s21::array<int, 5> b{5, 4, 3, 2, 1};
  b = a;
  for (size_t i = 0; i < 5; i++) EXPECT_EQ(a[i], b[i]);
}

TEST(ARRAY_OPERATOReq, case2_move) {
  s21::array<int, 5> a{1, 2, 3, 4, 5};
  s21::array<int, 5> b{5, 4, 3, 2, 1};
  b = std::move(a);
  EXPECT_EQ(a.size(), 0U);
  EXPECT_EQ(b.size(), 5U);
  EXPECT_EQ(1, b[0]);
  EXPECT_EQ(2, b[1]);
  EXPECT_EQ(3, b[2]);
  EXPECT_EQ(4, b[3]);
  EXPECT_EQ(5, b[4]);
}

TEST(ARRAY_FRONT, case1) {
  s21::array<int, 5> s21_arr{1, 2, 3, 4, 5};
  std::array<int, 5> std_arr{1, 2, 3, 4, 5};
  EXPECT_EQ(s21_arr.front(), std_arr.front());
}

TEST(ARRAY_BACK, case1) {
  s21::array<int, 5> s21_arr{1, 2, 3, 4, 5};
  std::array<int, 5> std_arr{1, 2, 3, 4, 5};
  EXPECT_EQ(s21_arr.back(), std_arr.back());
}

TEST(ARRAY_ITERATORS, case1) {
  s21::array<int, 5> s21_arr = {1, 2, 3, 4, 5};
  std::array<int, 5> std_arr = {1, 2, 3, 4, 5};
  s21::array<int, 5>::iterator s21_it = s21_arr.begin();
  std::array<int, 5>::iterator std_it = std_arr.begin();
  EXPECT_EQ(*s21_it, *std_it);
}

TEST(ARRAY_ITERATORS, case2) {
  s21::array<int, 5> s21_arr = {1, 2, 3, 4, 5};
  std::array<int, 5> std_arr = {1, 2, 3, 4, 5};
  s21::array<int, 5>::iterator s21_it = s21_arr.data();
  std::array<int, 5>::iterator std_it = std_arr.data();
  EXPECT_EQ(*s21_it, *std_it);
}

TEST(ARRAY_ITERATORS, case3) {
  s21::array<int, 5> s21_arr = {1, 2, 3, 4, 5};
  std::array<int, 5> std_arr = {1, 2, 3, 4, 5};
  s21::array<int, 5>::iterator s21_it = s21_arr.end();
  std::array<int, 5>::iterator std_it = std_arr.end();
  EXPECT_EQ(*(s21_it - 1), *(std_it - 1));
}

TEST(ARRAY_ACCESS, case1) {
  s21::array<int, 5> s21_arr;
  s21_arr.fill(5);
  EXPECT_ANY_THROW(s21_arr.at(-1));
}

TEST(ARRAY_ACCESS, case2) {
  s21::array<int, 5> s21_arr;
  s21_arr.fill(5);
  EXPECT_ANY_THROW(s21_arr.at(6));
}

TEST(ARRAY_EMPTY, case1) {
  s21::array<int, 0> s21_arr;
  EXPECT_TRUE(s21_arr.empty());
}

TEST(ARRAY_EMPTY, case2) {
  s21::array<int, 5> s21_arr;
  EXPECT_FALSE(s21_arr.empty());
}

TEST(ARRAY_MAXSIZE, case1) {
  s21::array<int, 5> s21_arr;
  std::array<int, 5> std_arr;
  EXPECT_EQ(s21_arr.max_size(), std_arr.max_size());
}

TEST(ARRAY_SWAP, case1) {
  s21::array<int, 5> a{1, 2, 3, 4, 5};
  s21::array<int, 5> copy_a(a);
  s21::array<int, 5> b{5, 4, 3, 2, 1};
  s21::array<int, 5> copy_b(b);
  a.swap(b);
  for (size_t i = 0; i < 5; i++) {
    EXPECT_EQ(b[i], copy_a[i]);
    EXPECT_EQ(a[i], copy_b[i]);
  }
}

TEST(ARRAY_SWAP, case2) {
  s21::array<int, 5> a{1, 2, 3, 4, 5, 6};
  s21::array<int, 5> b{5, 4, 3, 2, 1};
  EXPECT_ANY_THROW(a.swap(b));
}

TEST(ARRAY_FILL, case1) {
  s21::array<int, 5> a;
  a.fill(5);
  for (size_t i = 0; i < 5; i++) EXPECT_EQ(a[i], 5);
}