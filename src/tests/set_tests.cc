#include "tests.h"

TEST(Set, ConstructorDefaultSet) {
  s21::Set<char> my_empty_set;
  std::set<char> orig_empty_set;
  ASSERT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  ASSERT_EQ(my_empty_set.size(), orig_empty_set.size());
  // TODO: // ASSERT_EQ(my_empty_set.max_size(), orig_empty_set.max_size());
}

TEST(Set, ConstructorInitializerSet) {
  // Arrange
  s21::Set<int> a{1, 2, 3, 4};
  // Act
  // Assert
  ASSERT_FALSE(a.empty());
  ASSERT_EQ(a.size(), 4);
}

TEST(Set, ConstructorCopySet) {
  // Arrange
  s21::Set<int> a{18, 180};
  s21::Set<int> b(a);
  auto it = a.begin();
  // Act

  // Assert
  ASSERT_FALSE(a.empty());
  ASSERT_EQ(a.size(), 2);

  ASSERT_EQ(*it, 18);
  ASSERT_EQ(*(++it), 180);
}

TEST(Set, ConstructorMoveSet) {
  // Arrange
  s21::Set<int> a{18, 180};
  s21::Set<int> b(std::move(a));
  auto it = b.begin();
  // Act

  // Assert
  ASSERT_TRUE(a.empty());
  ASSERT_EQ(b.size(), 2);
  ASSERT_EQ(*it, 18);
  ASSERT_EQ(*(++it), 180);
}

TEST(Set, ConstructorMoveSet2) {
  s21::Set<int> my_set = {1, 2, 3, 4, 5};
  std::set<int> orig_set = {1, 2, 3, 4, 5};
  s21::Set<int> my_set_copy = std::move(my_set);
  std::set<int> orig_set_copy = std::move(orig_set);
  ASSERT_EQ(my_set.size(), orig_set.size());
  ASSERT_EQ(my_set_copy.size(), orig_set_copy.size());
  auto my_it = my_set_copy.begin();
  auto orig_it = orig_set_copy.begin();
  for (; my_it != my_set_copy.end(); ++my_it, ++orig_it) {
    ASSERT_TRUE(*orig_it == *my_it);
  }
}

TEST(Set, IteratorsSet_1) {
  // s21::Set<std::string> my_set = {"This", "is", "my", "set"};
  // std::set<std::string> orig_set = {"This", "is", "my", "set"};
  s21::Set<int> my_set = {15, 1, 20, 3, 4, 7};
  std::set<int> orig_set = {15, 1, 20, 3, 4, 7};
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  // ASSERT_TRUE(*orig_it == *my_it);
  my_it = my_set.end();
  orig_it = orig_set.end();
  // orig_it++;
  ASSERT_EQ(*orig_it, *my_it);
  ASSERT_EQ(*--orig_it, *--my_it);
}

TEST(Set, IteratorsSet_2) {
  // s21::Set<std::string> my_set = {"This", "is", "my", "set"};
  // std::set<std::string> orig_set = {"This", "is", "my", "set"};
  s21::Set<int> my_set = {1, 2, 3, 4, 5};
  std::set<int> orig_set = {1, 2, 3, 4, 5};
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  ASSERT_TRUE(*orig_it == *my_it);
  my_it = my_set.end();
  orig_it = orig_set.end();
  my_it--;
  orig_it--;
  ASSERT_EQ(*orig_it, *my_it);
}

TEST(Set, IteratorsSet_3) {
  // s21::Set<std::string> my_set = {"This", "is", "my", "set"};
  // std::set<std::string> orig_set = {"This", "is", "my", "set"};
  s21::Set<int> my_set = {1, 2, 3, 4, 5};
  std::set<int> orig_set = {1, 2, 3, 4, 5};
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  ASSERT_TRUE(*orig_it == *my_it);
  ASSERT_EQ(*++orig_it, *++my_it);
}

