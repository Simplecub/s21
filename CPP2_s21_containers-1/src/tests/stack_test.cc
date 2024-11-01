#include <deque>

#include "test.h"

typedef s21::stack<int> ListIntStack;
typedef s21::stack<double> ListDblStack;
typedef s21::stack<std::string> ListStrStack;

typedef s21::stack<int, s21::vector<int>> VectorIntStack;
typedef s21::stack<double, s21::vector<double>> VectorDblStack;
typedef s21::stack<std::string, s21::vector<std::string>> VectorStrStack;

typedef s21::stack<int, std::deque<int>> DeqIntStack;
typedef s21::stack<double, std::deque<double>> DeqDblStack;
typedef s21::stack<std::string, std::deque<std::string>> DeqStrStack;

// CONSTRUCTORS
TEST(STACK_TEST, DefaultCtorSize) {
  ListIntStack st_int;
  ListDblStack st_dbl;
  ListStrStack st_str;

  EXPECT_FALSE(st_int.size());
  EXPECT_FALSE(st_dbl.size());
  EXPECT_FALSE(st_str.size());
}

TEST(STACK_TEST, DefaultCtorSizeVector) {
  VectorIntStack st_int;
  VectorDblStack st_dbl;
  VectorStrStack st_str;

  EXPECT_FALSE(st_int.size());
  EXPECT_FALSE(st_dbl.size());
  EXPECT_FALSE(st_str.size());
}

TEST(STACK_TEST, DefaultCtorSizeDeque) {
  DeqIntStack st_int;
  DeqDblStack st_dbl;
  DeqStrStack st_str;

  EXPECT_FALSE(st_int.size());
  EXPECT_FALSE(st_dbl.size());
  EXPECT_FALSE(st_str.size());
}

TEST(STACK_TEST, InitListCtor) {
  ListIntStack st_int{-1, 0, 1, 2, 3, 4};
  ListDblStack st_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  ListStrStack st_str{"Hello", ",", "world", "!"};

  EXPECT_EQ(st_int.size(), 6U);
  EXPECT_EQ(st_dbl.size(), 7U);
  EXPECT_EQ(st_str.size(), 4U);
}

TEST(STACK_TEST, InitListCtorVector) {
  VectorIntStack st_int{-1, 0, 1, 2, 3, 4};
  VectorDblStack st_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  VectorStrStack st_str{"S", ",", "w", "!"};

  EXPECT_EQ(st_int.size(), 6U);
  EXPECT_EQ(st_dbl.size(), 7U);
  EXPECT_EQ(st_str.size(), 4U);
}

TEST(STACK_TEST, InitListCtorDeque) {
  DeqIntStack st_int{-1, 0, 1, 2, 3, 4};
  DeqDblStack st_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  DeqStrStack st_str{"S", ",", "w", "!"};

  EXPECT_EQ(st_int.size(), 6U);
  EXPECT_EQ(st_dbl.size(), 7U);
  EXPECT_EQ(st_str.size(), 4U);
}

TEST(STACK_TEST, CopyCtor) {
  ListIntStack st1_int{-1, 0, 1, 2, 3, 4};
  ListDblStack st1_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  ListStrStack st1_str{"Hello", ",", "world", "!"};

  ListIntStack st2_int{st1_int};
  ListDblStack st2_dbl{st1_dbl};
  ListStrStack st2_str{st1_str};

  EXPECT_EQ(st1_int.size(), st2_int.size());
  EXPECT_EQ(st1_dbl.size(), st2_dbl.size());
  EXPECT_EQ(st1_str.size(), st2_str.size());
}

TEST(STACK_TEST, CopyCtorVector) {
  VectorIntStack st1_int{-1, 0, 1, 2, 3, 4};
  VectorDblStack st1_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  VectorStrStack st1_str{"Hello", ",", "world", "!"};

  VectorIntStack st2_int{st1_int};
  VectorDblStack st2_dbl{st1_dbl};
  VectorStrStack st2_str{st1_str};

  EXPECT_EQ(st1_int.size(), st2_int.size());
  EXPECT_EQ(st1_dbl.size(), st2_dbl.size());
  EXPECT_EQ(st1_str.size(), st2_str.size());
}

TEST(STACK_TEST, CopyCtorDeque) {
  DeqIntStack st1_int{-1, 0, 1, 2, 3, 4};
  DeqDblStack st1_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  DeqStrStack st1_str{"Hello", ",", "world", "!"};

  DeqIntStack st2_int{st1_int};
  DeqDblStack st2_dbl{st1_dbl};
  DeqStrStack st2_str{st1_str};

  EXPECT_EQ(st1_int.size(), st2_int.size());
  EXPECT_EQ(st1_dbl.size(), st2_dbl.size());
  EXPECT_EQ(st1_str.size(), st2_str.size());
}

