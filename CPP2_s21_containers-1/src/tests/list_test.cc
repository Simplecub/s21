#include <gtest/gtest.h>

#include <list>

#include "./test.h"

TEST(LIST, case1) {
  s21::list<int> s21_list_int;
  s21::list<double> s21_list_double;
  s21::list<std::string> s21_list_string;

  EXPECT_EQ(s21_list_int.size(), 0U);
  EXPECT_EQ(s21_list_double.size(), 0U);
  EXPECT_EQ(s21_list_string.size(), 0U);
}

TEST(LIST, case2) {
  s21::list<int> s21_list_int(5);
  s21::list<double> s21_list_double(5);
  s21::list<std::string> s21_list_string(5);

  EXPECT_EQ(s21_list_int.size(), 5U);
  EXPECT_EQ(s21_list_double.size(), 5U);
  EXPECT_EQ(s21_list_string.size(), 5U);
}

TEST(LIST, case3) {
  EXPECT_THROW(s21::list<int> s21_list_int(0), std::out_of_range);
  EXPECT_THROW(s21::list<double> s21_list_double(0), std::out_of_range);
  EXPECT_THROW(s21::list<std::string> s21_list_string(0), std::out_of_range);
}

TEST(LIST, case4) {
  s21::list<int> s21_list_int{1, 4, 8, 9};
  s21::list<double> s21_list_double{1.4, 4.8, 8.9, 9.1};
  s21::list<std::string> s21_list_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_list_int.size(), 4U);
  EXPECT_EQ(s21_list_int.front(), 1);

  EXPECT_EQ(s21_list_double.size(), 4U);
  EXPECT_EQ(s21_list_double.front(), 1.4);

  EXPECT_EQ(s21_list_string.size(), 4U);
  EXPECT_EQ(s21_list_string.front(), "Hello");
}

TEST(LIST, case5) {
  s21::list<int> s21_list_ref_int{1, 4, 8, 9};
  s21::list<int> s21_list_res_int(s21_list_ref_int);

  s21::list<double> s21_list_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::list<double> s21_list_res_double(s21_list_ref_double);

  s21::list<std::string> s21_list_ref_string{"Hello", ",", "world", "!"};
  s21::list<std::string> s21_list_res_string(s21_list_ref_string);

  EXPECT_EQ(s21_list_res_int.size(), 4U);
  EXPECT_EQ(s21_list_res_int.front(), 1);

  EXPECT_EQ(s21_list_res_double.size(), 4U);
  EXPECT_EQ(s21_list_res_double.front(), 1.4);

  EXPECT_EQ(s21_list_res_string.size(), 4U);
  EXPECT_EQ(s21_list_res_string.front(), "Hello");
}

TEST(LIST, case6) {
  s21::list<int> s21_list_ref_int{1, 4, 8, 9};
  s21::list<int> s21_list_res_int = s21_list_ref_int;

  s21::list<double> s21_list_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::list<double> s21_list_res_double = s21_list_ref_double;

  s21::list<std::string> s21_list_ref_string{"Hello", ",", "world", "!"};
  s21::list<std::string> s21_list_res_string = s21_list_ref_string;

  EXPECT_EQ(s21_list_res_int.size(), 4U);
  EXPECT_EQ(s21_list_res_int.front(), 1);

  EXPECT_EQ(s21_list_res_double.size(), 4U);
  EXPECT_EQ(s21_list_res_double.front(), 1.4);

  EXPECT_EQ(s21_list_res_string.size(), 4U);
  EXPECT_EQ(s21_list_res_string.front(), "Hello");
}

TEST(LIST, case7) {
  s21::list<int> s21_list_ref_int;
  s21::list<int> s21_list_res_int = s21_list_ref_int;

  s21::list<double> s21_list_ref_double;
  s21::list<double> s21_list_res_double = s21_list_ref_double;

  s21::list<std::string> s21_list_ref_string;
  s21::list<std::string> s21_list_res_string = s21_list_ref_string;

  EXPECT_EQ(s21_list_res_int.size(), 0U);
  EXPECT_EQ(s21_list_res_double.size(), 0U);
  EXPECT_EQ(s21_list_res_string.size(), 0U);
}

TEST(LIST, case8) {
  s21::list<int> s21_list_ref_int{1, 4, 8, 9};
  s21::list<int> s21_list_res_int = std::move(s21_list_ref_int);

  s21::list<double> s21_list_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::list<double> s21_list_res_double = std::move(s21_list_ref_double);

  s21::list<std::string> s21_list_ref_string{"Hello", ",", "world", "!"};
  s21::list<std::string> s21_list_res_string = std::move(s21_list_ref_string);

  EXPECT_EQ(s21_list_ref_int.size(), 0U);
  EXPECT_EQ(s21_list_res_int.size(), 4U);
  EXPECT_EQ(s21_list_res_int.front(), 1);

  EXPECT_EQ(s21_list_ref_double.size(), 0U);
  EXPECT_EQ(s21_list_res_double.size(), 4U);
  EXPECT_EQ(s21_list_res_double.front(), 1.4);

  EXPECT_EQ(s21_list_ref_string.size(), 0U);
  EXPECT_EQ(s21_list_res_string.size(), 4U);
  EXPECT_EQ(s21_list_res_string.front(), "Hello");
}

