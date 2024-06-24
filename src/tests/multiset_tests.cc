#include <gtest/gtest.h>

#include <iostream>

#include "tests.h"

TEST(Multiset, ConstructorDefaultMultiSet) {
  s21::Multiset<char> my_empty_multiset;
  std::multiset<char> orig_empty_multiset;
  ASSERT_EQ(my_empty_multiset.empty(), orig_empty_multiset.empty());
  ASSERT_EQ(my_empty_multiset.size(), orig_empty_multiset.size());
  // TODO: // ASSERT_EQ(my_empty_set.max_size(), orig_empty_set.max_size());
}

TEST(Multiset, ConstructorInitializerMultiset_1) {
  // Arrange
  s21::Multiset<int> a{1, 2, 3, 4};
  // Act
  // Assert
  ASSERT_FALSE(a.empty());
  ASSERT_EQ(a.size(), 4);
}

TEST(Multiset, ConstructorInitializerMultiset_2) {
  // Arrange
  s21::Multiset<int> a{1, 2, 3, 4, 1, 2};
  // Act
  // Assert
  ASSERT_FALSE(a.empty());
  ASSERT_EQ(a.size(), 6);
}

TEST(Multiset, ConstructorCopyMultiset) {
  // Arrange
  s21::Multiset<int> a{18, 180, 18};
  s21::Multiset<int> b(a);
  auto it = a.begin();
  // Act

  // Assert
  ASSERT_FALSE(a.empty());
  ASSERT_EQ(a.size(), 3);

  ASSERT_EQ(*it++, 18);
  ASSERT_EQ(*it++, 18);
  ASSERT_EQ(*it, 180);
}

TEST(Multiset, ConstructorMoveMultiset) {
  // Arrange
  s21::Multiset<int> a{18, 180, 18};
  s21::Multiset<int> b(std::move(a));
  auto it = b.begin();
  // Act

  // Assert
  ASSERT_TRUE(a.empty());
  ASSERT_EQ(b.size(), 3);
  ASSERT_EQ(*it++, 18);
  ASSERT_EQ(*it++, 18);
  ASSERT_EQ(*it, 180);
}

TEST(Multiset, ConstructorMoveMultiset2) {
  s21::Multiset<int> my_set = {1, 2, 3, 4, 5, 2, 4};
  std::multiset<int> orig_set = {1, 2, 3, 4, 5, 2, 4};
  s21::Multiset<int> my_set_copy = std::move(my_set);
  std::multiset<int> orig_set_copy = std::move(orig_set);
  ASSERT_EQ(my_set.size(), orig_set.size());
  ASSERT_EQ(my_set_copy.size(), orig_set_copy.size());
  auto my_it = my_set_copy.begin();
  auto orig_it = orig_set_copy.begin();
  for (; my_it != my_set_copy.end(); ++my_it, ++orig_it) {
    ASSERT_TRUE(*orig_it == *my_it);
  }
}

TEST(Multiset, IteratorsMultiset_1) {
  // s21::Set<std::string> my_set = {"This", "is", "my", "set"};
  // std::set<std::string> orig_set = {"This", "is", "my", "set"};
  s21::Multiset<int> my_set = {15, 1, 20, 3, 4, 7, 3, 15};
  std::multiset<int> orig_set = {15, 1, 20, 3, 4, 7, 3, 15};
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  // ASSERT_TRUE(*orig_it == *my_it);
  my_it = my_set.end();
  orig_it = orig_set.end();
  // orig_it++;
  ASSERT_EQ(*orig_it, *my_it);
  ASSERT_EQ(*--orig_it, *--my_it);
}

TEST(Multiset, IteratorsMultiset_2) {
  // s21::Set<std::string> my_set = {"This", "is", "my", "set"};
  // std::set<std::string> orig_set = {"This", "is", "my", "set"};
  s21::Set<int> my_set = {1, 2, 3, 4, 5, 1, 3, 5};
  std::set<int> orig_set = {1, 2, 3, 4, 5, 1, 3, 5};
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  ASSERT_TRUE(*orig_it == *my_it);
  my_it = my_set.end();
  orig_it = orig_set.end();
  my_it--;
  orig_it--;
  ASSERT_EQ(*orig_it, *my_it);
}

