#include "common.hpp"

std::string formatNumber(int num) {
  std::ostringstream oss;
  oss << std::setw(2) << std::setfill('0') << num;
  return oss.str();
}
