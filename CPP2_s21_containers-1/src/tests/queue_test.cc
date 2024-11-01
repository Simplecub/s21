#include <deque>

#include "test.h"

typedef s21::queue<int> ListIntQueue;
typedef s21::queue<double> ListDblQueue;
typedef s21::queue<std::string> ListStrQueue;

typedef s21::queue<int, std::deque<int>> DeqIntQueue;
typedef s21::queue<double, std::deque<double>> DeqDblQueue;
typedef s21::queue<std::string, std::deque<std::string>> DeqStrQueue;

// CONSTRUCTORS
TEST(QUEUE_TEST, DefaultCtorSize) {
  ListIntQueue q_int;
  ListDblQueue q_dbl;
  ListStrQueue q_str;

  EXPECT_FALSE(q_int.size());
  EXPECT_FALSE(q_dbl.size());
  EXPECT_FALSE(q_str.size());
}

TEST(QUEUE_TEST, DefaultCtorSizeDeque) {
  DeqIntQueue q_int;
  DeqDblQueue q_dbl;
  DeqStrQueue q_str;

  EXPECT_FALSE(q_int.size());
  EXPECT_FALSE(q_dbl.size());
  EXPECT_FALSE(q_str.size());
}

TEST(QUEUE_TEST, InitListCtor) {
  ListIntQueue q_int{-1, 0, 1, 2, 3, 4};
  ListDblQueue q_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  ListStrQueue q_str{"Hello", ",", "world", "!"};

  EXPECT_EQ(q_int.size(), 6U);
  EXPECT_EQ(q_dbl.size(), 7U);
  EXPECT_EQ(q_str.size(), 4U);
}

TEST(QUEUE_TEST, InitListCtorDeque) {
  DeqIntQueue q_int{-1, 0, 1, 2, 3, 4};
  DeqDblQueue q_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  DeqStrQueue q_str{"S", ",", "w", "!"};

  EXPECT_EQ(q_int.size(), 6U);
  EXPECT_EQ(q_dbl.size(), 7U);
  EXPECT_EQ(q_str.size(), 4U);
}

TEST(QUEUE_TEST, CopyCtor) {
  ListIntQueue q1_int{-1, 0, 1, 2, 3, 4};
  ListDblQueue q1_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  ListStrQueue q1_str{"Hello", ",", "world", "!"};

  ListIntQueue q2_int{q1_int};
  ListDblQueue q2_dbl{q1_dbl};
  ListStrQueue q2_str{q1_str};

  EXPECT_EQ(q1_int.size(), q2_int.size());
  EXPECT_EQ(q1_dbl.size(), q2_dbl.size());
  EXPECT_EQ(q1_str.size(), q2_str.size());
}

TEST(QUEUE_TEST, CopyCtorDeque) {
  DeqIntQueue q1_int{-1, 0, 1, 2, 3, 4};
  DeqDblQueue q1_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  DeqStrQueue q1_str{"Hello", ",", "world", "!"};

  DeqIntQueue q2_int{q1_int};
  DeqDblQueue q2_dbl{q1_dbl};
  DeqStrQueue q2_str{q1_str};

  EXPECT_EQ(q1_int.size(), q2_int.size());
  EXPECT_EQ(q1_dbl.size(), q2_dbl.size());
  EXPECT_EQ(q1_str.size(), q2_str.size());
}

TEST(QUEUE_TEST, MoveCtorCopyAssignEmpty) {
  ListIntQueue q1_int{-1, 0, 1, 2, 3, 4};
  ListDblQueue q1_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  ListStrQueue q1_str{"Hello", ",", "world", "!"};

  ListIntQueue q2_int;
  ListDblQueue q2_dbl;
  ListStrQueue q2_str;

  q2_int = q1_int;
  q2_dbl = q1_dbl;
  q2_str = q1_str;

  EXPECT_EQ(q1_int.size(), q2_int.size());
  EXPECT_EQ(q1_dbl.size(), q2_dbl.size());
  EXPECT_EQ(q1_str.size(), q2_str.size());

  ListIntQueue q3_int = std::move(q2_int);
  ListDblQueue q3_dbl = std::move(q2_dbl);
  ListStrQueue q3_str = std::move(q2_str);

  EXPECT_TRUE(q2_int.empty());
  EXPECT_TRUE(q2_dbl.empty());
  EXPECT_TRUE(q2_str.empty());

  EXPECT_EQ(q1_int.size(), q3_int.size());
  EXPECT_EQ(q1_dbl.size(), q3_dbl.size());
  EXPECT_EQ(q1_str.size(), q3_str.size());
}

