#include <gtest/gtest.h>

#include "tests.h"

TEST(TestMap, Subtest_Constructor_1) {
  // Arrange
  s21::Map<std::string, int> a;
  std::map<std::string, int> b;
  // Act

  // Assert
  ASSERT_TRUE(a.empty());
  ASSERT_EQ(a.size(), 0);
  // ASSERT_EQ(b.max_size(), a.max_size());
}

TEST(TestMap, Subtest_Constructor_2) {
  // Arrange
  s21::Map<std::string, int> a{{"age", 18}, {"height", 180}};
  // Act

  // Assert
  ASSERT_FALSE(a.empty());
  ASSERT_EQ(a.size(), 2);
}

TEST(TestMap, Subtest_Constructor_3) {
  // Arrange
  s21::Map<std::string, int> a{{"age", 18}, {"height", 180}};
  s21::Map<std::string, int> b(a);
  auto it = a.begin();
  // Act

  // Assert
  ASSERT_FALSE(a.empty());
  ASSERT_EQ(a.size(), 2);
  ASSERT_EQ(it->first, "age");
  ASSERT_EQ((++it)->first, "height");
}

TEST(TestMap, Subtest_Constructor_4) {
  // Arrange
  s21::Map<std::string, int> a{{"age", 18}, {"height", 180}};
  s21::Map<std::string, int> b(std::move(a));
  auto it = b.begin();
  // Act

  // Assert
  ASSERT_TRUE(a.empty());
  ASSERT_EQ(b.size(), 2);
  ASSERT_EQ(it->first, "age");
  ASSERT_EQ((++it)->first, "height");
}

TEST(TestMap, Subtest_Operator_1) {
  // Arrange
  s21::Map<std::string, int> a{{"age", 18}, {"height", 180}};
  s21::Map<std::string, int> b = a;
  auto it = b.begin();
  // Act

  // Assert
  ASSERT_FALSE(a.empty());
  ASSERT_EQ(b.size(), 2);
  ASSERT_EQ(it->first, "age");
  ASSERT_EQ((++it)->first, "height");
}

TEST(TestMap, Subtest_At_1) {
  // Arrange
  s21::Map<std::string, int> a{{"age", 18}, {"height", 180}};
  // Act

  // Assert
  ASSERT_EQ(a.at("age"), 18);
  ASSERT_EQ(a.at("height"), 180);
}

TEST(TestMap, Subtest_At_2) {
  // Arrange
  s21::Map<std::string, int> a{{"age", 18}, {"height", 180}};
  // Act

  // Assert
  ASSERT_THROW(a.at("size"), std::out_of_range);
}

TEST(TestMap, Subtest_Operator_At_1) {
  // Arrange
  s21::Map<std::string, int> a{{"age", 18}, {"height", 180}};
  // Act
  a["weight"] = 80;

  // Assert
  ASSERT_EQ(a["age"], 18);
  ASSERT_EQ(a["height"], 180);
  ASSERT_EQ(a["weight"], 80);
}

TEST(TestMap, Subtest_Operator_At_2) {
  // Arrange
  s21::Map<std::string, int> a{{"age", 18}, {"height", 180}};
  // Act
  a["weight"];

  // Assert
  ASSERT_EQ(a["age"], 18);
  ASSERT_EQ(a["height"], 180);
  ASSERT_EQ(a["weight"], 0);
}

TEST(TestMap, Subtest_Insert_1) {
  // Arrange
  s21::Map<std::string, int> a{{"age", 18}, {"height", 180}};
  // Act
  auto result = a.insert({"weight", 80});

  // Assert
  ASSERT_EQ(a["age"], 18);
  ASSERT_EQ(a["height"], 180);
  ASSERT_EQ(a["weight"], 80);
  ASSERT_EQ(result.first->first, "weight");
  ASSERT_EQ(result.second, true);
}

TEST(TestMap, Subtest_Insert_2) {
  // Arrange
  s21::Map<std::string, int> a{{"age", 18}, {"height", 180}};

  // Act
  auto result = a.insert({"height", 100});

  // Assert
  ASSERT_EQ(a.size(), 2);
  ASSERT_EQ(a["age"], 18);
  ASSERT_EQ(a["height"], 180);
  ASSERT_EQ(result.first->first, "height");
  ASSERT_EQ(result.second, false);
}

TEST(TestMap, Subtest_Insert_3) {
  // Arrange
  s21::Map<std::string, int> a{{"age", 18}, {"height", 180}};

  // Act
  auto result = a.insert("weight", 80);

  // Assert
  ASSERT_EQ(a.size(), 3);
  ASSERT_EQ(a["age"], 18);
  ASSERT_EQ(a["height"], 180);
  ASSERT_EQ(a["weight"], 80);
  ASSERT_EQ(result.first->first, "weight");
  ASSERT_EQ(result.second, true);
}