TEST(LIST, case9) {
  s21::list<int> s21_list_ref_int{1, 4, 8, 9};
  s21::list<int> s21_list_res_int;
  s21_list_res_int = std::move(s21_list_ref_int);

  s21::list<double> s21_list_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::list<double> s21_list_res_double;
  s21_list_res_double = std::move(s21_list_ref_double);

  s21::list<std::string> s21_list_ref_string{"Hello", ",", "world", "!"};
  s21::list<std::string> s21_list_res_string;
  s21_list_res_string = std::move(s21_list_ref_string);

  EXPECT_EQ(s21_list_ref_int.size(), 0U);
  EXPECT_EQ(s21_list_res_int.size(), 4U);
  EXPECT_EQ(s21_list_res_int.front(), 1);

  EXPECT_EQ(s21_list_ref_double.size(), 0U);
  EXPECT_EQ(s21_list_res_double.size(), 4U);
  EXPECT_EQ(s21_list_res_double.front(), 1.4);

  EXPECT_EQ(s21_list_ref_string.size(), 0U);
  EXPECT_EQ(s21_list_res_string.size(), 4U);
  EXPECT_EQ(s21_list_res_string.front(), "Hello");
}

TEST(LIST, case10) {
  s21::list<int> a = {43, 43, 43, 5};
  s21::list<int> b = {2};
  a = std::move(b);
  EXPECT_EQ(a.back(), 2);
}

TEST(LIST, case11) {
  size_t n = 1e4;
  s21::list<int> lst(n);
  EXPECT_EQ(lst.size(), n);
  EXPECT_TRUE(lst.max_size() != 0);
  lst.pop_back();
  lst.pop_front();
  EXPECT_EQ(lst.size(), (n - 2));
  int back = lst.back();
  int front = lst.front();
  EXPECT_EQ(back, 0);
  EXPECT_EQ(front, 0);
}

TEST(LIST, case12) {
  s21::list<double> lst = {1.032, 2.320,    3.0,   4.0,   5.0,
                           6.0,   7.000043, 8.324, 9.343, 10.0};
  EXPECT_EQ(lst.size(), 10U);
  double front = lst.front();
  EXPECT_DOUBLE_EQ(front, 1.032);
  lst.pop_front();
  double new_front = lst.front();
  EXPECT_DOUBLE_EQ(new_front, 2.320);

  lst.pop_back();
  double back = lst.back();
  EXPECT_DOUBLE_EQ(back, 9.343);

  EXPECT_EQ(lst.size(), 8U);
  lst.clear();
  EXPECT_EQ(lst.size(), 0U);
}

TEST(LIST, case13) {
  s21::list<double> lst = {1.032, 2.32,     3.0,   4.0,   5.0,
                           6.0,   7.000043, 8.324, 9.343, 10.0};
  s21::list<double> lst_cpy(lst);
  EXPECT_EQ(lst_cpy.size(), 10U);
  double front = lst_cpy.front();
  EXPECT_DOUBLE_EQ(front, 1.032);
  lst_cpy.pop_front();
  double new_front = lst_cpy.front();
  EXPECT_DOUBLE_EQ(new_front, 2.320);
  double back = lst_cpy.back();
  EXPECT_DOUBLE_EQ(back, 10.0);
  lst_cpy.pop_back();
  back = lst_cpy.back();
  EXPECT_DOUBLE_EQ(back, 9.343);
  EXPECT_EQ(lst_cpy.size(), 8U);
}

TEST(LIST, case14) {
  s21::list<double> lst = {1.032, 2.32,     3.0,   4.0,   5.0,
                           6.0,   7.000043, 8.324, 9.343, 10.0};
  s21::list<double> lst_cpy(std::move(lst));
  EXPECT_EQ(lst_cpy.size(), 10U);
  double front = lst_cpy.front();
  EXPECT_DOUBLE_EQ(front, 1.032);
  lst_cpy.pop_front();
  double new_front = lst_cpy.front();
  EXPECT_DOUBLE_EQ(new_front, 2.320);
  double back = lst_cpy.back();
  EXPECT_DOUBLE_EQ(back, 10.0);
  lst_cpy.pop_back();
  back = lst_cpy.back();
  EXPECT_DOUBLE_EQ(back, 9.343);
  EXPECT_EQ(lst_cpy.size(), 8U);
  EXPECT_EQ(lst.size(), 0U);
}

TEST(LIST, case15) {
  std::list<int> orig_list = {};
  s21::list<int> lst = {};
  auto orig_itr_end = orig_list.end();
  auto itr_end = lst.end();
  EXPECT_EQ(*orig_itr_end, *itr_end);
}

TEST(LIST, case16) {
  std::list<int> orig_list;
  s21::list<int> lst;
  auto orig_itr = orig_list.end();
  auto itr = lst.end();
  EXPECT_EQ(*orig_itr, *itr);
}

TEST(LIST, CopyAssignmentOperator_case1) {
  // Тестируем для int
  s21::list<int> s21_list_ref_int{1, 4, 8, 9};
  s21::list<int> s21_list_res_int;
  s21_list_res_int = s21_list_ref_int;

  EXPECT_EQ(s21_list_res_int.size(), 4U);
  EXPECT_EQ(s21_list_res_int.front(), 1);
  EXPECT_EQ(s21_list_res_int.back(), 9);

  auto it_ref_int = s21_list_ref_int.begin();
  auto it_res_int = s21_list_res_int.begin();
  while (it_ref_int != s21_list_ref_int.end() &&
         it_res_int != s21_list_res_int.end()) {
    EXPECT_EQ(*it_ref_int, *it_res_int);
    ++it_ref_int;
    ++it_res_int;
  }
}

