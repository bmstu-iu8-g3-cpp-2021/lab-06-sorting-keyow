// Copyright 2021 keyow

#ifndef TEMPLATE_SORTING_H
#define TEMPLATE_SORTING_H

#include <algorithm>
#include <functional>
#include <iostream>

template <class T>
class BoolFunctionType {
 public:
  typedef std::function<bool(T, T)> type;
};

template <class It, class Out, class Compare = std::less<>>
Out merge_func(It first1, It last1, It first2, It last2, Out out,
               Compare cmp = Compare{}) {
  while (first1 != last1 || first2 != last2) {
    if (first1 == last1) {
      *out = *first2++;
    } else if (first2 == last2) {
      *out = *first1++;
    } else if (cmp(*first1, *first2)) {
      *out = *first1++;
    } else {
      *out = *first2++;
    }
    ++out;
  }
  return out;
}

template <class It, class Compare = std::less<>>
void inplace_merge_func(It first1, It mid, It last, Compare cmp = Compare{}) {
  It begin = first1;
  It first2 = mid;
  std::vector<typename It::value_type> container_copy;
  while (first1 != mid && first2 != last) {
    if (cmp(*first1, *first2)) {
      container_copy.emplace_back(*first1++);
    } else {
      container_copy.emplace_back(*first2++);
    }
  }
  container_copy.insert(container_copy.end(), first1, mid);
  container_copy.insert(container_copy.end(), first2, last);
  std::move(container_copy.begin(), container_copy.end(), begin);
}

template <class It, class Out, class Compare = std::less<>>
Out merge_sort(It first, It last, Out out, Compare cmp = Compare{}) {
  size_t size = std::distance(first, last);
  if (size == 1) {
    return out;
  }

  std::vector<typename It::value_type> container_copy;
  std::copy(first, last, std::back_inserter(container_copy));

  auto c_begin = container_copy.begin();
  auto c_end = container_copy.end();
  auto mid = std::next(c_begin, size / 2);

  merge_sort(c_begin, mid, c_begin, cmp);
  merge_sort(mid, c_end, mid, cmp);

  return std::merge(c_begin, mid, mid, c_end, out, cmp);
}

template <class It, class Compare = std::less<>>
void inplace_merge_sort(It first, It last, Compare cmp = Compare{}) {
  size_t size = std::distance(first, last);
  if (size == 1) {
    return;
  }

  auto mid = std::next(first, size / 2);

  inplace_merge_sort(first, mid, cmp);
  inplace_merge_sort(mid, last, cmp);
  inplace_merge_func(first, mid, last, cmp);
}

template <class It, class Compare = std::less<>>
void max_heapify(It first, It last, It current, size_t heap_size,
                 Compare cmp = Compare{}) {
  size_t dist = std::distance(first, current) + 1;
  It largest_node = current;
  It left = std::next(first, 2 * dist - 1);
  It right = std::next(first, 2 * dist);

  if (2 * dist - 1 < heap_size && cmp(*current, *left)) {
    largest_node = left;
  }

  if (2 * dist < heap_size && cmp(*largest_node, *right)) {
    largest_node = right;
  }

  if (largest_node != current) {
    std::swap(*current, *largest_node);
    max_heapify(first, last, largest_node, heap_size, cmp);
  }
}

template <class It, class Compare = std::less<>>
void heap_sort(It first, It last, Compare cmp = Compare{}) {
  size_t heap_size = std::distance(first, last);

  auto mid = std::next(first, heap_size / 2 - 1);
  auto r_end = std::prev(first);
  for (auto it = mid; it != r_end; --it) {
    max_heapify(first, last, it, heap_size, cmp);
  }

  for (auto it = std::prev(last); it != first; --it) {
    std::swap(*it, *first);
    --heap_size;
    max_heapify(first, last, first, heap_size);
  }
}

template <class It>
It partition(It first, It last) {
  auto value = *std::prev(last);
  auto i = std::prev(first);
  for (auto j = first; j != last; ++j) {
    if (*j < value) {
      ++i;
      std::swap(*i, *j);
    }
  }
  std::swap(*std::next(i), *std::prev(last));
  return std::next(i);
}

template <class It>
void quick_sort(It first, It last) {
  if (first == last) {
    return;
  }
  auto pivot = partition(first, last);
  quick_sort(first, pivot);
  quick_sort(std::next(pivot), last);
}

template <class It, class Compare=std::less<>>
void insertion_sort(It first, It last, Compare cmp=Compare{}) {
  auto begin = first;
  while (first != last) {
    auto it = first;
    while (it != begin && cmp(*it, *std::prev(it))) {
      std::swap(*it, *std::prev(it));
      --it;
    }
    ++first;
  }
}
#endif  // TEMPLATE_SORTING_H
