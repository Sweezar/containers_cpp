#include "tests.h"

TEST(Test_Tree, Subtest_Constructor_1) {
  // Arrange
  s21::Tree<int, int> a;

  // Act

  // Assert
  ASSERT_EQ(a.size(), 0);
  ASSERT_TRUE(a.empty());
}

TEST(Test_Tree, Subtest_Constructor_2) {
  // Arrange
  s21::Tree<int, int> a({2, 2});
  s21::Tree<int, int>::iterator it = a.begin();
  // Act

  // Assert
  ASSERT_EQ(a.size(), 1);
  ASSERT_FALSE(a.empty());
  ASSERT_EQ((*it), 2);
}

TEST(Test_Tree, Subtest_Constructor_3) {
  // Arrange
  s21::Tree<int, int> a{{2, 2}, {3, 3}};
  s21::Tree<int, int>::iterator it = a.begin();

  // Act

  // Assert
  ASSERT_EQ(a.size(), 2);
  ASSERT_FALSE(a.empty());
  ASSERT_EQ((*it++), 2);
  ASSERT_EQ((*it), 3);
}

TEST(Test_Tree, Subtest_Constructor_4) {
  // Arrange
  s21::Tree<int, int> a{{2, 2}, {3, 3}};
  s21::Tree<int, int> b(a);
  auto it = b.begin();

  // Act

  // Assert
  ASSERT_EQ(a.size(), 2);
  ASSERT_FALSE(a.empty());
  ASSERT_EQ(b.size(), 2);
  ASSERT_FALSE(b.empty());
  ASSERT_EQ((*it++), 2);
  ASSERT_EQ((*it), 3);
}

TEST(Test_Tree, Subtest_Constructor_5) {
  // Arrange
  s21::Tree<int, int> a{{2, 2}, {3, 3}};
  s21::Tree<int, int> b(std::move(a));
  auto it = b.begin();

  // Act

  // Assert
  ASSERT_EQ(a.size(), 0);
  ASSERT_TRUE(a.empty());
  ASSERT_EQ(b.size(), 2);
  ASSERT_FALSE(b.empty());
  ASSERT_EQ((*it++), 2);
  ASSERT_EQ((*it), 3);
}