TEST(LIST, LIST_CopyAssignmentOperator_case2_Test) {
  // Тестируем для int
  s21::list<int> s21_list_ref_int{1, 4, 8, 9};
  s21::list<int> s21_list_res_int{2, 5, 6, 7};
  s21_list_res_int = s21_list_ref_int;

  EXPECT_EQ(s21_list_res_int.size(), 4U);
  EXPECT_EQ(s21_list_res_int.front(), 1);
  EXPECT_EQ(s21_list_res_int.back(), 9);

  auto it_ref_int = s21_list_ref_int.begin();
  auto it_res_int = s21_list_res_int.begin();
  while (it_ref_int != s21_list_ref_int.end() &&
         it_res_int != s21_list_res_int.end()) {
    EXPECT_EQ(*it_ref_int, *it_res_int);
    ++it_ref_int;
    ++it_res_int;
  }
}
TEST(LIST_PUSH_FRONT, case1) {
  s21::list<int> s21_list_int{1, 4, 8, 9};
  s21::list<double> s21_list_double{1.4, 4.8, 8.9, 9.1};
  s21::list<std::string> s21_list_string{"Hello", ",", "world", "!"};

  s21_list_int.push_front(33);
  s21_list_double.push_front(33.0);
  s21_list_string.push_front("33");

  EXPECT_EQ(s21_list_int.size(), 5U);
  EXPECT_EQ(s21_list_int.front(), 33);

  EXPECT_EQ(s21_list_double.size(), 5U);
  EXPECT_EQ(s21_list_double.front(), 33.0);

  EXPECT_EQ(s21_list_string.size(), 5U);
  EXPECT_EQ(s21_list_string.front(), "33");
}

TEST(LIST_PUSH_FRONT, case2) {
  s21::list<int> s21_list_int;
  s21::list<double> s21_list_double;
  s21::list<std::string> s21_list_string;

  s21_list_int.push_front(33);
  s21_list_double.push_front(33.0);
  s21_list_string.push_front("33");

  EXPECT_EQ(s21_list_int.size(), 1U);
  EXPECT_EQ(s21_list_int.front(), 33);

  EXPECT_EQ(s21_list_double.size(), 1U);
  EXPECT_EQ(s21_list_double.front(), 33.0);

  EXPECT_EQ(s21_list_string.size(), 1U);
  EXPECT_EQ(s21_list_string.front(), "33");
}

TEST(LIST_PUSH_FRONT, case3) {
  s21::list<int> s21_list_int{1};
  s21::list<double> s21_list_double{1.0};
  s21::list<std::string> s21_list_string{"1"};

  s21_list_int.push_front(33);
  s21_list_double.push_front(33.0);
  s21_list_string.push_front("33");

  EXPECT_EQ(s21_list_int.size(), 2U);
  EXPECT_EQ(s21_list_int.front(), 33);

  EXPECT_EQ(s21_list_double.size(), 2U);
  EXPECT_EQ(s21_list_double.front(), 33.0);

  EXPECT_EQ(s21_list_string.size(), 2U);
  EXPECT_EQ(s21_list_string.front(), "33");
}

TEST(LIST_PUSH_FRONT, case4) {
  s21::list<int> lol = {1, 2, 10, 3, 4, 6, 43};
  std::list<int> lol_orig = {1, 2, 10, 3, 4, 6, 43};
  lol.push_front(21);
  lol_orig.push_front(21);
  auto itr_orig = lol_orig.begin();
  for (auto itr = lol.begin(); itr != lol.end(); ++itr) {
    EXPECT_EQ(*itr, *itr_orig);
    itr_orig++;
  }

  s21::list<int> lol1;
  std::list<int> lol_orig1;
  lol1.push_front(21);
  lol_orig1.push_front(21);
  auto itr_orig1 = lol_orig1.begin();
  for (auto itr1 = lol1.begin(); itr1 != lol1.end(); ++itr1) {
    EXPECT_EQ(*itr1, *itr_orig1);
    itr_orig1++;
  }
}

TEST(LIST_PUSH_BACK, case1) {
  s21::list<int> s21_list_int{1, 4, 8, 9};
  s21::list<double> s21_list_double{1.4, 4.8, 8.9, 9.1};
  s21::list<std::string> s21_list_string{"Hello", ",", "world", "!"};

  s21_list_int.push_back(33);
  s21_list_double.push_back(33.0);
  s21_list_string.push_back("33");

  EXPECT_EQ(s21_list_int.size(), 5U);
  EXPECT_EQ(s21_list_int.back(), 33);

  EXPECT_EQ(s21_list_double.size(), 5U);
  EXPECT_EQ(s21_list_double.back(), 33.0);

  EXPECT_EQ(s21_list_string.size(), 5U);
  EXPECT_EQ(s21_list_string.back(), "33");
}

TEST(LIST_PUSH_BACK, case2) {
  s21::list<int> s21_list_int;
  s21::list<double> s21_list_double;
  s21::list<std::string> s21_list_string;

  s21_list_int.push_back(33);
  s21_list_double.push_back(33.0);
  s21_list_string.push_back("33");

  EXPECT_EQ(s21_list_int.size(), 1U);
  EXPECT_EQ(s21_list_int.back(), 33);

  EXPECT_EQ(s21_list_double.size(), 1U);
  EXPECT_EQ(s21_list_double.back(), 33.0);

  EXPECT_EQ(s21_list_string.size(), 1U);
  EXPECT_EQ(s21_list_string.back(), "33");
}

TEST(LIST_PUSH_BACK, case3) {
  s21::list<int> s21_list_int{1};
  s21::list<double> s21_list_double{1.0};
  s21::list<std::string> s21_list_string{"1"};

  s21_list_int.push_back(33);
  s21_list_double.push_back(33.0);
  s21_list_string.push_back("33");

  EXPECT_EQ(s21_list_int.size(), 2U);
  EXPECT_EQ(s21_list_int.back(), 33);

  EXPECT_EQ(s21_list_double.size(), 2U);
  EXPECT_EQ(s21_list_double.back(), 33.0);

  EXPECT_EQ(s21_list_string.size(), 2U);
  EXPECT_EQ(s21_list_string.back(), "33");
}