TEST(Set, IteratorsSet_4) {
  // s21::Set<std::string> my_set = {"This", "is", "my", "set"};
  // std::set<std::string> orig_set = {"This", "is", "my", "set"};
  s21::Set<int> my_set = {1, 2, 3, 4, 5};
  std::set<int> orig_set = {1, 2, 3, 4, 5};
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  ASSERT_TRUE(*orig_it == *my_it);
  ASSERT_EQ(*orig_it++, *my_it++);
}

TEST(Set, ClearSet) {
  s21::Set<char> my_empty_set;
  std::set<char> orig_empty_set;
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

TEST(Set, InsertSet) {
  s21::Set<int> my_set = {5, 4, 3, 2, 7, 8, 9};
  std::set<int> orig_set = {5, 4, 3, 2, 7, 8, 9};
  auto my_pr = my_set.insert(666);
  auto orig_pr = orig_set.insert(666);
  ASSERT_TRUE(my_pr.second == orig_pr.second);
  ASSERT_TRUE(*my_pr.first == *orig_pr.first);
  my_pr = my_set.insert(111);
  orig_pr = orig_set.insert(111);
  ASSERT_EQ(my_pr.second, orig_pr.second);
  ASSERT_EQ(*my_pr.first, *orig_pr.first);
}

TEST(Set, InsertSet2) {
  s21::Set<int> my_set;
  std::set<int> orig_set;
  auto my_pr = my_set.insert(5);
  auto orig_pr = orig_set.insert(5);
  ASSERT_TRUE(my_pr.second == orig_pr.second);
  ASSERT_TRUE(*my_pr.first == *orig_pr.first);
  my_pr = my_set.insert(2);
  orig_pr = orig_set.insert(2);
  ASSERT_TRUE(my_pr.second == orig_pr.second);
  ASSERT_TRUE(*my_pr.first == *orig_pr.first);
}

TEST(Set, EraseSet) {
  s21::Set<int> my_set = {5, 4, 3, 2, 7, 8, 9};
  std::set<int> orig_set = {5, 4, 3, 2, 7, 8, 9};
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

TEST(Set, SwapSet) {
  s21::Set<int> my_set = {1};
  s21::Set<int> my_swap_set = {3, 4, 5};

  my_set.swap(my_swap_set);
  ASSERT_EQ(my_set.size(), 3);
  ASSERT_EQ(my_swap_set.size(), 1);
  ASSERT_EQ(*my_set.begin(), 3);
  ASSERT_EQ(*my_swap_set.begin(), 1);
}

TEST(Set, MergeSet) {
  s21::Set<int> my_set = {1};
  s21::Set<int> my_merge_set = {3, 4, 5};

  my_set.merge(my_merge_set);

  std::set<int> orig_set = {1};
  std::set<int> orig_merge_set = {3, 4, 5};

  orig_set.merge(orig_merge_set);

  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    ASSERT_TRUE(*orig_it == *my_it);
  }
  ASSERT_EQ(orig_set.size(), my_set.size());
  ASSERT_EQ(my_merge_set.size(), orig_merge_set.size());
}

TEST(Set, FindSet) {
  s21::Set<double> my_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  s21::Set<double> orig_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  auto my_it = my_set.find(2.4);
  auto orig_it = orig_set.find(2.4);
  ASSERT_TRUE(*orig_it == *my_it);
}

TEST(Set, ContainsSet) {
  s21::Set<double> my_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  s21::Set<double> orig_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  ASSERT_EQ(my_set.contains(2), orig_set.contains(2));
  ASSERT_EQ(my_set.contains(2.1), orig_set.contains(2.1));
}

TEST(Set, InsertManySet) {
  s21::Set<int> my_set = {1, 2, 3, 4, 5};
  s21::Set<int> reference_set = {1, 2, 3, 4, 5, 10, 20, 30};

  s21::Vector vc = my_set.insert_many(10, 3, 4, 20, 30);

  auto my_it = my_set.begin();
  auto reference_it = reference_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++reference_it) {
    ASSERT_TRUE(*reference_it == *my_it);
  }
}