TEST(QUEUE_TEST, MoveCtorCopyAssignEmptyDeque) {
  DeqIntQueue q1_int{-1, 0, 1, 2, 3, 4};
  DeqDblQueue q1_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  DeqStrQueue q1_str{"Hello", ",", "world", "!"};

  DeqIntQueue q2_int;
  DeqDblQueue q2_dbl;
  DeqStrQueue q2_str;

  q2_int = q1_int;
  q2_dbl = q1_dbl;
  q2_str = q1_str;

  EXPECT_EQ(q1_int.size(), q2_int.size());
  EXPECT_EQ(q1_dbl.size(), q2_dbl.size());
  EXPECT_EQ(q1_str.size(), q2_str.size());

  DeqIntQueue q3_int = std::move(q2_int);
  DeqDblQueue q3_dbl = std::move(q2_dbl);
  DeqStrQueue q3_str = std::move(q2_str);

  EXPECT_TRUE(q2_int.empty());
  EXPECT_TRUE(q2_dbl.empty());
  EXPECT_TRUE(q2_str.empty());

  EXPECT_EQ(q1_int.size(), q3_int.size());
  EXPECT_EQ(q1_dbl.size(), q3_dbl.size());
  EXPECT_EQ(q1_str.size(), q3_str.size());
}

TEST(QUEUE_TEST, MoveAssign) {
  ListIntQueue q1_int{-1, 0, 1, 2, 3, 4};
  ListDblQueue q1_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  ListStrQueue q1_str{"Hello", ",", "world", "!"};

  ListIntQueue q2_int;
  ListDblQueue q2_dbl;
  ListStrQueue q2_str;

  q2_int = std::move(q1_int);
  q2_dbl = std::move(q1_dbl);
  q2_str = std::move(q1_str);

  EXPECT_TRUE(q1_int.empty());
  EXPECT_TRUE(q1_dbl.empty());
  EXPECT_TRUE(q1_str.empty());

  EXPECT_EQ(q2_int.size(), 6U);
  EXPECT_EQ(q2_dbl.size(), 7U);
  EXPECT_EQ(q2_str.size(), 4U);
}

TEST(QUEUE_TEST, MoveAssignDeque) {
  DeqIntQueue q1_int{-1, 0, 1, 2, 3, 4};
  DeqDblQueue q1_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  DeqStrQueue q1_str{"Hello", ",", "world", "!"};

  DeqIntQueue q2_int;
  DeqDblQueue q2_dbl;
  DeqStrQueue q2_str;

  q2_int = std::move(q1_int);
  q2_dbl = std::move(q1_dbl);
  q2_str = std::move(q1_str);

  EXPECT_TRUE(q1_int.empty());
  EXPECT_TRUE(q1_dbl.empty());
  EXPECT_TRUE(q1_str.empty());

  EXPECT_EQ(q2_int.size(), 6U);
  EXPECT_EQ(q2_dbl.size(), 7U);
  EXPECT_EQ(q2_str.size(), 4U);
}