TEST(LIST_POP_FRONT, case1) {
  s21::list<int> s21_list_int{1, 4, 8, 9};
  s21::list<double> s21_list_double{1.4, 4.8, 8.9, 9.1};
  s21::list<std::string> s21_list_string{"Hello", ",", "world", "!"};

  s21_list_int.pop_front();
  s21_list_double.pop_front();
  s21_list_string.pop_front();

  EXPECT_EQ(s21_list_int.size(), 3U);
  EXPECT_EQ(s21_list_int.front(), 4);

  EXPECT_EQ(s21_list_double.size(), 3U);
  EXPECT_EQ(s21_list_double.front(), 4.8);

  EXPECT_EQ(s21_list_string.size(), 3U);
  EXPECT_EQ(s21_list_string.front(), ",");
}

TEST(LIST_POP_FRONT, case2) {
  s21::list<int> s21_list_int{1};
  s21::list<double> s21_list_double{1.0};
  s21::list<std::string> s21_list_string{"1"};

  s21_list_int.pop_front();
  s21_list_double.pop_front();
  s21_list_string.pop_front();

  EXPECT_EQ(s21_list_int.size(), 0U);
  EXPECT_EQ(s21_list_double.size(), 0U);
  EXPECT_EQ(s21_list_string.size(), 0U);
}

TEST(LIST_POP_FRONT, case3) {
  s21::list<int> lol = {1, 2, 10, 3, 4, 6, 43};
  std::list<int> lol_orig = {1, 2, 10, 3, 4, 6, 43};
  lol.pop_front();
  lol_orig.pop_front();
  auto itr_orig = lol_orig.begin();
  for (auto itr = lol.begin(); itr != lol.end(); ++itr) {
    EXPECT_EQ(*itr, *itr_orig);
    itr_orig++;
  }
}

TEST(LIST_POP_BACK, case1) {
  s21::list<int> s21_list_int{1, 4, 8, 9};
  s21::list<double> s21_list_double{1.4, 4.8, 8.9, 9.1};
  s21::list<std::string> s21_list_string{"Hello", ",", "world", "!"};

  s21_list_int.pop_back();
  s21_list_double.pop_back();
  s21_list_string.pop_back();

  EXPECT_EQ(s21_list_int.size(), 3U);
  EXPECT_EQ(s21_list_int.back(), 8);

  EXPECT_EQ(s21_list_double.size(), 3U);
  EXPECT_EQ(s21_list_double.back(), 8.9);

  EXPECT_EQ(s21_list_string.size(), 3U);
  EXPECT_EQ(s21_list_string.back(), "world");
}

TEST(LIST_POP_BACK, case2) {
  s21::list<int> s21_list_int{1, 2};
  s21::list<double> s21_list_double{1.0, 2.0};
  s21::list<std::string> s21_list_string{"1", "2"};

  s21_list_int.pop_back();
  s21_list_double.pop_back();
  s21_list_string.pop_back();

  EXPECT_EQ(s21_list_int.size(), 1U);
  EXPECT_EQ(s21_list_double.size(), 1U);
  EXPECT_EQ(s21_list_string.size(), 1U);
}

TEST(LIST_FRONT, case1) {
  s21::list<int> s21_list_int{1, 4, 8, 9};
  s21::list<double> s21_list_double{1.4, 4.8, 8.9, 9.1};
  s21::list<std::string> s21_list_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_list_int.front(), 1);
  EXPECT_EQ(s21_list_double.front(), 1.4);
  EXPECT_EQ(s21_list_string.front(), "Hello");
}

TEST(LIST_FRONT, case2) {
  s21::list<char> lol = {'l', 'o', 'l'};
  std::list<char> lol_orig = {'l', 'o', 'l'};
  EXPECT_EQ(lol.front(), lol_orig.front());
}

TEST(back, case1) {
  s21::list<int> s21_list_int{1, 4, 8, 9};
  s21::list<double> s21_list_double{1.4, 4.8, 8.9, 9.1};
  s21::list<std::string> s21_list_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_list_int.back(), 9);
  EXPECT_EQ(s21_list_double.back(), 9.1);
  EXPECT_EQ(s21_list_string.back(), "!");
}

TEST(swap, case1) {
  s21::list<int> s21_list_ref_int{1, 4, 8, 9};
  s21::list<int> s21_list_res_int{12, 13};

  s21::list<double> s21_list_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::list<double> s21_list_res_double{11.0, 12.0, 13.0};

  s21::list<std::string> s21_list_ref_string{"Hello", ",", "world", "!"};
  s21::list<std::string> s21_list_res_string{"12", "13", "14", "15"};

  s21_list_ref_int.swap(s21_list_res_int);
  s21_list_ref_double.swap(s21_list_res_double);
  s21_list_ref_string.swap(s21_list_res_string);

  EXPECT_EQ(s21_list_ref_int.size(), 2U);
  EXPECT_EQ(s21_list_ref_int.front(), 12);
  EXPECT_EQ(s21_list_res_int.size(), 4U);
  EXPECT_EQ(s21_list_res_int.front(), 1);

  EXPECT_EQ(s21_list_ref_double.size(), 3U);
  EXPECT_EQ(s21_list_ref_double.front(), 11.0);
  EXPECT_EQ(s21_list_res_double.size(), 4U);
  EXPECT_EQ(s21_list_res_double.front(), 1.4);

  EXPECT_EQ(s21_list_ref_string.size(), 4U);
  EXPECT_EQ(s21_list_ref_string.front(), "12");
  EXPECT_EQ(s21_list_res_string.size(), 4U);
  EXPECT_EQ(s21_list_res_string.front(), "Hello");
}

