#include "tests.h"

TEST(Vector, DefaultConstructor_EmptyVector) {
  s21::Vector<int> v;
  ASSERT_TRUE(v.empty());
  ASSERT_EQ(v.size(), 0);
}

TEST(Vector, SizeConstructor_PositiveSize) {
  const size_t size = 5;
  s21::Vector<int> v(size);
  ASSERT_FALSE(v.empty());
  ASSERT_EQ(v.size(), size);
  for (size_t i = 0; i < size; ++i) {
    ASSERT_EQ(v[i], 0);
  }
}

TEST(Vector, SizeConstructor_ZeroSize) {
  const size_t size = 0;
  s21::Vector<int> v(size);
  ASSERT_TRUE(v.empty());
  ASSERT_EQ(v.size(), size);
}

TEST(Vector, InitializerListConstructor_EmptyList) {
  s21::Vector<int> v = {};
  ASSERT_TRUE(v.empty());
  ASSERT_EQ(v.size(), 0);
}

TEST(Vector, InitializerListConstructor_NonEmptyList) {
  s21::Vector<int> v = {1, 2, 3, 4, 5};
  ASSERT_FALSE(v.empty());
  ASSERT_EQ(v.size(), 5);
  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(v[4], 5);
}

TEST(Vector, CopyConstructor_EmptyVector) {
  s21::Vector<int> v1;
  s21::Vector<int> v2(v1);
  ASSERT_TRUE(v2.empty());
  ASSERT_EQ(v2.size(), 0);
}

TEST(Vector, CopyConstructor_NonEmptyVector) {
  s21::Vector<int> v1 = {1, 2, 3};
  s21::Vector<int> v2(v1);
  ASSERT_EQ(v2.size(), v1.size());
  for (size_t i = 0; i < v1.size(); ++i) {
    ASSERT_EQ(v2[i], v1[i]);
  }
}

TEST(Vector, MoveConstructor_EmptyVector) {
  s21::Vector<int> v1;
  s21::Vector<int> v2(std::move(v1));
  ASSERT_TRUE(v2.empty());
  ASSERT_EQ(v2.size(), 0);
}

TEST(Vector, MoveConstructor_NonEmptyVector) {
  s21::Vector<int> v1 = {1, 2, 3};
  s21::Vector<int> v2(std::move(v1));
  ASSERT_EQ(v2.size(), 3);
  ASSERT_TRUE(v1.empty());
}

TEST(Vector, Destructor_EmptyVector) {
  s21::Vector<int> *v = new s21::Vector<int>();
  delete v;
}

TEST(Vector, Destructor_NonEmptyVector) {
  s21::Vector<int> *v = new s21::Vector<int>{1, 2, 3};
  delete v;
}

TEST(Vector, MoveAssignmentOperator_EmptyToEmpty) {
  s21::Vector<int> v1;
  s21::Vector<int> v2;
  v2 = std::move(v1);
  ASSERT_TRUE(v2.empty());
  ASSERT_EQ(v2.size(), 0);
}

TEST(Vector, MoveAssignmentOperator_NonEmptyToEmpty) {
  s21::Vector<int> v1 = {1, 2, 3};
  s21::Vector<int> v2;
  v2 = std::move(v1);
  ASSERT_EQ(v2.size(), 3);
  ASSERT_TRUE(v1.empty());
}

TEST(Vector, MoveAssignmentOperator_EmptyToNonEmpty) {
  s21::Vector<int> v1;
  s21::Vector<int> v2 = {4, 5, 6};
  v2 = std::move(v1);
  ASSERT_TRUE(v2.empty());
  ASSERT_EQ(v2.size(), 0);
}

TEST(Vector, MoveAssignmentOperator_NonEmptyToNonEmpty) {
  s21::Vector<int> v1 = {1, 2, 3};
  s21::Vector<int> v2 = {4, 5, 6};
  v2 = std::move(v1);
  ASSERT_EQ(v2.size(), 3);
  ASSERT_TRUE(v1.empty());
}

TEST(Vector, At_ValidIndex) {
  s21::Vector<int> v = {1, 2, 3, 4, 5};
  ASSERT_EQ(v.at(0), 1);
  ASSERT_EQ(v.at(2), 3);
  ASSERT_EQ(v.at(4), 5);
}

TEST(Vector, At_InvalidIndex) {
  s21::Vector<int> v = {1, 2, 3, 4, 5};
  ASSERT_THROW(v.at(5), std::out_of_range);
  ASSERT_THROW(v.at(10), std::out_of_range);
}

TEST(Vector, IndexOperator_ValidIndex) {
  s21::Vector<int> v = {1, 2, 3, 4, 5};
  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(v[2], 3);
  ASSERT_EQ(v[4], 5);
}

TEST(Vector, IndexOperator_InvalidIndex) {
  s21::Vector<int> v = {1, 2, 3, 4, 5};
  ASSERT_ANY_THROW(v[5]);
  ASSERT_ANY_THROW(v[10]);
}