TEST(STACK_TEST, MoveCtorCopyAssignEmpty) {
  ListIntStack st1_int{-1, 0, 1, 2, 3, 4};
  ListDblStack st1_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  ListStrStack st1_str{"Hello", ",", "world", "!"};

  ListIntStack st2_int;
  ListDblStack st2_dbl;
  ListStrStack st2_str;

  st2_int = st1_int;
  st2_dbl = st1_dbl;
  st2_str = st1_str;

  EXPECT_EQ(st1_int.size(), st2_int.size());
  EXPECT_EQ(st1_dbl.size(), st2_dbl.size());
  EXPECT_EQ(st1_str.size(), st2_str.size());

  ListIntStack st3_int = std::move(st2_int);
  ListDblStack st3_dbl = std::move(st2_dbl);
  ListStrStack st3_str = std::move(st2_str);

  EXPECT_TRUE(st2_int.empty());
  EXPECT_TRUE(st2_dbl.empty());
  EXPECT_TRUE(st2_str.empty());

  EXPECT_EQ(st1_int.size(), st3_int.size());
  EXPECT_EQ(st1_dbl.size(), st3_dbl.size());
  EXPECT_EQ(st1_str.size(), st3_str.size());
}

TEST(STACK_TEST, MoveCtorCopyAssignEmptyVector) {
  VectorIntStack st1_int{-1, 0, 1, 2, 3, 4};
  VectorDblStack st1_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  VectorStrStack st1_str{"Hello", ",", "world", "!"};

  VectorIntStack st2_int;
  VectorDblStack st2_dbl;
  VectorStrStack st2_str;

  st2_int = st1_int;
  st2_dbl = st1_dbl;
  st2_str = st1_str;

  EXPECT_EQ(st1_int.size(), st2_int.size());
  EXPECT_EQ(st1_dbl.size(), st2_dbl.size());
  EXPECT_EQ(st1_str.size(), st2_str.size());

  VectorIntStack st3_int = std::move(st2_int);
  VectorDblStack st3_dbl = std::move(st2_dbl);
  VectorStrStack st3_str = std::move(st2_str);

  EXPECT_TRUE(st2_int.empty());
  EXPECT_TRUE(st2_dbl.empty());
  EXPECT_TRUE(st2_str.empty());

  EXPECT_EQ(st1_int.size(), st3_int.size());
  EXPECT_EQ(st1_dbl.size(), st3_dbl.size());
  EXPECT_EQ(st1_str.size(), st3_str.size());
}

TEST(STACK_TEST, MoveCtorCopyAssignEmptyDeque) {
  DeqIntStack st1_int{-1, 0, 1, 2, 3, 4};
  DeqDblStack st1_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  DeqStrStack st1_str{"Hello", ",", "world", "!"};

  DeqIntStack st2_int;
  DeqDblStack st2_dbl;
  DeqStrStack st2_str;

  st2_int = st1_int;
  st2_dbl = st1_dbl;
  st2_str = st1_str;

  EXPECT_EQ(st1_int.size(), st2_int.size());
  EXPECT_EQ(st1_dbl.size(), st2_dbl.size());
  EXPECT_EQ(st1_str.size(), st2_str.size());

  DeqIntStack st3_int = std::move(st2_int);
  DeqDblStack st3_dbl = std::move(st2_dbl);
  DeqStrStack st3_str = std::move(st2_str);

  EXPECT_TRUE(st2_int.empty());
  EXPECT_TRUE(st2_dbl.empty());
  EXPECT_TRUE(st2_str.empty());

  EXPECT_EQ(st1_int.size(), st3_int.size());
  EXPECT_EQ(st1_dbl.size(), st3_dbl.size());
  EXPECT_EQ(st1_str.size(), st3_str.size());
}

TEST(STACK_TEST, MoveAssign) {
  ListIntStack st1_int{-1, 0, 1, 2, 3, 4};
  ListDblStack st1_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  ListStrStack st1_str{"Hello", ",", "world", "!"};

  ListIntStack st2_int;
  ListDblStack st2_dbl;
  ListStrStack st2_str;

  st2_int = std::move(st1_int);
  st2_dbl = std::move(st1_dbl);
  st2_str = std::move(st1_str);

  EXPECT_TRUE(st1_int.empty());
  EXPECT_TRUE(st1_dbl.empty());
  EXPECT_TRUE(st1_str.empty());

  EXPECT_EQ(st2_int.size(), 6U);
  EXPECT_EQ(st2_dbl.size(), 7U);
  EXPECT_EQ(st2_str.size(), 4U);
}