TEST(swap, case2) {
  s21::list<int> s21_list_ref_int{1, 4, 8, 9};
  s21::list<int> s21_list_res_int;

  s21::list<double> s21_list_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::list<double> s21_list_res_double;

  s21::list<std::string> s21_list_ref_string{"Hello", ",", "world", "!"};
  s21::list<std::string> s21_list_res_string;

  s21_list_ref_int.swap(s21_list_res_int);
  s21_list_ref_double.swap(s21_list_res_double);
  s21_list_ref_string.swap(s21_list_res_string);

  EXPECT_EQ(s21_list_ref_int.size(), 0U);
  EXPECT_EQ(s21_list_res_int.size(), 4U);
  EXPECT_EQ(s21_list_res_int.front(), 1);

  EXPECT_EQ(s21_list_ref_double.size(), 0U);
  EXPECT_EQ(s21_list_res_double.size(), 4U);
  EXPECT_EQ(s21_list_res_double.front(), 1.4);

  EXPECT_EQ(s21_list_ref_string.size(), 0U);
  EXPECT_EQ(s21_list_res_string.size(), 4U);
  EXPECT_EQ(s21_list_res_string.front(), "Hello");
}

TEST(sort, case1) {
  s21::list<int> s21_list_int{8, 1, 4, 9};
  s21::list<double> s21_list_double{9.1, 1.4, 4.8, 8.9};
  s21::list<std::string> s21_list_string{"hello", "there", "21", "school"};

  s21_list_int.sort();
  s21_list_double.sort();
  s21_list_string.sort();

  EXPECT_EQ(s21_list_int.front(), 1);
  EXPECT_EQ(s21_list_double.front(), 1.4);
  EXPECT_EQ(s21_list_string.front(), "21");
}

TEST(sort, case2) {
  s21::list<int> s21_list_int{8};
  s21::list<double> s21_list_double{9.1};
  s21::list<std::string> s21_list_string{"hello"};

  s21_list_int.sort();
  s21_list_double.sort();
  s21_list_string.sort();

  EXPECT_EQ(s21_list_int.front(), 8);
  EXPECT_EQ(s21_list_double.front(), 9.1);
  EXPECT_EQ(s21_list_string.front(), "hello");
}

TEST(merge, case1) {
  s21::list<int> s21_list_ref_int{1, 4, 8, 9};
  s21::list<int> s21_list_res_int{12, 13};

  s21::list<double> s21_list_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::list<double> s21_list_res_double{11.0, 12.0, 13.0};

  s21::list<std::string> s21_list_ref_string{"Hello", ",", "world", "!"};
  s21::list<std::string> s21_list_res_string{"12", "13", "14", "15"};

  s21_list_res_int.merge(s21_list_ref_int);
  s21_list_res_double.merge(s21_list_ref_double);
  s21_list_res_string.merge(s21_list_ref_string);

  EXPECT_EQ(s21_list_ref_int.size(), 0U);
  EXPECT_EQ(s21_list_res_int.size(), 6U);
  EXPECT_EQ(s21_list_res_int.front(), 1);

  EXPECT_EQ(s21_list_ref_double.size(), 0U);
  EXPECT_EQ(s21_list_res_double.size(), 7U);
  EXPECT_EQ(s21_list_res_double.front(), 1.4);

  EXPECT_EQ(s21_list_ref_string.size(), 0U);
  EXPECT_EQ(s21_list_res_string.size(), 8U);
  EXPECT_EQ(s21_list_res_string.front(), "12");
}

TEST(merge, case2) {
  s21::list<int> s21_list_ref_int{1, 4, 8, 9};
  s21::list<int> s21_list_res_int;

  s21::list<double> s21_list_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::list<double> s21_list_res_double;

  s21::list<std::string> s21_list_ref_string{"Hello", ",", "world", "!"};
  s21::list<std::string> s21_list_res_string;

  s21_list_res_int.merge(s21_list_ref_int);
  s21_list_res_double.merge(s21_list_ref_double);
  s21_list_res_string.merge(s21_list_ref_string);

  EXPECT_EQ(s21_list_ref_int.size(), 0U);
  EXPECT_EQ(s21_list_res_int.size(), 4U);
  EXPECT_EQ(s21_list_res_int.front(), 1);

  EXPECT_EQ(s21_list_ref_double.size(), 0U);
  EXPECT_EQ(s21_list_res_double.size(), 4U);
  EXPECT_EQ(s21_list_res_double.front(), 1.4);

  EXPECT_EQ(s21_list_ref_string.size(), 0U);
  EXPECT_EQ(s21_list_res_string.size(), 4U);
  EXPECT_EQ(s21_list_res_string.front(), "Hello");
}

TEST(merge, case3) {
  s21::list<int> lol = {1, 2, 10, 3, 4, 6, 43};
  std::list<int> lol_orig = {1, 2, 10, 3, 4, 6, 43};
  s21::list<int> list_merge = {2, 5, 7, 9};
  std::list<int> list_merge_orig = {2, 5, 7, 9};
  lol.sort();
  lol_orig.sort();
  lol.merge(list_merge);
  lol_orig.merge(list_merge_orig);
  auto itr_orig = lol_orig.begin();
  for (auto itr = lol.begin(); itr != lol.end(); ++itr) {
    EXPECT_EQ(*itr, *itr_orig);
    itr_orig++;
  }
}

