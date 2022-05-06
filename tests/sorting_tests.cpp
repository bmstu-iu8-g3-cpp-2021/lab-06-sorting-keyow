// Copyright 2021 keyow

#include <gtest/gtest.h>

#include <fstream>
#include <list>
#include <vector>

#include "../include/sorting.h"
#include "timer.h"

namespace {
struct TestCase {
  std::vector<int> test_vector;
  std::vector<int> out_vector;
  void print() {
    std::for_each(test_vector.begin(), test_vector.end(),
                  [](int el) { std::cout << el << ' '; });
  }
  void print_output_container() {
    std::for_each(out_vector.begin(), out_vector.end(),
                  [](int el) { std::cout << el << ' '; });
  }
};

void Load(std::string filename, std::vector<int>& test_vector) {
  test_vector.clear();
  std::ifstream fout(filename, std::ios::app);
  int number;
  while (!fout.eof()) {
    fout >> number;
    test_vector.push_back(number);
  }
}
}  // namespace

TEST(Merging, merging) {
  std::vector<int> v1 = {1, 5, 6};
  std::vector<int> v2 = {2, 5, 7};
  std::vector<int> v3;

  merge_func(v1.begin(), v1.end(), v2.begin(), v2.end(),
             std::back_inserter(v3));

  EXPECT_TRUE(v3 == std::vector<int>({1, 2, 5, 5, 6, 7}));

  std::list<double> l1 = {1.1, 6.54, 43.0};
  std::list<double> l2;
  std::list<double> l3;

  // здесь я поэкспериментировал, люблю эксперименты
  BoolFunctionType<int>::type func_pointer = std::greater<int>{};

  merge_func(l1.begin(), l1.end(), l2.begin(), l2.end(), std::back_inserter(l3),
             func_pointer);

  EXPECT_TRUE(l3 == std::list<double>({1.1, 6.54, 43.0}));

  std::vector<std::string> names_1 = {"Alex", "John"};
  std::vector<std::string> names_2 = {"Alice", "Bob"};
  std::vector<std::string> names_merged;

  merge_func(names_1.begin(), names_1.end(), names_2.begin(), names_2.end(),
             std::back_inserter(names_merged));
  EXPECT_TRUE(names_merged ==
              std::vector<std::string>({"Alex", "Alice", "Bob", "John"}));
}

TEST(MergeSort, mergesort) {
  std::vector<int> vec = {1, 4, 3, 2};
  std::vector<int> sorted_vec;
  merge_sort(vec.begin(), vec.end(), std::back_inserter(sorted_vec));
  EXPECT_EQ(sorted_vec, std::vector<int>({1, 2, 3, 4}));
}

TEST(ImplaceMergeSort, implacemergesort) {
  std::vector<int> vec = {1, 4, 3, 2};
  inplace_merge_sort(vec.begin(), vec.end());
  EXPECT_EQ(vec, std::vector<int>({1, 2, 3, 4}));
}

TEST(HeapSort, heapsort) {
  std::list<int> l = {13, 321, 5, -12, -1231, 414, 3134, -41, 0, 0, -999};
  heap_sort(l.begin(), l.end());
  EXPECT_EQ(
      l, std::list<int>({-1231, -999, -41, -12, 0, 0, 5, 13, 321, 414, 3134}));

  std::vector<int> vec = {1, -1, -15, -30};
  heap_sort(vec.begin(), vec.end());
  EXPECT_EQ(vec, std::vector<int>({-30, -15, -1, 1}));
}

TEST(QuickSort, quicksort) {
  std::vector<int> vec = {13, 321, 5, -12, -1231, 414, 3134, -41, 0, 0, -999};
  quick_sort(vec.begin(), vec.end());
  EXPECT_EQ(vec, std::vector<int>(
                     {-1231, -999, -41, -12, 0, 0, 5, 13, 321, 414, 3134}));

  std::vector<int> vec1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  quick_sort(vec1.begin(), vec1.end());
  EXPECT_TRUE(vec1 == std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}));
}

TEST(InsertionSort, insertionsort) {
  std::vector<int> vec = {13, 321, 5, -12, -1231, 414, 3134, -41, 0, 0, -999};
  insertion_sort(vec.begin(), vec.end());
  EXPECT_EQ(vec, std::vector<int>(
                     {-1231, -999, -41, -12, 0, 0, 5, 13, 321, 414, 3134}));
  std::vector<int> vec1 = {};
  insertion_sort(vec1.begin(), vec1.end());
  EXPECT_TRUE(vec1.empty());
}

TEST(Comparing, Quicksort) {
  TestCase test;
  Timer time;

  for (int i = 0; i < 100; ++i) {
    std::cout << i + 1 << std::endl;
    Load("../tests/test_arr.txt", test.test_vector);
    time.start();
    quick_sort(test.test_vector.begin(), test.test_vector.end());
    time.end();
    time.log("../tests/log/quicksort_log.txt");
  }
}

TEST(Comparing, Heapsort) {
  TestCase test;
  Timer time;

  for (int i = 0; i < 100; ++i) {
    std::cout << i + 1 << std::endl;
    Load("../tests/test_arr.txt", test.test_vector);
    time.start();
    heap_sort(test.test_vector.begin(), test.test_vector.end());
    time.end();
    time.log("../tests/log/heapsort_log.txt");
  }
}

TEST(Comparing, MergeSort) {
  TestCase test;
  Timer time;

  for (int i = 0; i < 100; ++i) {
    std::cout << i + 1 << std::endl;
    Load("../tests/test_arr.txt", test.test_vector);
    time.start();
    merge_sort(test.test_vector.begin(), test.test_vector.end(),
               std::back_inserter(test.out_vector));
    time.end();
    time.log("../tests/log/mergesort_log.txt");
  }
}

TEST(Comparing, InplaceMergeSort) {
  TestCase test;
  Timer time;

  for (int i = 0; i < 100; ++i) {
    std::cout << i + 1 << std::endl;
    Load("../tests/test_arr.txt", test.test_vector);
    time.start();
    inplace_merge_sort(test.test_vector.begin(), test.test_vector.end());
    time.end();
    time.log("../tests/log/inplacemergesort_log.txt");
  }
}

TEST(Comparing, InsertionSort) {
  TestCase test;
  Timer time;

  Load("../tests/test_arr.txt", test.test_vector);
  time.start();
  insertion_sort(test.test_vector.begin(), test.test_vector.end());
  time.end();
  time.log("../tests/log/insertionsort_log.txt");
}

TEST(Comparing, StableSort) {
  TestCase test;
  Timer time;

  for (int i = 0; i < 100; ++i) {
    std::cout << i + 1 << std::endl;
    Load("../tests/test_arr.txt", test.test_vector);
    time.start();
    stable_sort(test.test_vector.begin(), test.test_vector.end());
    time.end();
    time.log("../tests/log/stablesort_log.txt");
  }
}

TEST(Comparing, Sort) {
  TestCase test;
  Timer time;

  for (int i = 0; i < 100; ++i) {
    std::cout << i + 1 << std::endl;
    Load("../tests/test_arr.txt", test.test_vector);
    time.start();
    std::sort(test.test_vector.begin(), test.test_vector.end());
    time.end();
    time.log("../tests/log/sort_log.txt");
  }
}