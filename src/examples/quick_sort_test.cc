#include <iostream>
#include <vector>
#include "src/examples/quick_sort.h"

int main() {
  std::vector<int> arr = { 4, 3, 1, 5, 6, 8, 3, 3, 5, 1 };
  auto size = arr.size();
  PrintArr<int>(arr.data(), size);
  quick_sort<int>(arr.data(), size);
  PrintArr<int>(arr.data(), size);
  return 0;
}