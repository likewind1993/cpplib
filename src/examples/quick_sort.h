#include <cstddef>

template <typename T>
void PrintArr(const T* arr, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
}

template <typename T>
void swap(T* data, size_t x, size_t y) {
  auto temp = data[x];
  data[x] = data[y];
  data[y] = temp;
}

template <typename T>
size_t partition(T* data, size_t left, size_t right) {
  auto mid = data[right];
  auto i = left, j = left;
  while (j < right) {
    if (data[j] <= mid) {
      swap<T>(data, i++, j);
    }
    ++j;
  }
  swap<T>(data, i, right);
  return i;
}

// TODO(likewind1993) : 当前算法对已经完成排序的数组（如1， 2， 3， 4），
// 仍然会执行parition分割，应该设置一个标志位，发现已经完成排序后，跳出递归
template <typename T>
void quick_sort(T* data, size_t left, size_t right) {
  if (left < right) {
    auto mid = partition<T>(data, left, right);
    quick_sort<T>(data, left, mid - 1);
    quick_sort<T>(data, mid + 1, right);
  }
}

template <typename T>
void quick_sort(T* data, size_t size) {
  quick_sort<T>(data, 0, size - 1);
}