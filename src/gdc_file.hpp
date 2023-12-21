#pragma once

#include "file.hpp"

#include <_types/_uint8_t.h>
#include <stdint.h>

class gdc_file {
 protected:
  static constexpr int XOR_BITMAP = 0x55555555;
  static constexpr int VERSION = 0x58434447;
  static constexpr int TABLE_MULT = 39916801;
  static constexpr int VERSION_0 = 0;
  static constexpr int VERSION_8 = 8;

  file f;
  FILE* fp{};
  long end{};
  uint32_t key{};
  uint32_t table[256];

  gdc_file(const char* filename, const char* mode) : f(filename, mode){};
};
