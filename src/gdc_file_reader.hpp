

#pragma once

#include "gdc_file.hpp"

#include <_types/_uint8_t.h>
#include <stdint.h>

class block_field;

class gdc_file_reader : gdc_file {
 public:
  gdc_file_reader(const char* filename);

  void read_start();
  void read_version();
  void read_end();

  void read_key();
  uint32_t next_int();
  void update_key(void* ptr, uint32_t len);

  uint32_t read_int();
  uint16_t read_short();
  uint8_t read_byte();
  float read_float();

  uint32_t read_block_start(block_field& b);
  void read_block_end(block_field& b);
};
