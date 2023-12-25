#pragma once

#include "file.hpp"

#include <_types/_uint8_t.h>
#include <stdint.h>

class gdc_file {
 protected:
  static constexpr int XOR_BITMAP = 0x55555555;
  static constexpr int VERSION = 0x58434447;
  static constexpr int FACTORIAL_PRIME = 39916801;
  static constexpr int VERSION_0 = 0;
  static constexpr int VERSION_8 = 8;

  file _f;
  FILE* _fp{};
  long _end{};
  uint32_t _key{};
  uint32_t _table[256]{};

  gdc_file(const char* filename, const char* mode) : _f(filename, mode){};
  void build_table();
  void update_key(void* ptr, uint32_t len);
};
