#include <gtest/gtest.h>

#include <iostream>
#include <map>
#include <string>

#include "../s21_map.h"

TEST(map, ConstructorDefaultMap) {
  s21::map<int, char> my_empty_map;
  std::map<int, char> orig_empty_map;
  EXPECT_EQ(my_empty_map.empty(), orig_empty_map.empty());
}

TEST(map, ConstructorInitializerMap) {
  s21::map<int, int> my_map = {{1, 1}, {2, 2}, {3, 3}, {4, 4}};
  std::map<int, int> orig_map = {{1, 1}, {2, 2}, {3, 3}, {4, 4}};
  EXPECT_EQ(my_map.size(), orig_map.size());
  auto my_it = my_map.begin();
  auto orig_it = orig_map.begin();

  for (; my_it != my_map.end(); my_it++, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(map, ConstructorInitializer2Map) {
  s21::map<int, char> my_map = {};
  std::map<int, char> orig_map = {};
  EXPECT_EQ(my_map.size(), orig_map.size());

  auto my_it = my_map.begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.end(); my_it++, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(map, ConstructorCopyMap) {
  s21::map<int, int> my_map = {{3, 4}, {1, 2}, {5, 6}};
  std::map<int, int> orig_map = {{3, 4}, {1, 2}, {5, 6}};
  s21::map<int, int> my_map_copy = my_map;
  std::map<int, int> orig_map_copy = orig_map;
  EXPECT_EQ(my_map_copy.size(), orig_map_copy.size());
  auto my_it = my_map_copy.begin();
  auto orig_it = orig_map_copy.begin();
  for (; my_it != my_map_copy.end(); my_it++, orig_it++) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(map, ConstructorMoveMap) {
  s21::map<int, int> my_map = {{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> orig_map = {{1, 2}, {3, 4}, {5, 6}};
  s21::map<int, int> my_map_copy = my_map;
  std::map<int, int> orig_map_copy = std::move(orig_map);

  EXPECT_EQ(my_map_copy.size(), orig_map_copy.size());
  auto my_it = my_map_copy.begin();
  auto orig_it = orig_map_copy.begin();
  for (; my_it != my_map_copy.end(); my_it++, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(map, MaxSize) {
  s21::map<int, int> m1;
  std::map<int, int> m2;
  EXPECT_EQ(m1.max_size(), 576460752303423487U);
}

TEST(map, MapOperator) {
  s21::map<int, int> my_map = {{1, 1}, {2, 2}, {3, 3}};
  std::map<int, int> orig_map = {{1, 1}, {2, 2}, {3, 3}};
  my_map[1] = 11;
  orig_map[1] = 11;
  orig_map[2] = 22;

  EXPECT_TRUE(my_map[1] == orig_map[1]);
  EXPECT_FALSE(my_map[2] == orig_map[2]);
  EXPECT_TRUE(my_map[3] == orig_map[3]);
}

TEST(map, MapAtOperatorException) {
  s21::map<char, std::string> my_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  EXPECT_THROW(my_map.at('g') = "Alisa", std::out_of_range);
}

TEST(map, MapAtOperator) {
  s21::map<char, std::string> my_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  std::map<char, std::string> orig_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  my_map.at('a') = "Alisa";
  orig_map.at('a') = "Alisa";
  orig_map.at('b') = "Ben";
  EXPECT_TRUE(my_map['a'] == orig_map['a']);
  EXPECT_FALSE(my_map['b'] == orig_map['b']);
  EXPECT_TRUE(my_map['c'] == orig_map['c']);
}

TEST(map, MapCapacity) {
  s21::map<char, std::string> my_map;
  std::map<char, std::string> orig_map;
  EXPECT_TRUE(my_map.empty() == orig_map.empty());
  my_map.insert('z', "wow");
  EXPECT_FALSE(my_map.empty() == orig_map.empty());
  EXPECT_EQ(my_map.size(), 1U);
}

TEST(map, MapClear) {
  s21::map<int, int> my_map;
  std::map<int, int> orig_map;
  my_map.clear();
  orig_map.clear();
  EXPECT_EQ(my_map.empty(), orig_map.empty());
  my_map.insert(std::make_pair(1, 1));
  orig_map.insert(std::make_pair(1, 1));
  EXPECT_EQ(my_map.empty(), orig_map.empty());
  my_map.clear();
  orig_map.clear();
  EXPECT_EQ(my_map.empty(), orig_map.empty());
}

TEST(map, MapInsert1) {
  s21::map<int, char> my_map;
  std::map<int, char> orig_map;

  EXPECT_EQ((*(my_map.insert(std::make_pair(1, 'a')).first)).first,
            (*(orig_map.insert(std::make_pair(1, 'a')).first)).first);
  EXPECT_EQ((*(my_map.insert(std::make_pair(2, 'a')).first)).second,
            (*(orig_map.insert(std::make_pair(2, 'a')).first)).second);
  EXPECT_TRUE((my_map.insert(std::make_pair(1, 'a'))).second ==
              (orig_map.insert(std::make_pair(1, 'a'))).second);
}

TEST(map, MapInsert2) {
  s21::map<int, char> my_map;
  std::map<int, char> orig_map;
  const int key1 = 1;
  const int key2 = 2;
  const char value1 = 'a';

  EXPECT_EQ((*(my_map.insert(key1, value1).first)).first,
            (*(orig_map.insert(std::make_pair(1, 'a')).first)).first);
  EXPECT_EQ((*(my_map.insert(key2, value1).first)).second,
            (*(orig_map.insert(std::make_pair(2, 'a')).first)).second);
  EXPECT_TRUE((my_map.insert(key1, value1)).second ==
              (orig_map.insert(std::make_pair(1, 'a'))).second);
}

TEST(map, MapInsert3) {
  s21::map<int, char> my_map;
  std::map<int, char> orig_map;
  const int key1 = 1;
  const int key2 = 2;
  const char value1 = 'a';
  const char value2 = 'b';

  EXPECT_EQ((*(my_map.insert_or_assign(key1, value1).first)).first,
            (*(orig_map.insert_or_assign(key1, value1).first)).first);
  EXPECT_EQ((*(my_map.insert_or_assign(key2, value1).first)).second,
            (*(orig_map.insert_or_assign(key2, value1).first)).second);
  EXPECT_TRUE((my_map.insert_or_assign(key1, value2)).second ==
              (orig_map.insert_or_assign(key1, value2)).second);
}

TEST(map, MapErase) {
  s21::map<int, char> my_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  std::map<int, char> orig_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  EXPECT_EQ(my_map.size(), orig_map.size());

  EXPECT_EQ(my_map.size(), orig_map.size());
  EXPECT_TRUE(my_map.contains(1));

  const int key1 = 22;
  const int value1 = 'm';
  auto iter =
      s21::map<int, char>::MapIterator(my_map.insert(key1, value1).first);

  my_map.erase(iter);
  EXPECT_FALSE(my_map.contains(22));
  s21::map<int, char> my_map2 = {{1, 1}, {3, 3}, {4, 4}};
  const int key2 = 2;
  const int value2 = 2;
  auto iter2 =
      s21::map<int, char>::MapIterator(my_map2.insert(key2, value2).first);
  my_map2.erase(iter2);
}

TEST(map, SwapMap) {
  s21::map<int, int> my_map = {{1, 1}};
  s21::map<int, int> my_swap_map = {{3, 3}, {4, 4}};

  my_map.swap(my_swap_map);
  EXPECT_EQ(my_map.size(), 2U);
  EXPECT_EQ(my_swap_map.size(), 1U);
  auto x = (*(my_map.begin())).first;
  auto y = (*(my_swap_map.begin())).first;
  EXPECT_EQ(x, 3);
  EXPECT_EQ(y, 1);
}

TEST(map, MergeMap) {
  s21::map<int, int> m6({{1, 1}, {2, 2}, {3, 3}});
  s21::map<int, int> m7({{1, 1}, {5, 5}});
  m6.merge(m7);
  EXPECT_TRUE(m6.contains(5));
  EXPECT_TRUE(m6.contains(1));
}

TEST(map_InsertMany_Test, TestBody) {
  s21::map<int, int> mapMy({{1, 10}});
  mapMy.insert_many(std::make_pair(2, 20), std::make_pair(3, 30),
                    std::make_pair(4, 40));
  mapMy.insert_many();
  EXPECT_EQ(mapMy.size(), 4U);
  EXPECT_EQ(mapMy[1], 10);
  EXPECT_EQ(mapMy[2], 20);
  EXPECT_EQ(mapMy[3], 30);
  EXPECT_EQ(mapMy[4], 40);
}
