#include "common.hpp"

std::string formatNumber(int num, int count) {
  std::ostringstream oss;
  oss << std::setw(count) << std::setfill('0') << num;
  return oss.str();
}