TEST(Vector, ConstIndexOperator_ValidIndex) {
  const s21::Vector<int> v = {1, 2, 3, 4, 5};
  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(v[2], 3);
  ASSERT_EQ(v[4], 5);
}

TEST(Vector, ConstIndexOperator_InvalidIndex) {
  const s21::Vector<int> v = {1, 2, 3, 4, 5};
  ASSERT_ANY_THROW(v[5]);
  ASSERT_ANY_THROW(v[10]);
}

TEST(Vector, FrontConst_ValidVector) {
  const s21::Vector<int> v = {1, 2, 3, 4, 5};
  ASSERT_EQ(v.front(), 1);
}

TEST(Vector, FrontConst_EmptyVector) {
  const s21::Vector<int> v;
  ASSERT_THROW(v.front(), std::out_of_range);
}

TEST(Vector, BackConst_ValidVector) {
  const s21::Vector<int> v = {1, 2, 3, 4, 5};
  ASSERT_EQ(v.back(), 5);
}

TEST(Vector, BackConst_EmptyVector) {
  const s21::Vector<int> v;
  ASSERT_THROW(v.back(), std::out_of_range);
}

TEST(Vector, Data_ValidVector) {
  s21::Vector<int> v = {1, 2, 3, 4, 5};
  int *dataPtr = v.data();
  ASSERT_EQ(*dataPtr, 1);
  *dataPtr = 10;
  ASSERT_EQ(v[0], 10);
}

TEST(Vector, Data_EmptyVector) {
  s21::Vector<int> v;
  int *dataPtr = v.data();
  ASSERT_EQ(dataPtr, nullptr);
}

TEST(Vector, Begin_ValidVector) {
  s21::Vector<int> v = {1, 2, 3, 4, 5};
  auto it = v.begin();
  ASSERT_EQ(*it, 1);
  *it = 10;
  ASSERT_EQ(v[0], 10);
}

TEST(Vector, Begin_EmptyVector) {
  s21::Vector<int> v;
  auto it = v.begin();
  ASSERT_EQ(it, v.end());
}

TEST(Vector, End_ValidVector) {
  s21::Vector<int> v = {1, 2, 3, 4, 5};
  auto it = v.end();
  auto beginIt = v.begin();
  ASSERT_NE(it, beginIt);
}

TEST(Vector, End_EmptyVector) {
  s21::Vector<int> v;
  auto it = v.end();
  ASSERT_EQ(it, v.begin());
}

TEST(Vector, Empty_EmptyVector) {
  const s21::Vector<int> v;
  ASSERT_TRUE(v.empty());
}

TEST(Vector, Empty_NonEmptyVector) {
  const s21::Vector<int> v = {1, 2, 3};
  ASSERT_FALSE(v.empty());
}

TEST(Vector, Size_EmptyVector) {
  const s21::Vector<int> v;
  ASSERT_EQ(v.size(), 0);
}

TEST(Vector, Size_NonEmptyVector) {
  const s21::Vector<int> v = {1, 2, 3};
  ASSERT_EQ(v.size(), 3);
}

TEST(Vector, MaxSize) {
  const s21::Vector<int> v;
  ASSERT_GT(v.max_size(), 0);
}

TEST(Vector, Reserve_IncreaseCapacity) {
  s21::Vector<int> v;
  size_t initial_capacity = v.capacity();
  size_t new_capacity = initial_capacity + 10;
  v.reserve(new_capacity);
  ASSERT_GE(v.capacity(), new_capacity);
}

TEST(Vector, Reserve_DecreaseCapacity) {
  s21::Vector<int> v = {1, 2, 3, 4, 5};
  size_t initialCapacity = v.capacity();
  size_t newCapacity = initialCapacity - 2;
  v.reserve(newCapacity);
  ASSERT_LE(v.capacity(), initialCapacity);
  ASSERT_GE(v.capacity(), newCapacity);
}

TEST(Vector, Capacity_EmptyVector) {
  const s21::Vector<int> v;
  ASSERT_GE(v.capacity(), 0);
}

TEST(Vector, Capacity_NonEmptyVector) {
  const s21::Vector<int> v = {1, 2, 3};
  ASSERT_GE(v.capacity(), v.size());
}

TEST(Vector, ShrinkToFit_EmptyVector) {
  s21::Vector<int> v;
  v.shrink_to_fit();
  ASSERT_GE(v.capacity(), 0);
}

TEST(Vector, ShrinkToFit_NonEmptyVector) {
  s21::Vector<int> v = {1, 2, 3, 4, 5};
  size_t initialCapacity = v.capacity();
  v.pop_back();  // Simulate a reduction in size
  v.shrink_to_fit();
  ASSERT_LE(v.capacity(), v.size());
  ASSERT_LE(v.capacity(), initialCapacity);
}

TEST(Vector, Clear_EmptyVector) {
  s21::Vector<int> v;
  v.clear();
  ASSERT_TRUE(v.empty());
  ASSERT_EQ(v.size(), 0);
  // Clearing an empty vector should not affect capacity
  ASSERT_GE(v.capacity(), 0);
}