TEST(reverse, case1) {
  s21::list<int> s21_list_int{1, 4, 8, 9};
  s21::list<double> s21_list_double{1.4, 4.8, 8.9, 9.1};
  s21::list<std::string> s21_list_string{"Hello", ",", "world", "!"};

  s21_list_int.reverse();
  s21_list_double.reverse();
  s21_list_string.reverse();

  EXPECT_EQ(s21_list_int.front(), 9);
  EXPECT_EQ(s21_list_double.front(), 9.1);
  EXPECT_EQ(s21_list_string.front(), "!");
}

TEST(reverse, case2) {
  s21::list<int> s21_list_int{1};
  s21::list<double> s21_list_double{1.4};
  s21::list<std::string> s21_list_string{"Hello"};

  s21_list_int.reverse();
  s21_list_double.reverse();
  s21_list_string.reverse();

  EXPECT_EQ(s21_list_int.front(), 1);
  EXPECT_EQ(s21_list_double.front(), 1.4);
  EXPECT_EQ(s21_list_string.front(), "Hello");
}

TEST(unique, case1) {
  s21::list<int> s21_list_int{1, 1, 4, 4, 8, 8, 8, 9, 9, 9, 9, 9};
  s21::list<double> s21_list_double{1.4, 4.8, 1.4, 4.8, 8.9, 9.1,
                                    1.4, 4.8, 8.9, 8.9, 9.1};
  s21::list<std::string> s21_list_string{"Hello", ",",     "Hello", ",",
                                         "world", ",",     "world", "!",
                                         "!",     "world", "!"};

  s21_list_int.unique();
  s21_list_double.unique();
  s21_list_string.unique();

  EXPECT_EQ(s21_list_int.size(), 4U);
  EXPECT_EQ(s21_list_double.size(), 10U);
  EXPECT_EQ(s21_list_string.size(), 10U);
}

TEST(unique, case2) {
  s21::list<int> s21_list_int{1, 4, 8, 9};
  s21::list<double> s21_list_double{1.4, 4.8, 8.9, 9.1};
  s21::list<std::string> s21_list_string{"Hello", ",", "world", "!"};

  s21_list_int.unique();
  s21_list_double.unique();
  s21_list_string.unique();

  EXPECT_EQ(s21_list_int.size(), 4U);
  EXPECT_EQ(s21_list_double.size(), 4U);
  EXPECT_EQ(s21_list_string.size(), 4U);
}

TEST(unique, case3) {
  s21::list<int> s21_list_int;
  s21::list<double> s21_list_double;
  s21::list<std::string> s21_list_string;

  s21_list_int.unique();
  s21_list_double.unique();
  s21_list_string.unique();

  EXPECT_EQ(s21_list_int.size(), 0U);
  EXPECT_EQ(s21_list_double.size(), 0U);
  EXPECT_EQ(s21_list_string.size(), 0U);
}

TEST(size, case1) {
  s21::list<int> s21_list_int{1, 4, 8, 9};
  s21::list<double> s21_list_double{1.4, 4.8, 8.9, 9.1};
  s21::list<std::string> s21_list_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_list_int.size(), 4U);
  EXPECT_EQ(s21_list_double.size(), 4U);
  EXPECT_EQ(s21_list_string.size(), 4U);
}

TEST(size, case2) {
  s21::list<int> s21_list_int;
  s21::list<double> s21_list_double;
  s21::list<std::string> s21_list_string;

  EXPECT_EQ(s21_list_int.size(), 0U);
  EXPECT_EQ(s21_list_double.size(), 0U);
  EXPECT_EQ(s21_list_string.size(), 0U);
}

TEST(max_size, case1) {
  s21::list<int> s21_list_int{1, 4, 8, 9};
  std::list<int> std_list_int{1, 4, 8, 9};

  s21::list<double> s21_list_double{1.4, 4.8, 8.9, 9.1};
  std::list<double> std_list_double{1.4, 4.8, 8.9, 9.1};

  s21::list<std::string> s21_list_string{"Hello", ",", "world", "!"};
  std::list<std::string> std_list_string{"Hello", ",", "world", "!"};

  EXPECT_TRUE(s21_list_int.max_size() &&
              (std_list_int.max_size() || 384307168202282325U));
  EXPECT_TRUE(s21_list_double.max_size() &&
              (std_list_double.max_size() || 384307168202282325U));
  EXPECT_TRUE(s21_list_string.max_size() &&
              (std_list_string.max_size() || 192153584101141162U));
}

TEST(LIST_EMPTY, case1) {
  s21::list<int> s21_list_int{1, 4, 8, 9};
  s21::list<double> s21_list_double{1.4, 4.8, 8.9, 9.1};
  s21::list<std::string> s21_list_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_list_int.empty(), 0);
  EXPECT_EQ(s21_list_double.empty(), 0);
  EXPECT_EQ(s21_list_double.empty(), 0);
}

TEST(LIST_EMPTY, case2) {
  s21::list<int> s21_list_int;
  s21::list<double> s21_list_double;
  s21::list<std::string> s21_list_string;

  EXPECT_EQ(s21_list_int.empty(), 1);
  EXPECT_EQ(s21_list_double.empty(), 1);
  EXPECT_EQ(s21_list_double.empty(), 1);
}

TEST(LIST_EMPTY, case3) {
  s21::list<int> lol;
  std::list<int> lol_orig;
  EXPECT_EQ(lol.front(), lol_orig.front());
}

TEST(LIST_EMPTY, case4) {
  s21::list<int> lol;
  std::list<int> lol_orig;
  EXPECT_EQ(lol.back(), lol_orig.back());
}