TEST(TestMap, Subtest_Insert_4) {
  // Arrange
  s21::Map<std::string, int> a{{"age", 18}, {"height", 180}};

  // Act
  auto result = a.insert("height", 80);

  // Assert
  ASSERT_EQ(a.size(), 2);
  ASSERT_EQ(a["age"], 18);
  ASSERT_EQ(a["height"], 180);
  ASSERT_EQ(result.first->first, "height");
  ASSERT_EQ(result.second, false);
}

TEST(TestMap, Subtest_Insert_Or_Assign_1) {
  // Arrange
  s21::Map<std::string, int> a{{"age", 18}, {"height", 180}};

  // Act
  auto result = a.insert_or_assign("height", 80);

  // Assert
  ASSERT_EQ(a.size(), 2);
  ASSERT_EQ(a["age"], 18);
  ASSERT_EQ(a["height"], 80);
  ASSERT_EQ(result.first->first, "height");
  ASSERT_EQ(result.second, false);
}

TEST(TestMap, Subtest_Insert_Or_Assign_2) {
  // Arrange
  s21::Map<std::string, int> a{{"age", 18}, {"height", 180}};

  // Act
  auto result = a.insert_or_assign("weight", 80);

  // Assert
  ASSERT_EQ(a.size(), 3);
  ASSERT_EQ(a["age"], 18);
  ASSERT_EQ(a["height"], 180);
  ASSERT_EQ(a["weight"], 80);
  ASSERT_EQ(result.first->first, "weight");
  ASSERT_EQ(result.second, true);
}

TEST(TestMap, Subtest_Erase_1) {
  // Arrange
  s21::Map<std::string, int> a{{"age", 18}, {"height", 180}, {"weight", 80}};
  auto it = a.begin();

  // Act
  // it++;
  a.erase(it);

  // Assert
  ASSERT_EQ(a.size(), 2);
  ASSERT_THROW(a.at("age"), std::out_of_range);
}

TEST(TestMap, Subtest_Erase_2) {
  // Arrange
  s21::Map<std::string, int> a{{"age", 18}, {"height", 180}, {"weight", 80}};
  auto it = a.begin();

  // Act
  it++;
  a.erase(it);

  // Assert
  ASSERT_EQ(a.size(), 2);
  ASSERT_THROW(a.at("height"), std::out_of_range);
}

TEST(TestMap, Subtest_Swap_1) {
  // Arrange
  s21::Map<std::string, int> a{{"age", 18}, {"height", 180}, {"weight", 80}};
  s21::Map<std::string, int> b{{"age", 28}, {"height", 176}};

  // Act
  a.swap(b);

  // Assert
  ASSERT_EQ(a.size(), 2);
  ASSERT_EQ(b.size(), 3);
  ASSERT_EQ(a.at("height"), 176);
  ASSERT_EQ(b.at("height"), 180);
}

TEST(TestMap, Subtest_Merge_1) {
  // Arrange
  s21::Map<std::string, int> a{{"age", 18}, {"height", 180}, {"weight", 80}};
  s21::Map<std::string, int> b{{"depth", 10}, {"quality", 80}, {"height", 176}};

  // Act
  a.merge(b);

  // Assert
  ASSERT_EQ(a.size(), 5);
  ASSERT_EQ(b.size(), 1);
  ASSERT_EQ(a.at("height"), 180);
  ASSERT_EQ(a.at("depth"), 10);
  ASSERT_EQ(b.at("height"), 176);
}

TEST(TestMap, Subtest_Contains_1) {
  // Arrange
  s21::Map<std::string, int> a{{"age", 18}, {"height", 180}, {"weight", 80}};

  // Act

  // Assert
  ASSERT_EQ(a.size(), 3);
  ASSERT_TRUE(a.contains("height"));
  ASSERT_FALSE(a.contains("depth"));
  ASSERT_TRUE(a.contains("age"));
}

TEST(TestMap, InsertManyMap) {
  s21::Map<int, int> my_map = {{1, 2}, {3, 4}, {4, 15}, {5, 10}};
  s21::Map<int, int> reference_Map = {
      {1, 2}, {3, 4}, {4, 15}, {5, 10}, {10, 3},
  };

  s21::Vector vc = my_map.insert_many(std::pair<int, int>(10, 3),
                                      std::pair<int, int>(4, 20));

  auto my_it = my_map.begin();
  auto reference_it = reference_Map.begin();
  for (; my_it != my_map.end(); ++my_it, ++reference_it) {
    ASSERT_TRUE(*reference_it == *my_it);
  }
}