TEST(STACK_TEST, MoveAssignVector) {
  VectorIntStack st1_int{-1, 0, 1, 2, 3, 4};
  VectorDblStack st1_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  VectorStrStack st1_str{"Hello", ",", "world", "!"};

  VectorIntStack st2_int;
  VectorDblStack st2_dbl;
  VectorStrStack st2_str;

  st2_int = std::move(st1_int);
  st2_dbl = std::move(st1_dbl);
  st2_str = std::move(st1_str);

  EXPECT_TRUE(st1_int.empty());
  EXPECT_TRUE(st1_dbl.empty());
  EXPECT_TRUE(st1_str.empty());

  EXPECT_EQ(st2_int.size(), 6U);
  EXPECT_EQ(st2_dbl.size(), 7U);
  EXPECT_EQ(st2_str.size(), 4U);
}

TEST(STACK_TEST, MoveAssignDeque) {
  DeqIntStack st1_int{-1, 0, 1, 2, 3, 4};
  DeqDblStack st1_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  DeqStrStack st1_str{"Hello", ",", "world", "!"};

  DeqIntStack st2_int;
  DeqDblStack st2_dbl;
  DeqStrStack st2_str;

  st2_int = std::move(st1_int);
  st2_dbl = std::move(st1_dbl);
  st2_str = std::move(st1_str);

  EXPECT_TRUE(st1_int.empty());
  EXPECT_TRUE(st1_dbl.empty());
  EXPECT_TRUE(st1_str.empty());

  EXPECT_EQ(st2_int.size(), 6U);
  EXPECT_EQ(st2_dbl.size(), 7U);
  EXPECT_EQ(st2_str.size(), 4U);
}

TEST(STACK_TEST, PushTopPop) {
  ListIntStack st_int{-1, 0, 1, 2, 3, 4};
  ListDblStack st_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  ListStrStack st_str{"Hello", ",", "world", "!"};

  EXPECT_EQ(st_int.size(), 6U);
  EXPECT_EQ(st_dbl.size(), 7U);
  EXPECT_EQ(st_str.size(), 4U);

  EXPECT_EQ(st_int.top(), 4);
  EXPECT_EQ(st_dbl.top(), 1.23);
  EXPECT_EQ(st_str.top(), "!");

  st_int.push(5);
  st_dbl.push(-3683.5680);
  st_str.push("!!");

  EXPECT_EQ(st_int.size(), 7U);
  EXPECT_EQ(st_dbl.size(), 8U);
  EXPECT_EQ(st_str.size(), 5U);

  EXPECT_EQ(st_int.top(), 5);
  EXPECT_EQ(st_dbl.top(), -3683.5680);
  EXPECT_EQ(st_str.top(), "!!");

  st_int.pop();
  st_dbl.pop();
  st_str.pop();

  EXPECT_EQ(st_int.size(), 6U);
  EXPECT_EQ(st_dbl.size(), 7U);
  EXPECT_EQ(st_str.size(), 4U);

  EXPECT_EQ(st_int.top(), 4);
  EXPECT_EQ(st_dbl.top(), 1.23);
  EXPECT_EQ(st_str.top(), "!");
}

TEST(STACK_TEST, PushTopPopVector) {
  VectorIntStack st_int{-1, 0, 1, 2, 3, 4};
  VectorDblStack st_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  VectorStrStack st_str{"Hello", ",", "world", "!"};

  EXPECT_EQ(st_int.size(), 6U);
  EXPECT_EQ(st_dbl.size(), 7U);
  EXPECT_EQ(st_str.size(), 4U);

  EXPECT_EQ(st_int.top(), 4);
  EXPECT_EQ(st_dbl.top(), 1.23);
  EXPECT_EQ(st_str.top(), "!");

  st_int.push(5);
  st_dbl.push(-3683.5680);
  st_str.push("!!");

  EXPECT_EQ(st_int.size(), 7U);
  EXPECT_EQ(st_dbl.size(), 8U);
  EXPECT_EQ(st_str.size(), 5U);

  EXPECT_EQ(st_int.top(), 5);
  EXPECT_EQ(st_dbl.top(), -3683.5680);
  EXPECT_EQ(st_str.top(), "!!");

  st_int.pop();
  st_dbl.pop();
  st_str.pop();

  EXPECT_EQ(st_int.size(), 6U);
  EXPECT_EQ(st_dbl.size(), 7U);
  EXPECT_EQ(st_str.size(), 4U);

  EXPECT_EQ(st_int.top(), 4);
  EXPECT_EQ(st_dbl.top(), 1.23);
  EXPECT_EQ(st_str.top(), "!");
}

