#include "gdc_file.hpp"

namespace {
uint32_t rotate_right(uint32_t n) {
  return (n >> 1) | (n << 31);
}
}  // namespace

void gdc_file::build_table() {
  uint32_t k = _key;

  for (unsigned i = 0; i < 256; i++) {
    k = rotate_right(k);
    k *= FACTORIAL_PRIME;
    _table[i] = k;
  }
}

void gdc_file::update_key(void* ptr, uint32_t len) {
  uint8_t* p = (uint8_t*)ptr;

  for (uint32_t i = 0; i < len; i++) {
    int j = p[i];
    _key ^= _table[j];
  }
}