TEST(Vector, Clear_NonEmptyVector) {
  s21::Vector<int> v = {1, 2, 3, 4, 5};
  v.clear();
  ASSERT_TRUE(v.empty());
  ASSERT_EQ(v.size(), 0);
  // Clearing a vector should not affect capacity immediately
  ASSERT_GE(v.capacity(), 0);
}

TEST(Vector, Insert_Beginning) {
  s21::Vector<int> v = {2, 3, 4};
  auto it = v.insert(v.begin(), 1);
  ASSERT_EQ(v.size(), 4);
  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(*it, 1);
}

TEST(Vector, Insert_Middle) {
  s21::Vector<int> v = {1, 3, 4};
  auto it = v.insert(v.begin() + 1, 2);
  ASSERT_EQ(v.size(), 4);
  ASSERT_EQ(v[1], 2);
  ASSERT_EQ(*it, 2);
}

TEST(Vector, Insert_End) {
  s21::Vector<int> v = {1, 2, 3};
  auto it = v.insert(v.end(), 4);
  ASSERT_EQ(v.size(), 4);
  ASSERT_EQ(v[3], 4);
  ASSERT_EQ(*it, 4);
}

TEST(Vector, Erase_Beginning) {
  s21::Vector<int> v = {1, 2, 3, 4};
  v.erase(v.begin());  // Erase the first element
  ASSERT_EQ(v.size(), 3);
  ASSERT_EQ(v[0], 2);
}

TEST(Vector, Erase_Middle) {
  s21::Vector<int> v = {1, 2, 3, 4};
  v.erase(v.begin() + 1);
  ASSERT_EQ(v.size(), 3);
  ASSERT_EQ(v[1], 3);
}

TEST(Vector, Erase_End) {
  s21::Vector<int> v = {1, 2, 3, 4};
  v.erase(v.end() - 1);  // Erase the last element
  ASSERT_EQ(v.size(), 3);
  ASSERT_EQ(v[2], 3);
}

TEST(Vector, PushBack_EmptyVector) {
  s21::Vector<int> v;
  v.push_back(1);
  ASSERT_EQ(v.size(), 1);
  ASSERT_EQ(v[0], 1);
}

TEST(Vector, PushBack_NonEmptyVector) {
  s21::Vector<int> v = {1, 2, 3};
  v.push_back(4);
  ASSERT_EQ(v.size(), 4);
  ASSERT_EQ(v[3], 4);
}

TEST(Vector, PopBack_NonEmptyVector) {
  s21::Vector<int> v = {1, 2, 3};
  v.pop_back();
  ASSERT_EQ(v.size(), 2);
  ASSERT_EQ(v.back(), 2);
}

TEST(Vector, PopBack_EmptyVector) {
  s21::Vector<int> v;
  v.pop_back();
  ASSERT_TRUE(v.empty());
}

TEST(Vector, Swap_NonEmptyVectors) {
  s21::Vector<int> v1 = {1, 2, 3};
  s21::Vector<int> v2 = {4, 5, 6};

  v1.swap(v2);

  ASSERT_EQ(v1.size(), 3);
  ASSERT_EQ(v2.size(), 3);

  ASSERT_EQ(v1[0], 4);
  ASSERT_EQ(v1[2], 6);

  ASSERT_EQ(v2[0], 1);
  ASSERT_EQ(v2[2], 3);
}

TEST(Vector, Swap_EmptyAndNonEmptyVectors) {
  s21::Vector<int> v1;
  s21::Vector<int> v2 = {1, 2, 3};

  v1.swap(v2);

  ASSERT_EQ(v1.size(), 3);
  ASSERT_FALSE(v1.empty());
  ASSERT_EQ(v2.size(), 0);
  ASSERT_TRUE(v2.empty());
}

// TEST(Vector, InsertMany) {
//    s21::Vector<int> vec = {1, 2, 3, 7, 8};
//    s21::Vector<int>::const_iterator pos = vec.begin() + 3;

//   vec.insert_many(pos, 4, 5, 6);

//   // Check the size of the vector after insertion
//   ASSERT_EQ(vec.size(), 8);

//   // Check the elements after insertion
//   ASSERT_EQ(vec[0], 1);
//   ASSERT_EQ(vec[1], 2);
//   ASSERT_EQ(vec[2], 3);
//   ASSERT_EQ(vec[3], 4);
//   ASSERT_EQ(vec[4], 5);
//   ASSERT_EQ(vec[5], 6);
//   ASSERT_EQ(vec[6], 7);
//   ASSERT_EQ(vec[7], 8);
// }

// TEST(Vector, InsertManyBack) {
//    s21::Vector<int> vec = {1, 2, 3};

//   vec.insert_many_back(4, 5, 6);

//   // Check the size of the vector after insertion
//   ASSERT_EQ(vec.size(), 6);

//   // Check the elements after insertion
//   ASSERT_EQ(vec[0], 1);
//   ASSERT_EQ(vec[1], 2);
//   ASSERT_EQ(vec[2], 3);
//   ASSERT_EQ(vec[3], 4);
//   ASSERT_EQ(vec[4], 5);
//   ASSERT_EQ(vec[5], 6);
// }