TEST(Multiset, IteratorsMultiset_3) {
  // s21::Set<std::string> my_set = {"This", "is", "my", "set"};
  // std::set<std::string> orig_set = {"This", "is", "my", "set"};
  s21::Multiset<int> my_set = {1, 2, 3, 4, 5, 1, 3, 5};
  std::multiset<int> orig_set = {1, 2, 3, 4, 5, 1, 3, 5};
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  ASSERT_TRUE(*orig_it == *my_it);
  ASSERT_EQ(*++orig_it, *++my_it);
}

TEST(Multiset, IteratorsMultiset_4) {
  // s21::Set<std::string> my_set = {"This", "is", "my", "set"};
  // std::set<std::string> orig_set = {"This", "is", "my", "set"};
  s21::Multiset<int> my_set = {1, 2, 3, 4, 5, 1, 3, 5};
  std::multiset<int> orig_set = {1, 2, 3, 4, 5, 1, 3, 5};
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  ASSERT_TRUE(*orig_it == *my_it);
  ASSERT_EQ(*orig_it++, *my_it++);
}

TEST(Multiset, ClearMultiset) {
  s21::Multiset<char> my_empty_set;
  std::multiset<char> orig_empty_set;
  my_empty_set.clear();
  orig_empty_set.clear();
  ASSERT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  ASSERT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.insert('a');
  orig_empty_set.insert('b');
  ASSERT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  ASSERT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.clear();
  orig_empty_set.clear();
  ASSERT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  ASSERT_EQ(my_empty_set.size(), orig_empty_set.size());
}

TEST(Multiset, InsertMultiset) {
  s21::Multiset<int> my_set = {5, 4, 3, 2, 7, 8, 9};
  std::multiset<int> orig_set = {5, 4, 3, 2, 7, 8, 9};
  auto my_pr = my_set.insert(7);
  auto orig_pr = orig_set.insert(7);
  ASSERT_TRUE(*my_pr == *orig_pr);
  my_pr = my_set.insert(111);
  orig_pr = orig_set.insert(111);
  ASSERT_EQ(*my_pr, *orig_pr);
}

TEST(Multiset, InsertMultiset2) {
  s21::Multiset<int> my_set;
  std::multiset<int> orig_set;
  auto my_pr = my_set.insert(5);
  auto orig_pr = orig_set.insert(5);
  ASSERT_TRUE(*my_pr == *orig_pr);
  my_pr = my_set.insert(5);
  orig_pr = orig_set.insert(5);
  ASSERT_TRUE(*my_pr == *orig_pr);
}

TEST(Multiset, EraseMultiset) {
  s21::Multiset<int> my_set = {5, 4, 3, 2, 5, 7, 8, 9};
  std::multiset<int> orig_set = {5, 4, 3, 2, 5, 7, 8, 9};
  auto size = my_set.size();
  auto new_size = my_set.size();
  ASSERT_EQ(size, new_size);
  my_set.erase(my_set.begin());
  orig_set.erase(orig_set.begin());
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    ASSERT_TRUE(*orig_it == *my_it);
  }
}

TEST(Multiset, SwapMultiset) {
  s21::Multiset<int> my_set = {1};
  s21::Multiset<int> my_swap_set = {3, 4, 5};

  my_set.swap(my_swap_set);
  ASSERT_EQ(my_set.size(), 3);
  ASSERT_EQ(my_swap_set.size(), 1);
  ASSERT_EQ(*my_set.begin(), 3);
  ASSERT_EQ(*my_swap_set.begin(), 1);
}

