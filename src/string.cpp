#include "string.hpp"

void string::read(gdc_file* gdc) {
  uint32_t len = gdc->read_int();
  if (len > 256) {
    throw std::runtime_error("Length of string is suspiciously long: " +
                             std::to_string(len));
  }

  clear();
  reserve(len);

  for (uint32_t i = 0; i < len; i++) {
    push_back(gdc->read_byte());
  }
}