TEST(QUEUE_TEST, PushBackFrontPop) {
  ListIntQueue q_int{-1, 0, 1, 2, 3, 4};
  ListDblQueue q_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  ListStrQueue q_str{"Hello", ",", "world", "!"};

  EXPECT_EQ(q_int.size(), 6U);
  EXPECT_EQ(q_dbl.size(), 7U);
  EXPECT_EQ(q_str.size(), 4U);

  EXPECT_EQ(q_int.back(), 4);
  EXPECT_EQ(q_dbl.back(), 1.23);
  EXPECT_EQ(q_str.back(), "!");

  EXPECT_EQ(q_int.front(), -1);
  EXPECT_EQ(q_dbl.front(), 0);
  EXPECT_EQ(q_str.front(), "Hello");

  q_int.push(5);
  q_dbl.push(-3683.5680);
  q_str.push("!!");

  EXPECT_EQ(q_int.size(), 7U);
  EXPECT_EQ(q_dbl.size(), 8U);
  EXPECT_EQ(q_str.size(), 5U);

  EXPECT_EQ(q_int.back(), 5);
  EXPECT_EQ(q_dbl.back(), -3683.5680);
  EXPECT_EQ(q_str.back(), "!!");

  q_int.pop();
  q_dbl.pop();
  q_str.pop();

  EXPECT_EQ(q_int.size(), 6U);
  EXPECT_EQ(q_dbl.size(), 7U);
  EXPECT_EQ(q_str.size(), 4U);

  EXPECT_EQ(q_int.front(), 0);
  EXPECT_EQ(q_dbl.front(), 1.3);
  EXPECT_EQ(q_str.front(), ",");
}

TEST(QUEUE_TEST, PushBackFrontPopDeque) {
  DeqIntQueue q_int{-1, 0, 1, 2, 3, 4};
  DeqDblQueue q_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  DeqStrQueue q_str{"Hello", ",", "world", "!"};

  EXPECT_EQ(q_int.size(), 6U);
  EXPECT_EQ(q_dbl.size(), 7U);
  EXPECT_EQ(q_str.size(), 4U);

  EXPECT_EQ(q_int.back(), 4);
  EXPECT_EQ(q_dbl.back(), 1.23);
  EXPECT_EQ(q_str.back(), "!");

  EXPECT_EQ(q_int.front(), -1);
  EXPECT_EQ(q_dbl.front(), 0);
  EXPECT_EQ(q_str.front(), "Hello");

  q_int.push(5);
  q_dbl.push(-3683.5680);
  q_str.push("!!");

  EXPECT_EQ(q_int.size(), 7U);
  EXPECT_EQ(q_dbl.size(), 8U);
  EXPECT_EQ(q_str.size(), 5U);

  EXPECT_EQ(q_int.back(), 5);
  EXPECT_EQ(q_dbl.back(), -3683.5680);
  EXPECT_EQ(q_str.back(), "!!");

  q_int.pop();
  q_dbl.pop();
  q_str.pop();

  EXPECT_EQ(q_int.size(), 6U);
  EXPECT_EQ(q_dbl.size(), 7U);
  EXPECT_EQ(q_str.size(), 4U);

  EXPECT_EQ(q_int.front(), 0);
  EXPECT_EQ(q_dbl.front(), 1.3);
  EXPECT_EQ(q_str.front(), ",");
}

TEST(QUEUE_TEST, InsertMany) {
  ListIntQueue q_int{-1, 0, 1, 2, 3, 4};
  ListDblQueue q_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  ListStrQueue q_str{"Hello", ",", "world", "!"};

  q_int.insert_many_back();
  q_dbl.insert_many_back();
  q_str.insert_many_back();

  EXPECT_EQ(q_int.size(), 6U);
  EXPECT_EQ(q_dbl.size(), 7U);
  EXPECT_EQ(q_str.size(), 4U);

  EXPECT_EQ(q_int.back(), 4);
  EXPECT_EQ(q_dbl.back(), 1.23);
  EXPECT_EQ(q_str.back(), "!");

  q_int.insert_many_back(-5);
  q_dbl.insert_many_back(-4.009);
  q_str.insert_many_back("\n");

  EXPECT_EQ(q_int.size(), 7U);
  EXPECT_EQ(q_dbl.size(), 8U);
  EXPECT_EQ(q_str.size(), 5U);

  EXPECT_EQ(q_int.back(), -5);
  EXPECT_EQ(q_dbl.back(), -4.009);
  EXPECT_EQ(q_str.back(), "\n");

  q_int.insert_many_back(5, 6, 7, 8);
  q_dbl.insert_many_back(3.563, -456.123, 0);
  q_str.insert_many_back("--", "");

  EXPECT_EQ(q_int.size(), 11U);
  EXPECT_EQ(q_dbl.size(), 11U);
  EXPECT_EQ(q_str.size(), 7U);

  EXPECT_EQ(q_int.back(), 8);
  EXPECT_EQ(q_dbl.back(), 0);
  EXPECT_EQ(q_str.back(), "");
}

