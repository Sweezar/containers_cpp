#include "tests.h"

TEST(TestQueue, Subtest_Constructor_1) {
  // Arrange
  s21::Queue<int> a;

  // Act

  // Assert
  ASSERT_TRUE(a.empty());
  ASSERT_EQ(a.size(), 0);
}

TEST(TestQueue, Subtest_Constructor_2) {
  // Arrange
  s21::Queue<double> a;

  // Act

  // Assert
  ASSERT_TRUE(a.empty());
  ASSERT_EQ(a.size(), 0);
}

TEST(TestQueue, Subtest_Constructor_3) {
  // Arrange
  s21::Queue<int> a{1, 2, 3, 4};

  // Act

  // Assert
  ASSERT_FALSE(a.empty());
  ASSERT_EQ(a.front(), 1);
  ASSERT_EQ(a.back(), 4);
  ASSERT_EQ(a.size(), 4);
}

TEST(TestQueue, Subtest_Constructor_4) {
  // Arrange
  s21::Queue<int> a{1, 2, 3, 4};
  s21::Queue<int> b(a);

  // Act

  // Assert
  ASSERT_FALSE(b.empty());
  ASSERT_EQ(b.front(), 1);
  ASSERT_EQ(b.back(), 4);
  ASSERT_EQ(b.size(), 4);
}

TEST(TestQueue, Subtest_Constructor_5) {
  // Arrange
  s21::Queue<int> a{1, 2, 3, 4};
  s21::Queue<int> b(std::move(a));

  // Act

  // Assert
  ASSERT_TRUE(a.empty());
  ASSERT_FALSE(b.empty());
  ASSERT_EQ(b.front(), 1);
  ASSERT_EQ(b.back(), 4);
  ASSERT_EQ(b.size(), 4);
}

TEST(TestQueue, Subtest_Assignment_Operator_1) {
  // Arrange
  s21::Queue<int> a{1, 2, 3, 4};
  s21::Queue<int> b;

  // Act
  b = a;

  // Assert
  ASSERT_FALSE(a.empty());
  ASSERT_FALSE(b.empty());
  ASSERT_EQ(a.front(), 1);
  ASSERT_EQ(a.back(), 4);
  ASSERT_EQ(a.size(), 4);
  ASSERT_EQ(b.front(), 1);
  ASSERT_EQ(b.back(), 4);
  ASSERT_EQ(b.size(), 4);
}

TEST(TestQueue, Subtest_Assignment_Operator_2) {
  // Arrange
  s21::Queue<int> a{1, 2, 3, 4};
  s21::Queue<int> b{1};

  // Act
  b = a;

  // Assert
  ASSERT_FALSE(a.empty());
  ASSERT_FALSE(b.empty());
  ASSERT_EQ(a.front(), 1);
  ASSERT_EQ(a.back(), 4);
  ASSERT_EQ(a.size(), 4);
  ASSERT_EQ(b.front(), 1);
  ASSERT_EQ(b.back(), 4);
  ASSERT_EQ(b.size(), 4);
}

TEST(TestQueue, Subtest_Push_1) {
  // Arrange
  s21::Queue<int> a;
  int num = 4;

  // Act
  a.push(num);

  // Assert
  ASSERT_EQ(a.front(), num);
  ASSERT_EQ(a.back(), num);
  ASSERT_EQ(a.size(), 1);
  ASSERT_FALSE(a.empty());
}

TEST(TestQueue, Subtest_Push_2) {
  // Arrange
  s21::Queue<int> a;
  int num1 = 4;
  int num2 = 10;

  // Act
  a.push(num1);
  a.push(num2);

  // Assert
  ASSERT_EQ(a.front(), num1);
  ASSERT_EQ(a.back(), num2);
  ASSERT_EQ(a.size(), 2);
}

TEST(TestQueue, Subtest_Push_3) {
  // Arrange
  s21::Queue<int> a{1};
  int num = 4;

  // Act
  a.push(num);

  // Assert
  ASSERT_EQ(a.back(), num);
  ASSERT_EQ(a.size(), 2);
}

TEST(TestQueue, Subtest_Pop_Back_1) {
  // Arrange
  s21::Queue<int> a{1, 2, 3};

  // Act
  a.pop();

  // Assert
  ASSERT_EQ(a.front(), 2);
  ASSERT_EQ(a.back(), 3);
  ASSERT_EQ(a.size(), 2);
}

TEST(TestQueue, Subtest_Pop_Back_2) {
  // Arrange
  s21::Queue<int> a{1, 2, 3};

  // Act
  a.pop();
  a.pop();
  a.pop();

  // Assert
  ASSERT_EQ(a.front(), 0);
  ASSERT_EQ(a.back(), 0);
  ASSERT_EQ(a.size(), 0);
}

TEST(TestQueue, Subtest_Swap_1) {
  // Arrange
  s21::Queue<int> a{4};
  s21::Queue<int> b{1};

  // Act
  a.swap(b);

  // Assert
  ASSERT_EQ(a.size(), 1);
  ASSERT_EQ(a.front(), 1);
  ASSERT_EQ(b.size(), 1);
  ASSERT_EQ(b.front(), 4);
}

TEST(TestQueue, Subtest_Swap_2) {
  // Arrange
  s21::Queue<int> a{4, 5, 6};
  s21::Queue<int> b{1, 2, 3};

  // Act
  a.swap(b);

  // Assert
  ASSERT_EQ(a.size(), 3);
  ASSERT_EQ(a.front(), 1);
  ASSERT_EQ(a.back(), 3);
  ASSERT_EQ(b.size(), 3);
  ASSERT_EQ(b.front(), 4);
  ASSERT_EQ(b.back(), 6);
}

TEST(TestQueue, Subtest_Swap_3) {
  // Arrange
  s21::Queue<int> a{4, 5, 6, 7};
  s21::Queue<int> b{1, 2};

  // Act
  a.swap(b);

  // Assert
  ASSERT_EQ(a.size(), 2);
  ASSERT_EQ(a.front(), 1);
  ASSERT_EQ(a.back(), 2);
  ASSERT_EQ(b.size(), 4);
  ASSERT_EQ(b.front(), 4);
  ASSERT_EQ(b.back(), 7);
}

TEST(TestQueue, Subtest_Swap_4) {
  // Arrange
  s21::Queue<int> a{4, 5, 6, 7};
  s21::Queue<int> b;

  // Act
  a.swap(b);

  // Assert
  ASSERT_EQ(a.size(), 0);
  ASSERT_EQ(a.front(), 0);
  ASSERT_EQ(a.back(), 0);
  ASSERT_EQ(b.size(), 4);
  ASSERT_EQ(b.front(), 4);
  ASSERT_EQ(b.back(), 7);
}

TEST(TestQueue, Subtest_Insert_Many_Back_1) {
  // Arrange
  s21::Queue<int> a{1};

  // Act
  a.insert_many_back(3, 4, 8, 9);

  // Assert
  ASSERT_EQ(a.front(), 1);
  ASSERT_EQ(a.back(), 9);
}

TEST(TestQueue, Subtest_Insert_Many_Back_2) {
  // Arrange
  s21::Queue<int> a{1};

  // Act
  a.insert_many_back(3);

  // Assert
  ASSERT_EQ(a.front(), 1);
  ASSERT_EQ(a.back(), 3);
}

TEST(TestQueue, Subtest_Insert_Many_Back_3) {
  // Arrange
  s21::Queue<int> a{1};

  // Act
  a.insert_many_back();

  // Assert
  ASSERT_EQ(a.front(), 1);
}
