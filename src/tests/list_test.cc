#include <gtest/gtest.h>

#include "tests.h"

TEST(List, Subtest_Constructor_1) {
  // Arrange
  s21::List<int> a;

  // Act

  // Assert
  ASSERT_TRUE(a.empty());
  ASSERT_EQ(a.size(), 0);
  ASSERT_EQ(a.max_size(), MAX_LIST_SIZE);
}

TEST(List, Subtest_Constructor_2) {
  // Arrange
  s21::List<int> a(10);

  // Act

  // Assert
  ASSERT_TRUE(a.empty());
  ASSERT_EQ(a.size(), 0);
  ASSERT_EQ(a.max_size(), 10);
}

TEST(List, Subtest_Constructor_3) {
  // Arrange
  s21::List<double> a(10);

  // Act

  // Assert
  ASSERT_TRUE(a.empty());
  ASSERT_EQ(a.size(), 0);
  ASSERT_EQ(a.max_size(), 10);
}

TEST(List, Subtest_Constructor_4) {
  // Arrange
  s21::List<int> a{1, 2, 3, 4};

  // Act

  // Assert
  ASSERT_FALSE(a.empty());
  ASSERT_EQ(a.front(), 1);
  ASSERT_EQ(a.back(), 4);
  ASSERT_EQ(a.size(), 4);
}

TEST(List, Subtest_Constructor_5) {
  // Arrange
  s21::List<int> a{1, 2, 3, 4};
  s21::List<int> b(a);

  // Act

  // Assert
  ASSERT_FALSE(b.empty());
  ASSERT_EQ(b.front(), 1);
  ASSERT_EQ(b.back(), 4);
  ASSERT_EQ(b.size(), 4);
}

TEST(List, Subtest_Constructor_6) {
  // Arrange
  s21::List<int> a{1, 2, 3, 4};
  s21::List<int> b(std::move(a));

  // Act

  // Assert
  ASSERT_TRUE(a.empty());
  ASSERT_FALSE(b.empty());
  ASSERT_EQ(b.front(), 1);
  ASSERT_EQ(b.back(), 4);
  ASSERT_EQ(b.size(), 4);
}

