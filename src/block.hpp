#pragma once

#include "block_field.hpp"

class gdc_file;

class block {
 public:
  int num{};
  int version{};
  block_field b;

  void read_start(gdc_file*);
  void read_end(gdc_file*);
};

void validate_block(const block& b, int expected_block, int expected_version);