TEST(LIST_INSERT, case1) {
  s21::list<int> s21_list_int{1, 4, 8, 9};
  s21::list<double> s21_list_double{1.4, 4.8, 8.9, 9.1};
  s21::list<std::string> s21_list_string{"Hello", ",", "world", "!"};

  auto it_int = s21_list_int.begin();
  it_int = s21_list_int.insert(it_int, 13);
  ++it_int;
  ++it_int;
  it_int = s21_list_int.insert(it_int, 13);
  EXPECT_EQ(s21_list_int.front(), 13);
  EXPECT_EQ(*(++(++s21_list_int.begin())), 13);

  auto it_double = s21_list_double.begin();
  it_double = s21_list_double.insert(it_double, 21.0);
  ++it_double;
  ++it_double;
  it_double = s21_list_double.insert(it_double, 21.0);
  EXPECT_EQ(s21_list_double.front(), 21.0);
  EXPECT_EQ(*(++(++s21_list_double.begin())), 21.0);

  auto it_string = s21_list_string.begin();
  it_string = s21_list_string.insert(it_string, "HI");
  ++it_string;
  ++it_string;
  it_string = s21_list_string.insert(it_string, "HI");
  EXPECT_EQ(s21_list_string.front(), "HI");
  EXPECT_EQ(*(++(++s21_list_string.begin())), "HI");
}

TEST(LIST_INSERT, case2) {
  s21::list<int> s21_list_int;
  s21::list<double> s21_list_double;
  s21::list<std::string> s21_list_string;

  auto it_int = s21_list_int.begin();
  it_int = s21_list_int.insert(it_int, 13);
  EXPECT_EQ(s21_list_int.front(), 13);

  auto it_double = s21_list_double.begin();
  it_double = s21_list_double.insert(it_double, 21.0);
  EXPECT_EQ(s21_list_double.front(), 21.0);

  auto it_string = s21_list_string.begin();
  it_string = s21_list_string.insert(it_string, "HI");
  EXPECT_EQ(s21_list_string.front(), "HI");
}

TEST(LIST_INSERT, case3) {
  s21::list<int> s21_list_int{1};
  s21::list<double> s21_list_double{1.0};
  s21::list<std::string> s21_list_string{"1"};

  auto it_int = s21_list_int.begin();
  it_int = s21_list_int.insert(it_int, 13);
  EXPECT_EQ(s21_list_int.front(), 13);

  auto it_double = s21_list_double.begin();
  it_double = s21_list_double.insert(it_double, 21.0);
  EXPECT_EQ(s21_list_double.front(), 21.0);

  auto it_string = s21_list_string.begin();
  it_string = s21_list_string.insert(it_string, "HI");
  EXPECT_EQ(s21_list_string.front(), "HI");
}

TEST(LIST_INSERT, case4) {
  s21::list<int> lol;
  std::list<int> lol_orig;
  auto itr = lol.begin();
  auto itr_orig = lol_orig.begin();
  itr = lol.insert(itr, 21);
  itr_orig = lol_orig.insert(itr_orig, 21);
  EXPECT_EQ(*itr, *itr_orig);

  s21::list<int> lol1 = {1, 2, 3, 4, 6, 43};
  std::list<int> lol_orig1 = {1, 2, 3, 4, 6, 43};
  auto itr1 = lol1.begin();
  auto itr_orig1 = lol_orig1.begin();
  itr1 = lol1.insert(itr1, 21);
  itr_orig1 = lol_orig1.insert(itr_orig1, 21);
  auto end1 = lol1.end();
  auto end_orig1 = lol_orig1.end();
  while (itr1 != end1 && itr_orig1 != end_orig1) {
    EXPECT_EQ(*itr1, *itr_orig1);
    ++itr1;
    itr_orig1++;
  }

  s21::list<int> lol2 = {1, 2, 3, 4, 6, 44};
  std::list<int> lol_orig2 = {1, 2, 3, 4, 6, 44};
  auto itr2 = lol2.end();
  auto itr_orig2 = lol_orig2.end();
  itr2 = lol2.insert(itr2, 21);
  itr_orig2 = lol_orig2.insert(itr_orig2, 21);
  while (itr2 != lol2.begin() && itr_orig2 != lol_orig2.begin()) {
    EXPECT_EQ(*itr2, *itr_orig2);
    --itr2;
    --itr_orig2;
  }
}

TEST(LIST_SPLICE, case1) {
  s21::list<int> s21_list_ref_int{3, 5};
  s21::list<int> s21_list_res_int{1, 4, 8, 9};

  s21::list<double> s21_list_ref_double{5.6, 7.1};
  s21::list<double> s21_list_res_double{1.4, 4.8, 8.9, 9.1};

  s21::list<std::string> s21_list_ref_string{"Hi"};
  s21::list<std::string> s21_list_res_string{"Hello", ",", "world", "!"};

  auto it_int = s21_list_res_int.cbegin();

  s21_list_res_int.splice(it_int, s21_list_ref_int);
  EXPECT_EQ(*(s21_list_res_int.begin()), 3);
  EXPECT_EQ(*(++s21_list_res_int.begin()), 5);

  auto it_double = s21_list_res_double.cbegin();
  s21_list_res_double.splice(it_double, s21_list_ref_double);
  EXPECT_EQ(*(s21_list_res_double.begin()), 5.6);
  EXPECT_EQ(*(++s21_list_res_double.begin()), 7.1);

  auto it_string = s21_list_res_string.cbegin();
  s21_list_res_string.splice(it_string, s21_list_ref_string);
  EXPECT_EQ(*(s21_list_res_string.begin()), "Hi");
}

