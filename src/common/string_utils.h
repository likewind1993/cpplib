#include <string>
#include <vector>

namespace common {

std::vector<std::string> Split(const std::string& str,
                               const std::string& splitor) {
  std::vector<std::string> res;
  std::string::size_type slow, fast;
  size_t len = str.length();

  fast = str.find(splitor);
  slow = 0;

  while(fast != std::string::npos) {
    res.emplace_back(str.substr(slow, fast - slow));
    slow = fast + splitor.size();
    fast = str.find(splitor, slow);
  }
  if (slow != len) {
    res.emplace_back(str.substr(slow));
  }

  return res;
}
}  // namespace common