TEST(QUEUE_TEST, InsertManyDeque) {
  DeqIntQueue q_int{-1, 0, 1, 2, 3, 4};
  DeqDblQueue q_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  DeqStrQueue q_str{"Hello", ",", "world", "!"};

  q_int.insert_many_back();
  q_dbl.insert_many_back();
  q_str.insert_many_back();

  EXPECT_EQ(q_int.size(), 6U);
  EXPECT_EQ(q_dbl.size(), 7U);
  EXPECT_EQ(q_str.size(), 4U);

  EXPECT_EQ(q_int.back(), 4);
  EXPECT_EQ(q_dbl.back(), 1.23);
  EXPECT_EQ(q_str.back(), "!");

  q_int.insert_many_back(-5);
  q_dbl.insert_many_back(-4.009);
  q_str.insert_many_back("\n");

  EXPECT_EQ(q_int.size(), 7U);
  EXPECT_EQ(q_dbl.size(), 8U);
  EXPECT_EQ(q_str.size(), 5U);

  EXPECT_EQ(q_int.back(), -5);
  EXPECT_EQ(q_dbl.back(), -4.009);
  EXPECT_EQ(q_str.back(), "\n");

  q_int.insert_many_back(5, 6, 7, 8);
  q_dbl.insert_many_back(3.563, -456.123, 0);
  q_str.insert_many_back("--", "");

  EXPECT_EQ(q_int.size(), 11U);
  EXPECT_EQ(q_dbl.size(), 11U);
  EXPECT_EQ(q_str.size(), 7U);

  EXPECT_EQ(q_int.back(), 8);
  EXPECT_EQ(q_dbl.back(), 0);
  EXPECT_EQ(q_str.back(), "");
}

TEST(QUEUE_TEST, Swap) {
  ListIntQueue q1_int{-1, 0, 1, 2, 3, 4};
  ListDblQueue q1_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  ListStrQueue q1_str{"Hello", ",", "world", "!"};

  ListIntQueue q2_int;
  ListDblQueue q2_dbl;
  ListStrQueue q2_str;

  q1_int.swap(q2_int);
  q1_dbl.swap(q2_dbl);
  q1_str.swap(q2_str);

  EXPECT_TRUE(q1_int.empty());
  EXPECT_TRUE(q1_dbl.empty());
  EXPECT_TRUE(q1_str.empty());

  EXPECT_EQ(q2_int.size(), 6U);
  EXPECT_EQ(q2_dbl.size(), 7U);
  EXPECT_EQ(q2_str.size(), 4U);
}

TEST(QUEUE_TEST, SwapDeque) {
  DeqIntQueue q1_int{-1, 0, 1, 2, 3, 4};
  DeqDblQueue q1_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  DeqStrQueue q1_str{"Hello", ",", "world", "!"};

  DeqIntQueue q2_int;
  DeqDblQueue q2_dbl;
  DeqStrQueue q2_str;

  q1_int.swap(q2_int);
  q1_dbl.swap(q2_dbl);
  q1_str.swap(q2_str);

  EXPECT_TRUE(q1_int.empty());
  EXPECT_TRUE(q1_dbl.empty());
  EXPECT_TRUE(q1_str.empty());

  EXPECT_EQ(q2_int.size(), 6U);
  EXPECT_EQ(q2_dbl.size(), 7U);
  EXPECT_EQ(q2_str.size(), 4U);
}
