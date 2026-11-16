#pragma once

#include <cstddef>
#include <utility>
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

template <typename T>
void Registry<T>::add(T item) {
  items.push_back(std::move(item));
}

template <typename T>
void Registry<T>::remove(std::size_t index) {
  items.erase(items.begin() + index);
}

template <typename T>
std::size_t Registry<T>::size() const {
  return items.size();
}

template <typename T>
T& Registry<T>::operator[](std::size_t index) {
  return items[index];
}

template <typename T>
const T& Registry<T>::operator[](std::size_t index) const {
  return items[index];
}
