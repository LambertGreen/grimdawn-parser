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
    k *= TABLE_MULT;
    _table[i] = k;
  }
}
