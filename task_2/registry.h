#pragma once

#include <cstddef>
#include <vector>

template <typename T>
class Registry {
 public:
  void add(T item);
  void remove(std::size_t index);
  std::size_t size() const;

  T& operator[](std::size_t index);
  const T& operator[](std::size_t index) const;

 private:
  std::vector<T> items;
};
