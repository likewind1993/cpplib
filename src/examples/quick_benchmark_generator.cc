#include <climits>
#include <fstream>
#include <random>
#include <string>

#include "src/common/string_utils.h"

const static std::string kDefaultSplitor = " ";
const static std::string kDefaultFileName = "random_nums";
const static size_t kGeneratedNum = 1000000;

bool LoadArrays(const std::string& file_name,
                std::vector<int>* nums) {
  std::ifstream in;
  in.open(file_name);
  if (!in.is_open()) return false;

  std::string line;
  while(getline(in, line)) {
    auto strs = common::Split(line, kDefaultSplitor);
    for (auto& str : strs) {
      (*nums).emplace_back(stoi(str));
    }
  }

  in.close();
  return true;
}

bool GenerateArrays(const std::string& file_name) {
  std::ofstream out;
  out.open(file_name);
  if (!out.is_open()) return false;

  for (size_t i = 0; i < kGeneratedNum; ++i) {
    srand((unsigned)time(NULL));
    out << rand() % INT_MAX << kDefaultSplitor; 
  } 

  out.close();
  return false;
}

int main() {

  GenerateArrays(kDefaultFileName);

  return 0;
}