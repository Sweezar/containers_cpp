#include "../s21_list/list.h"
#include <list>
#include <gtest/gtest.h>

TEST(TestList, Subtest_Constructor_1) {
  // Arrange
  s21::List<int> a;

  // Act

  // Assert
  ASSERT_EQ(a.empty(), true);
  ASSERT_EQ(a.size(), 0);
  ASSERT_EQ(a.max_size(), MAX_LIST_SIZE);
}

TEST(TestList, Subtest_Constructor_2) {
  // Arrange
  s21::List<int> a(10);

  // Act

  // Assert
  ASSERT_EQ(a.empty(), true);
  ASSERT_EQ(a.size(), 0);
  ASSERT_EQ(a.max_size(), 10);
}

TEST(TestList, Subtest_Constructor_3) {
  // Arrange
  s21::List<double> a(10);

  // Act

  // Assert
  ASSERT_EQ(a.empty(), true);
  ASSERT_EQ(a.size(), 0);
  ASSERT_EQ(a.max_size(), 10);
}

TEST(TestList, Subtest_Constructor_4) {
  // Arrange
  s21::List<int> a{1,2,3,4};

  // Act

  // Assert
  
}

TEST(TestList, Subtest_Push_Back_1) {
  // Arrange
  s21::List<int> a;
  int num = 4;

  // Act
    a.push_back(num);

  // Assert
  ASSERT_EQ(a.front(), num);
  ASSERT_EQ(a.back(), num);
  ASSERT_EQ(a.size(), 1);
  ASSERT_FALSE(a.empty());
}

TEST(TestList, Subtest_Push_Back_2) {
  // Arrange
  s21::List<int> a;
  int num1 = 4;
  int num2 = 10;

  // Act
    a.push_back(num1);
    a.push_back(num2);

  // Assert
  ASSERT_EQ(a.front(), num1);
  ASSERT_EQ(a.back(), num2);
  ASSERT_EQ(a.size(), 2);
}

TEST(TestList, Subtest_Push_Front_1) {
  // Arrange
  s21::List<int> a;
  int num = 4;

  // Act
    a.push_front(num);

  // Assert
  ASSERT_EQ(a.front(), num);
  ASSERT_EQ(a.back(), num);
  ASSERT_EQ(a.size(), 1);
}

TEST(TestList, Subtest_Push_Front_2) {
  // Arrange
  s21::List<int> a;
  int num1 = 4;
  int num2 = 10;

  // Act
    a.push_front(num1);
    a.push_front(num2);

  // Assert
  ASSERT_EQ(a.front(), num2);
  ASSERT_EQ(a.back(), num1);
  ASSERT_EQ(a.size(), 2);
}

TEST(TestList, Subtest_Pop_Back_1) {
  // Arrange
  s21::List<int> a;
  std::list<int> b;
  int num = 4;

  // Act
    a.push_back(num);
    a.pop_back();

  // Assert
  ASSERT_EQ(a.front(), 0);
  ASSERT_EQ(a.back(), 0);
  ASSERT_EQ(a.size(), 0);
}

TEST(TestList, Subtest_Pop_Back_2) {
  // Arrange
  s21::List<int> a;
  int num1 = 4;
  int num2 = 10;

  // Act
    a.push_back(num1);
    a.push_back(num2);
    a.pop_back();

  // Assert
  ASSERT_EQ(a.front(), num1);
  ASSERT_EQ(a.back(), num1);
  ASSERT_EQ(a.size(), 1);
}

TEST(TestList, Subtest_Pop_Front_1) {
  // Arrange
  s21::List<int> a;
  std::list<int> b;
  int num = 4;

  // Act
    a.push_back(num);
    a.pop_front();

  // Assert
  ASSERT_EQ(a.front(), 0);
  ASSERT_EQ(a.back(), 0);
  ASSERT_EQ(a.size(), 0);
}

TEST(TestList, Subtest_Pop_Front_2) {
  // Arrange
  s21::List<int> a;
  int num1 = 4;
  int num2 = 10;

  // Act
    a.push_back(num1);
    a.push_back(num2);
    a.pop_front();

  // Assert
  ASSERT_EQ(a.front(), num2);
  ASSERT_EQ(a.back(), num2);
  ASSERT_EQ(a.size(), 1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