TEST(List, Subtest_Assignment_Operator_1) {
  // Arrange
  s21::List<int> a{1, 2, 3, 4};
  s21::List<int> b;

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

TEST(List, Subtest_Assignment_Operator_2) {
  // Arrange
  s21::List<int> a{1, 2, 3, 4};
  s21::List<int> b{1};

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

TEST(List, Subtest_Push_Back_1) {
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

TEST(List, Subtest_Push_Back_2) {
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

TEST(List, Subtest_Push_Front_1) {
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

TEST(List, Subtest_Push_Front_2) {
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

TEST(List, Subtest_Pop_Back_1) {
  // Arrange
  s21::List<int> a;
  // std::list<int> b;
  int num = 4;

  // Act
  a.push_back(num);
  a.pop_back();

  // Assert
  ASSERT_EQ(a.front(), 0);
  ASSERT_EQ(a.back(), 0);
  ASSERT_EQ(a.size(), 0);
}

TEST(List, Subtest_Pop_Back_2) {
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

TEST(List, Subtest_Pop_Front_1) {
  // Arrange
  s21::List<int> a;
  // std::list<int> b;
  int num = 4;

  // Act
  a.push_back(num);
  a.pop_front();

  // Assert
  ASSERT_EQ(a.front(), 0);
  ASSERT_EQ(a.back(), 0);
  ASSERT_EQ(a.size(), 0);
}

TEST(List, Subtest_Pop_Front_2) {
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

TEST(List, Subtest_Insert_1) {
  // Arrange
  s21::List<int> a;
  s21::List<int>::iterator it = a.begin();
  int num = 14;

  // Act
  it = a.insert(it, num);

  // Assert
  ASSERT_EQ(a.size(), 1);
  ASSERT_EQ(*it, num);
}

TEST(List, Subtest_Insert_2) {
  // Arrange
  s21::List<int> a{4, 10, 20};
  s21::List<int>::iterator it = a.begin();
  int num = 14;

  // Act
  ++it;
  ++it;
  it = a.insert(it, num);

  // Assert
  ASSERT_EQ(a.size(), 4);
  ASSERT_EQ(*it, num);
}

TEST(List, Subtest_Insert_3) {
  // Arrange
  s21::List<int> a{4, 10, 20};
  s21::List<int>::iterator it = a.begin();
  int num = 14;

  // Act
  ++it;
  it = a.insert(it, num);

  // Assert
  ASSERT_EQ(a.size(), 4);
  ASSERT_EQ(*it, num);
}

TEST(List, Subtest_Erase_1) {
  // Arrange
  s21::List<int> a{4, 10, 20};
  s21::List<int>::iterator it = a.begin();

  // Act
  ++it;
  ++it;
  a.erase(it);

  // Assert
  ASSERT_EQ(a.size(), 2);
  ASSERT_EQ(a.front(), 4);
  ASSERT_EQ(a.back(), 10);
}

TEST(List, Subtest_Erase_2) {
  // Arrange
  s21::List<int> a{4, 10, 20};
  s21::List<int>::iterator it = a.begin();

  // Act
  a.erase(it);

  // Assert
  ASSERT_EQ(a.size(), 2);
  ASSERT_EQ(a.front(), 10);
  ASSERT_EQ(a.back(), 20);
}

TEST(List, Subtest_Erase_3) {
  // Arrange
  s21::List<int> a{4};
  s21::List<int>::iterator it = a.begin();

  // Act
  a.erase(it);

  // Assert
  ASSERT_TRUE(a.empty());
  ASSERT_EQ(a.size(), 0);
  ASSERT_EQ(a.front(), 0);
  ASSERT_EQ(a.back(), 0);
}

TEST(List, Subtest_Swap_1) {
  // Arrange
  s21::List<int> a{4};
  s21::List<int> b{1};

  // Act
  a.swap(b);

  // Assert
  ASSERT_EQ(a.size(), 1);
  ASSERT_EQ(a.front(), 1);
  ASSERT_EQ(b.size(), 1);
  ASSERT_EQ(b.front(), 4);
}

TEST(List, Subtest_Swap_2) {
  // Arrange
  s21::List<int> a{4, 5, 6};
  s21::List<int> b{1, 2, 3};

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

TEST(List, Subtest_Swap_3) {
  // Arrange
  s21::List<int> a{4, 5, 6, 7};
  s21::List<int> b{1, 2};

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

TEST(List, Subtest_Swap_4) {
  // Arrange
  s21::List<int> a{4, 5, 6, 7};
  s21::List<int> b;

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

TEST(List, Subtest_Merge_1) {
  // Arrange
  s21::List<int> a;
  s21::List<int> b{1, 2, 3};

  // Act
  a.merge(b);

  // Assert
  ASSERT_TRUE(b.empty());
  ASSERT_EQ(a.front(), 1);
  ASSERT_EQ(a.back(), 3);
  ASSERT_EQ(a.size(), 3);
}

TEST(List, Subtest_Merge_2) {
  // Arrange
  s21::List<int> a{2, 3, 6};
  s21::List<int> b;

  // Act
  a.merge(b);

  // Assert
  ASSERT_TRUE(b.empty());
  ASSERT_EQ(a.front(), 2);
  ASSERT_EQ(a.back(), 6);
  ASSERT_EQ(a.size(), 3);
}

TEST(List, Subtest_Merge_3) {
  // Arrange
  s21::List<int> a{1, 7};
  s21::List<int> b{2, 3, 6};

  // Act
  a.merge(b);

  // Assert
  ASSERT_TRUE(b.empty());
  ASSERT_EQ(a.front(), 1);
  ASSERT_EQ(a.back(), 7);
  ASSERT_EQ(a.size(), 5);
}

TEST(List, Subtest_Merge_4) {
  // Arrange
  s21::List<int> a{2, 3, 6};
  s21::List<int> b{1, 4, 12};

  // Act
  a.merge(b);

  // Assert
  ASSERT_TRUE(b.empty());
  ASSERT_EQ(a.front(), 1);
  ASSERT_EQ(a.back(), 12);
  ASSERT_EQ(a.size(), 6);
}

TEST(List, Subtest_Merge_5) {
  // Arrange
  s21::List<int> a{5, 6, 10};
  s21::List<int> b{1, 4, 12};
  // Act
  a.merge(b);

  // Assert
  ASSERT_EQ(a.front(), 1);
  ASSERT_EQ(a.back(), 12);
  ASSERT_EQ(a.size(), 6);
  ASSERT_TRUE(b.empty());
}

TEST(List, Subtest_Merge_6) {
  // Arrange
  s21::List<int> a{1, 4, 12};
  s21::List<int> b{5, 6, 10};

  // Act
  a.merge(b);

  // Assert
  ASSERT_EQ(a.front(), 1);
  ASSERT_EQ(a.back(), 12);
  ASSERT_EQ(a.size(), 6);
  ASSERT_TRUE(b.empty());
}

TEST(List, Subtest_Splice_1) {
  // Arrange
  s21::List<int> a{7, 8};
  s21::List<int> b{2, 3, 4, 5};
  s21::List<int>::iterator it = a.begin();

  // Act
  a.splice(it, b);

  // Assert
  ASSERT_EQ(a.front(), 2);
  ASSERT_EQ(a.back(), 8);
  ASSERT_EQ(a.size(), 6);
  ASSERT_TRUE(b.empty());
}

TEST(List, Subtest_Splice_2) {
  // Arrange
  s21::List<int> a{7, 8};
  s21::List<int> b{2, 3, 4, 5};
  s21::List<int>::iterator it = a.begin();

  // Act
  it++;
  a.splice(it, b);

  // Assert
  ASSERT_EQ(a.front(), 7);
  ASSERT_EQ(a.back(), 8);
  ASSERT_EQ(a.size(), 6);
  ASSERT_TRUE(b.empty());
}

TEST(List, Subtest_Splice_3) {
  // Arrange
  s21::List<int> a{7};
  s21::List<int> b{2, 3, 4, 5};
  s21::List<int>::iterator it = a.begin();

  // Act
  it++;
  a.splice(it, b);

  // Assert
  ASSERT_EQ(a.front(), 7);
  ASSERT_EQ(a.back(), 5);
  ASSERT_EQ(a.size(), 5);
  ASSERT_TRUE(b.empty());
}

TEST(List, Subtest_Splice_4) {
  // Arrange
  s21::List<int> a;
  s21::List<int> b{2, 3, 4, 5};
  s21::List<int>::iterator it = a.begin();

  // Act
  it++;
  a.splice(it, b);

  // Assert
  ASSERT_EQ(a.front(), 2);
  ASSERT_EQ(a.back(), 5);
  ASSERT_EQ(a.size(), 4);
  ASSERT_TRUE(b.empty());
}

TEST(List, Subtest_Reverse_1) {
  // Arrange
  s21::List<int> a{2, 3, 4, 5};

  // Act
  a.reverse();
  s21::List<int>::iterator it = a.begin();

  // Assert
  ASSERT_EQ(a.front(), 5);
  ASSERT_EQ(*++it, 4);
  ASSERT_EQ(*++it, 3);
  ASSERT_EQ(a.back(), 2);
  ASSERT_EQ(a.size(), 4);
}

TEST(List, Subtest_Unique_1) {
  // Arrange
  s21::List<int> a{2, 3, 4, 5};

  // Act
  a.unique();
  s21::List<int>::iterator it = a.begin();

  // Assert
  ASSERT_EQ(a.front(), 2);
  ASSERT_EQ(*++it, 3);
  ASSERT_EQ(*++it, 4);
  ASSERT_EQ(a.back(), 5);
  ASSERT_EQ(a.size(), 4);
}

TEST(List, Subtest_Unique_2) {
  // Arrange
  s21::List<int> a{2, 3, 4, 2, 3, 4};

  // Act
  a.unique();
  s21::List<int>::iterator it = a.begin();

  // Assert
  ASSERT_EQ(a.front(), 2);
  ASSERT_EQ(*++it, 3);
  ASSERT_EQ(*++it, 4);
  ASSERT_EQ(*++it, 2);
  ASSERT_EQ(*++it, 3);
  ASSERT_EQ(a.back(), 4);
  ASSERT_EQ(a.size(), 6);
}

TEST(List, Subtest_Unique_3) {
  // Arrange
  s21::List<int> a{2, 2, 3, 3, 4, 4, 4};

  // Act
  a.unique();
  s21::List<int>::iterator it = a.begin();

  // Assert
  ASSERT_EQ(a.front(), 2);
  ASSERT_EQ(*++it, 3);
  ASSERT_EQ(a.back(), 4);
  ASSERT_EQ(a.size(), 3);
}

TEST(List, Subtest_Sort_1) {
  // Arrange
  s21::List<int> a{10, 4, 5, 8, 6, 7, 2};

  // Act
  a.sort();
  s21::List<int>::iterator it = a.begin();

  // Assert
  ASSERT_EQ(*it++, 2);
  ASSERT_EQ(*it++, 4);
  ASSERT_EQ(*it++, 5);
  ASSERT_EQ(*it++, 6);
  ASSERT_EQ(*it++, 7);
  ASSERT_EQ(*it++, 8);
  ASSERT_EQ(*it, 10);
}

TEST(List, Subtest_Sort_2) {
  // Arrange
  s21::List<int> a{10, 4};

  // Act
  a.sort();
  s21::List<int>::iterator it = a.begin();

  // Assert
  ASSERT_EQ(*it++, 4);
  ASSERT_EQ(*it, 10);
}

TEST(List, Subtest_Sort_3) {
  // Arrange
  s21::List<int> a{4};

  // Act
  a.sort();
  s21::List<int>::iterator it = a.begin();

  // Assert
  ASSERT_EQ(*it, 4);
}

TEST(List, Subtest_Sort_4) {
  // Arrange
  s21::List<int> a{2, 1, 2, 2, 1, 1};

  // Act
  a.sort();
  s21::List<int>::iterator it = a.begin();

  // Assert
  ASSERT_EQ(*it++, 1);
  ASSERT_EQ(*it++, 1);
  ASSERT_EQ(*it++, 1);
  ASSERT_EQ(*it++, 2);
  ASSERT_EQ(*it++, 2);
  ASSERT_EQ(*it, 2);
}

TEST(TestList, Subtest_Insert_Many_1) {
  // Arrange
  s21::List<int> a{2, 1, 2, 2, 1, 1};
  s21::List<int>::iterator it = a.begin();

  // Act
  ++it;
  a.insert_many(it, 3, 4);

  // Assert
  ASSERT_EQ(*it, 1);
  ASSERT_EQ(*--it, 4);
  ASSERT_EQ(*--it, 3);
  ASSERT_EQ(*--it, 2);
}

TEST(TestList, Subtest_Insert_Many_2) {
  // Arrange
  s21::List<int> a{2, 1, 2, 2, 1, 1};
  s21::List<int>::iterator it = a.begin();

  // Act
  ++it;
  a.insert_many(it, 3, 4, 8, 9);

  // Assert
  ASSERT_EQ(*it, 1);
  ASSERT_EQ(*--it, 9);
  ASSERT_EQ(*--it, 8);
  ASSERT_EQ(*--it, 4);
  ASSERT_EQ(*--it, 3);
  ASSERT_EQ(*--it, 2);
}

TEST(TestList, Subtest_Insert_Many_3) {
  // Arrange
  s21::List<int> a{2, 1, 2, 2, 1, 1};
  s21::List<int>::iterator it = a.begin();

  // Act
  a.insert_many(it);

  // Assert
  ASSERT_EQ(*it, 2);
}

TEST(TestList, Subtest_Insert_Many_Back_1) {
  // Arrange
  s21::List<int> a{1};
  s21::List<int>::iterator it = a.begin();

  // Act
  a.insert_many_back(3, 4, 8, 9);

  // Assert
  ASSERT_EQ(*it, 1);
  ASSERT_EQ(*++it, 3);
  ASSERT_EQ(*++it, 4);
  ASSERT_EQ(*++it, 8);
  ASSERT_EQ(*++it, 9);
}

TEST(TestList, Subtest_Insert_Many_Back_2) {
  // Arrange
  s21::List<int> a{1};
  s21::List<int>::iterator it = a.begin();

  // Act
  a.insert_many_back(3);

  // Assert
  ASSERT_EQ(*it, 1);
  ASSERT_EQ(*++it, 3);
}

TEST(TestList, Subtest_Insert_Many_Back_3) {
  // Arrange
  s21::List<int> a{1};

  // Act
  a.insert_many_back();

  // Assert
  ASSERT_EQ(a.front(), 1);
}

TEST(TestList, Subtest_Insert_Many_Front_1) {
  // Arrange
  s21::List<int> a{1};

  // Act
  a.insert_many_front(9, 8, 4, 3);
  s21::List<int>::iterator it = a.begin();

  // Assert
  ASSERT_EQ(*it, 9);
  ASSERT_EQ(*++it, 8);
  ASSERT_EQ(*++it, 4);
  ASSERT_EQ(*++it, 3);
  ASSERT_EQ(*++it, 1);
}

TEST(TestList, Subtest_Insert_Many_Front_2) {
  // Arrange
  s21::List<int> a{1};

  // Act
  a.insert_many_front(3);
  s21::List<int>::iterator it = a.begin();

  // Assert
  ASSERT_EQ(*it, 3);
  ASSERT_EQ(*++it, 1);
}

TEST(TestList, Subtest_Insert_Many_Front_3) {
  // Arrange
  s21::List<int> a{1};

  // Act
  a.insert_many_front();

  // Assert
  ASSERT_EQ(a.front(), 1);
}
