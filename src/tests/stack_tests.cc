#include <gtest/gtest.h>

#include "tests.h"

TEST(Stack, Constructor_Default) {
  s21::Stack<int> our_stack;
  std::stack<int> std_stack;
  ASSERT_EQ(our_stack.empty(), std_stack.empty());
}

TEST(Stack, Constructor_List) {
  s21::Stack<int> our_stack{1, 2, 3};
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  // our_stack.push(4);
  ASSERT_EQ(our_stack.top(), std_stack.top());
  // ASSERT_EQ(our_stack.size(), 2);
}

TEST(Stack, Constructor_Copy) {
  s21::Stack<int> our_stack = {1, 2, 3};
  s21::Stack<int> our_copy(our_stack);
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std::stack<int> std_copy(std_stack);
  ASSERT_EQ(our_copy.top(), std_copy.top());
}

TEST(Stack, Operator_Copy) {
  s21::Stack<int> our_stack_int = {1, 2, 3};
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  s21::Stack<int> our_stack_empty;
  std::stack<int> std_stack_empty;
  our_stack_empty = our_stack_int;
  std_stack_empty = std_stack_int;
  ASSERT_EQ(our_stack_empty.top(), std_stack_empty.top());
  ASSERT_EQ(our_stack_int.empty(), std_stack_int.empty());
}

TEST(Stack, Constructor_Move) {
  s21::Stack<int> our_stack = {1, 2, 3};
  s21::Stack<int> our_move(std::move(our_stack));
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std::stack<int> std_move(std::move(std_stack));
  ASSERT_EQ(our_move.top(), std_move.top());
  ASSERT_EQ(our_stack.empty(), std_stack.empty());
}

TEST(Stack, Top) {
  s21::Stack<int> our_stack_int = {1, 2, 3};
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  s21::Stack<double> our_stack_double = {1.1f, 2.1f, 3.1f};
  std::stack<double> std_stack_double;
  std_stack_double.push(1.1f);
  std_stack_double.push(2.1f);
  std_stack_double.push(3.1f);
  s21::Stack<std::string> our_stack_string = {"abc", "def", "ghf"};
  std::stack<std::string> std_stack_string;
  std_stack_string.push("abc");
  std_stack_string.push("def");
  std_stack_string.push("ghf");
  ASSERT_EQ(our_stack_int.top(), std_stack_int.top());
  ASSERT_EQ(our_stack_double.top(), std_stack_double.top());
  ASSERT_EQ(our_stack_string.top(), std_stack_string.top());
}

TEST(Stack, Empty) {
  s21::Stack<int> our_stack_int = {1, 2, 3};
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  ASSERT_EQ(our_stack_int.empty(), std_stack_int.empty());
  s21::Stack<int> our_stack_empty;
  std::stack<int> std_stack_empty;
  ASSERT_EQ(our_stack_empty.empty(), std_stack_empty.empty());
}

TEST(Stack, Size) {
  s21::Stack<int> our_stack_int = {1, 2, 3};
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  ASSERT_EQ(our_stack_int.size(), std_stack_int.size());
  s21::Stack<int> our_stack_empty;
  std::stack<int> std_stack_empty;
  ASSERT_EQ(our_stack_empty.size(), std_stack_empty.size());
}

TEST(Stack, Push) {
  s21::Stack<int> our_stack_int;
  our_stack_int.push(1);
  our_stack_int.push(2);
  our_stack_int.push(3);
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  ASSERT_EQ(our_stack_int.top(), std_stack_int.top());
}

TEST(Stack, Pop) {
  s21::Stack<int> our_stack_int;
  our_stack_int.push(1);
  our_stack_int.push(2);
  our_stack_int.push(3);
  our_stack_int.pop();
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  std_stack_int.pop();
  ASSERT_EQ(our_stack_int.top(), std_stack_int.top());
  our_stack_int.pop();
  our_stack_int.pop();
  std_stack_int.pop();
  std_stack_int.pop();
  ASSERT_EQ(our_stack_int.empty(), std_stack_int.empty());
}

TEST(Stack, Swap) {
  s21::Stack<int> our_stack_int = {1, 2, 3};
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  s21::Stack<int> our_stack_empty;
  std::stack<int> std_stack_empty;
  our_stack_empty.swap(our_stack_int);
  std_stack_empty.swap(std_stack_int);
  ASSERT_EQ(our_stack_empty.top(), std_stack_empty.top());
  ASSERT_EQ(our_stack_int.empty(), std_stack_int.empty());
}

TEST(Stack, InsertManyFront) {
  s21::Stack<int> our_stack_int;
  our_stack_int.insert_many_front(1, 2, 3);
  ASSERT_EQ(our_stack_int.top(), 3);
}