TEST(Multiset, MergeMultiset) {
  s21::Multiset<int> my_set = {1, 2, 3, 4, 5};
  s21::Multiset<int> my_merge_set = {3, 4, 5};

  my_set.merge(my_merge_set);

  std::multiset<int> orig_set = {1, 2, 3, 4, 5};
  std::multiset<int> orig_merge_set = {3, 4, 5};

  orig_set.merge(orig_merge_set);

  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    ASSERT_TRUE(*orig_it == *my_it);
  }
  ASSERT_EQ(orig_set.size(), my_set.size());
  ASSERT_EQ(my_merge_set.size(), orig_merge_set.size());
}

TEST(Multiset, Multiset_Count_1) {
  // Arrange
  s21::Multiset<int> my_set = {1, 1, 1, 1, 1, 1};

  // Act

  // Assert
  ASSERT_EQ(my_set.count(1), 6);
}

TEST(Multiset, Multiset_Count_2) {
  // Arrange
  s21::Multiset<int> my_set = {1, 2, 3, 1, 4, 1};

  // Act

  // Assert
  ASSERT_EQ(my_set.count(1), 3);
}

TEST(Multiset, FindMultiset) {
  s21::Multiset<double> my_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  std::multiset<double> orig_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  auto my_it = my_set.find(2.4);
  auto orig_it = orig_set.find(2.4);
  ASSERT_TRUE(*orig_it == *my_it);
}

TEST(Multiset, ContainsMultiset) {
  s21::Multiset<double> my_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  ASSERT_FALSE(my_set.contains(2));
  ASSERT_TRUE(my_set.contains(2.1));
}

TEST(Multiset, Multiset_Equal_Range_1) {
  // Arrange
  s21::Multiset<int> my_set = {1, 2, 3, 1, 4, 1};

  // Act
  auto result = my_set.equal_range(1);

  // Assert
  ASSERT_EQ(*(result.first), 1);
  ASSERT_EQ(*(result.second), 1);
  ASSERT_FALSE(result.first == result.second);
}

TEST(Multiset, Multiset_Lower_Bound_1) {
  // Arrange
  s21::Multiset<int> my_set = {1, 2, 3, 1, 4, 1};

  // Act
  auto result = my_set.lower_bound(3);

  // Assert
  ASSERT_EQ(*result, 3);
}

TEST(Multiset, Multiset_Lower_Bound_2) {
  // Arrange
  s21::Multiset<int> my_set = {1, 2, 3, 1, 4, 1, 4};

  // Act
  auto result = my_set.lower_bound(15);

  // Assert
  ASSERT_EQ(*result, 7);
}

TEST(Multiset, Multiset_Lower_Bound_3) {
  // Arrange
  s21::Multiset<int> my_set = {1, 2, 3, 1, 4, 1, 4};

  // Act
  auto result = my_set.lower_bound(-15);

  // Assert
  ASSERT_EQ(*result, 1);
}

TEST(Multiset, Multiset_Upper_Bound_1) {
  // Arrange
  s21::Multiset<int> my_set = {1, 2, 3, 1, 4, 1};

  // Act
  auto result = my_set.upper_bound(3);

  // Assert
  ASSERT_EQ(*result, 4);
}

TEST(Multiset, Multiset_Upper_Bound_2) {
  // Arrange
  s21::Multiset<int> my_set = {1, 2, 3, 1, 4, 1, 4};

  // Act
  auto result = my_set.upper_bound(15);

  // Assert
  ASSERT_EQ(*result, 7);
}

TEST(Multiset, Multiset_Upper_Bound_3) {
  // Arrange
  s21::Multiset<int> my_set = {1, 2, 3, 1, 4, 1, 4};

  // Act
  auto result = my_set.upper_bound(-15);

  // Assert
  ASSERT_EQ(*result, 1);
}

TEST(Multiset, Multiset_Insert_Many_1) {
  // Arrange
  s21::Multiset<int> my_set = {1, 2, 3, 4};

  // Act
  auto result = my_set.insert_many(1, 2, 4, 4);

  // Assert
  ASSERT_EQ(my_set.size(), 8);
  ASSERT_EQ(my_set.count(4), 3);
}