TEST(LIST_SPLICE, case2) {
  s21::list<int> s21_list_ref_int;
  s21::list<int> s21_list_res_int{1, 4, 8, 9};

  s21::list<double> s21_list_ref_double;
  s21::list<double> s21_list_res_double{1.4, 4.8, 8.9, 9.1};

  s21::list<std::string> s21_list_ref_string;
  s21::list<std::string> s21_list_res_string{"Hello", ",", "world", "!"};

  auto it_int = s21_list_res_int.cbegin();
  s21_list_res_int.splice(it_int, s21_list_ref_int);
  EXPECT_EQ(*(s21_list_res_int.begin()), 1);

  auto it_double = s21_list_res_double.cbegin();
  s21_list_res_double.splice(it_double, s21_list_ref_double);
  EXPECT_EQ(*(s21_list_res_double.begin()), 1.4);

  auto it_string = s21_list_res_string.cbegin();
  s21_list_res_string.splice(it_string, s21_list_ref_string);
  EXPECT_EQ(*(s21_list_res_string.begin()), "Hello");
}
TEST(LIST_SPLICE, case3) {
  s21::list<int> s21_list_ref_int{1, 4, 8, 9};
  s21::list<int> s21_list_res_int;

  s21::list<double> s21_list_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::list<double> s21_list_res_double;

  s21::list<std::string> s21_list_ref_string{"Hello", ",", "world", "!"};
  s21::list<std::string> s21_list_res_string;

  auto it_int = s21_list_res_int.cbegin();
  s21_list_res_int.splice(it_int, s21_list_ref_int);
  EXPECT_EQ(*(s21_list_res_int.begin()), 1);

  auto it_double = s21_list_res_double.cbegin();
  s21_list_res_double.splice(it_double, s21_list_ref_double);
  EXPECT_EQ(*(s21_list_res_double.begin()), 1.4);

  auto it_string = s21_list_res_string.cbegin();
  s21_list_res_string.splice(it_string, s21_list_ref_string);
  EXPECT_EQ(*(s21_list_res_string.begin()), "Hello");
}

TEST(List, Erase) {
  s21::list<int> our_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  our_list.erase(our_list.begin());
  std_list.erase(std_list.begin());
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(List, Insert_Many_case1) {
  s21::list<int> our_list = {1, 2, 3, 4, 5};
  s21::list<int>::iterator our_it = our_list.begin();
  ++our_it;
  our_list.insert_many(our_it, 7, 8, 9);
  our_it = our_list.begin();
  EXPECT_EQ(*our_it, 1);
  ++our_it;
  EXPECT_EQ(*our_it, 7);
  ++our_it;
  EXPECT_EQ(*our_it, 8);
  ++our_it;
  EXPECT_EQ(*our_it, 9);
  ++our_it;
  EXPECT_EQ(*our_it, 2);
}

TEST(list, insert_Many_case2) {
  s21::list<int> s21_list = {1};
  std::list<int> std_list{-1, -23, 4, 1, 5, 6, 4, -1, -1, 1};

  s21_list.insert_many(s21_list.begin(), -1, -23, 4, 1, 5, 6, 4, -1, -1);

  auto it1 = s21_list.begin();
  auto it2 = std_list.begin();
  while (it1 != s21_list.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(list, insert_many_case3) {
  s21::list<double> s21_list{1};
  std::list<double> std_list{0.5, 1.5, 2.0, 1.0};

  s21_list.insert_many(s21_list.begin(), 0.5, 1.5, 2.0);

  auto it1 = s21_list.begin();
  auto it2 = std_list.begin();
  while (it1 != s21_list.end() && it2 != std_list.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }

  EXPECT_EQ(s21_list.size(), std_list.size());
}

TEST(list, modifierInsert) {
  s21::list<int> s21_list_1 = {'a', 'c', 'd'};
  s21::list<int> s21_list_2 = {'a', 'b', 'c', 'd'};

  auto it = s21_list_1.begin();
  ++it;
  s21_list_1.insert(it, 'b');

  auto it1 = s21_list_1.begin();
  auto it2 = s21_list_2.begin();
  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_list_1.size(), s21_list_2.size());
}

TEST(list, insertManyBack_1) {
  s21::list<int> s21_list{1};
  std::list<int> std_list{1, -1, -23, 4, 1, 5, 6, 4, -1, -1};

  s21_list.insert_many_back(-1, -23, 4, 1, 5, 6, 4, -1, -1);

  auto it1 = s21_list.begin();
  auto it2 = std_list.begin();
  while (it1 != s21_list.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(List, Insert_Many_Back_2) {
  s21::list<int> our_list = {1, 2, 3, 4, 5};
  s21::list<int>::iterator our_it;
  our_list.insert_many_back(7, 8, 9);
  our_it = our_list.end();
  --our_it;
  EXPECT_EQ(*our_it, 9);
  --our_it;
  EXPECT_EQ(*our_it, 8);
  --our_it;
  EXPECT_EQ(*our_it, 7);
  --our_it;
  EXPECT_EQ(*our_it, 5);
  --our_it;
  EXPECT_EQ(*our_it, 4);
}

TEST(list, insertManyFront_1) {
  s21::list<int> s21_list{-1};
  std::list<int> std_list{1, -1, -23, 4, 1, 5, 6, 4, -1, -1};

  s21_list.insert_many_front(-1, 4, 6, 5, 1, 4, -23, -1, 1);

  auto it1 = s21_list.begin();
  auto it2 = std_list.begin();
  while (it1 != s21_list.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(List, insertManyFront_2) {
  s21::list<int> our_list = {1, 2, 3, 4, 5};
  s21::list<int>::iterator our_it;
  our_list.insert_many_front(7, 8, 9);
  our_it = our_list.begin();
  EXPECT_EQ(*our_it, 9);
  ++our_it;
  EXPECT_EQ(*our_it, 8);
  ++our_it;
  EXPECT_EQ(*our_it, 7);
  ++our_it;
  EXPECT_EQ(*our_it, 1);
  ++our_it;
  EXPECT_EQ(*our_it, 2);
}