TEST(STACK_TEST, PushTopPopQueue) {
  DeqIntStack st_int{-1, 0, 1, 2, 3, 4};
  DeqDblStack st_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  DeqStrStack st_str{"Hello", ",", "world", "!"};

  EXPECT_EQ(st_int.size(), 6U);
  EXPECT_EQ(st_dbl.size(), 7U);
  EXPECT_EQ(st_str.size(), 4U);

  EXPECT_EQ(st_int.top(), 4);
  EXPECT_EQ(st_dbl.top(), 1.23);
  EXPECT_EQ(st_str.top(), "!");

  st_int.push(5);
  st_dbl.push(-3683.5680);
  st_str.push("!!");

  EXPECT_EQ(st_int.size(), 7U);
  EXPECT_EQ(st_dbl.size(), 8U);
  EXPECT_EQ(st_str.size(), 5U);

  EXPECT_EQ(st_int.top(), 5);
  EXPECT_EQ(st_dbl.top(), -3683.5680);
  EXPECT_EQ(st_str.top(), "!!");

  st_int.pop();
  st_dbl.pop();
  st_str.pop();

  EXPECT_EQ(st_int.size(), 6U);
  EXPECT_EQ(st_dbl.size(), 7U);
  EXPECT_EQ(st_str.size(), 4U);

  EXPECT_EQ(st_int.top(), 4);
  EXPECT_EQ(st_dbl.top(), 1.23);
  EXPECT_EQ(st_str.top(), "!");
}

TEST(STACK_TEST, Swap) {
  ListIntStack st1_int{-1, 0, 1, 2, 3, 4};
  ListDblStack st1_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  ListStrStack st1_str{"Hello", ",", "world", "!"};

  ListIntStack st2_int;
  ListDblStack st2_dbl;
  ListStrStack st2_str;

  st1_int.swap(st2_int);
  st1_dbl.swap(st2_dbl);
  st1_str.swap(st2_str);

  EXPECT_TRUE(st1_int.empty());
  EXPECT_TRUE(st1_dbl.empty());
  EXPECT_TRUE(st1_str.empty());

  EXPECT_EQ(st2_int.size(), 6U);
  EXPECT_EQ(st2_dbl.size(), 7U);
  EXPECT_EQ(st2_str.size(), 4U);
}

TEST(STACK_TEST, SwapVector) {
  VectorIntStack st1_int{-1, 0, 1, 2, 3, 4};
  VectorDblStack st1_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  VectorStrStack st1_str{"Hello", ",", "world", "!"};

  VectorIntStack st2_int;
  VectorDblStack st2_dbl;
  VectorStrStack st2_str;

  st1_int.swap(st2_int);
  st1_dbl.swap(st2_dbl);
  st1_str.swap(st2_str);

  EXPECT_TRUE(st1_int.empty());
  EXPECT_TRUE(st1_dbl.empty());
  EXPECT_TRUE(st1_str.empty());

  EXPECT_EQ(st2_int.size(), 6U);
  EXPECT_EQ(st2_dbl.size(), 7U);
  EXPECT_EQ(st2_str.size(), 4U);
}

TEST(STACK_TEST, SwapDeque) {
  DeqIntStack st1_int{-1, 0, 1, 2, 3, 4};
  DeqDblStack st1_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  DeqStrStack st1_str{"Hello", ",", "world", "!"};

  DeqIntStack st2_int;
  DeqDblStack st2_dbl;
  DeqStrStack st2_str;

  st1_int.swap(st2_int);
  st1_dbl.swap(st2_dbl);
  st1_str.swap(st2_str);

  EXPECT_TRUE(st1_int.empty());
  EXPECT_TRUE(st1_dbl.empty());
  EXPECT_TRUE(st1_str.empty());

  EXPECT_EQ(st2_int.size(), 6U);
  EXPECT_EQ(st2_dbl.size(), 7U);
  EXPECT_EQ(st2_str.size(), 4U);
}

