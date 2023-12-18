
#pragma once

#include "gdc_file.hpp"

#include <_types/_uint8_t.h>
#include <stdint.h>

class block_field;

class gdc_file_writer : gdc_file {
 public:
  gdc_file_writer(const char* filename);

  void write_start();
  void write_version();
  void write_end();

  void write_int(uint32_t val);
  void write_short(uint16_t val);
  void write_byte(uint8_t val);
  void write_float(float val);

  void write_block_start(block_field* b, uint32_t n);
  void write_block_end(block_field* b);
};
