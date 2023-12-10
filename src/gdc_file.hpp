#pragma once

#include "common.hpp"

#include "file.hpp"

class block_field;

class gdc_file {
 private:
  file f;
  FILE* fp{};

  long end{};
  uint32_t key{};
  uint32_t table[256];

 public:
  gdc_file(const char* filename);
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
  uint32_t read_block_start(block_field* b);
  void read_block_end(block_field* b);
  void write_int(uint32_t val);
  void write_short(uint16_t val);
  void write_byte(uint8_t val);
  void write_float(float val);
  void write_block_start(block_field* b, uint32_t n);
  void write_block_end(block_field* b);
};