TEST(STACK_TEST, InsertMany) {
  ListIntStack st_int{-1, 0, 1, 2, 3, 4};
  ListDblStack st_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  ListStrStack st_str{"Hello", ",", "world", "!"};

  st_int.insert_many_front();
  st_dbl.insert_many_front();
  st_str.insert_many_front();

  EXPECT_EQ(st_int.size(), 6U);
  EXPECT_EQ(st_dbl.size(), 7U);
  EXPECT_EQ(st_str.size(), 4U);

  EXPECT_EQ(st_int.top(), 4);
  EXPECT_EQ(st_dbl.top(), 1.23);
  EXPECT_EQ(st_str.top(), "!");

  st_int.insert_many_front(-5);
  st_dbl.insert_many_front(-4.009);
  st_str.insert_many_front("\n");

  EXPECT_EQ(st_int.size(), 7U);
  EXPECT_EQ(st_dbl.size(), 8U);
  EXPECT_EQ(st_str.size(), 5U);

  EXPECT_EQ(st_int.top(), -5);
  EXPECT_EQ(st_dbl.top(), -4.009);
  EXPECT_EQ(st_str.top(), "\n");

  st_int.insert_many_front(5, 6, 7, 8);
  st_dbl.insert_many_front(3.563, -456.123, 0);
  st_str.insert_many_front("--", "");

  EXPECT_EQ(st_int.size(), 11U);
  EXPECT_EQ(st_dbl.size(), 11U);
  EXPECT_EQ(st_str.size(), 7U);

  EXPECT_EQ(st_int.top(), 8);
  EXPECT_EQ(st_dbl.top(), 0);
  EXPECT_EQ(st_str.top(), "");
}

TEST(STACK_TEST, InsertManyVector) {
  VectorIntStack st_int{-1, 0, 1, 2, 3, 4};
  VectorDblStack st_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  VectorStrStack st_str{"Hello", ",", "world", "!"};

  st_int.insert_many_front();
  st_dbl.insert_many_front();
  st_str.insert_many_front();

  EXPECT_EQ(st_int.size(), 6U);
  EXPECT_EQ(st_dbl.size(), 7U);
  EXPECT_EQ(st_str.size(), 4U);

  EXPECT_EQ(st_int.top(), 4);
  EXPECT_EQ(st_dbl.top(), 1.23);
  EXPECT_EQ(st_str.top(), "!");

  st_int.insert_many_front(-5);
  st_dbl.insert_many_front(-4.009);
  st_str.insert_many_front("\n");

  EXPECT_EQ(st_int.size(), 7U);
  EXPECT_EQ(st_dbl.size(), 8U);
  EXPECT_EQ(st_str.size(), 5U);

  EXPECT_EQ(st_int.top(), -5);
  EXPECT_EQ(st_dbl.top(), -4.009);
  EXPECT_EQ(st_str.top(), "\n");

  st_int.insert_many_front(5, 6, 7, 8);
  st_dbl.insert_many_front(3.563, -456.123, 0);
  st_str.insert_many_front("--", "");

  EXPECT_EQ(st_int.size(), 11U);
  EXPECT_EQ(st_dbl.size(), 11U);
  EXPECT_EQ(st_str.size(), 7U);

  EXPECT_EQ(st_int.top(), 8);
  EXPECT_EQ(st_dbl.top(), 0);
  EXPECT_EQ(st_str.top(), "");
}

TEST(STACK_TEST, InsertManyDeque) {
  DeqIntStack st_int{-1, 0, 1, 2, 3, 4};
  DeqDblStack st_dbl{0, 1.3, 1, -1, -2847.4, 923.39281, 1.23};
  DeqStrStack st_str{"Hello", ",", "world", "!"};

  st_int.insert_many_front();
  st_dbl.insert_many_front();
  st_str.insert_many_front();

  EXPECT_EQ(st_int.size(), 6U);
  EXPECT_EQ(st_dbl.size(), 7U);
  EXPECT_EQ(st_str.size(), 4U);

  EXPECT_EQ(st_int.top(), 4);
  EXPECT_EQ(st_dbl.top(), 1.23);
  EXPECT_EQ(st_str.top(), "!");

  st_int.insert_many_front(-5);
  st_dbl.insert_many_front(-4.009);
  st_str.insert_many_front("\n");

  EXPECT_EQ(st_int.size(), 7U);
  EXPECT_EQ(st_dbl.size(), 8U);
  EXPECT_EQ(st_str.size(), 5U);

  EXPECT_EQ(st_int.top(), -5);
  EXPECT_EQ(st_dbl.top(), -4.009);
  EXPECT_EQ(st_str.top(), "\n");

  st_int.insert_many_front(5, 6, 7, 8);
  st_dbl.insert_many_front(3.563, -456.123, 0);
  st_str.insert_many_front("--", "");

  EXPECT_EQ(st_int.size(), 11U);
  EXPECT_EQ(st_dbl.size(), 11U);
  EXPECT_EQ(st_str.size(), 7U);

  EXPECT_EQ(st_int.top(), 8);
  EXPECT_EQ(st_dbl.top(), 0);
  EXPECT_EQ(st_str.top(), "");
}
