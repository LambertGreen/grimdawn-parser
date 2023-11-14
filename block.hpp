#pragma once

#include "common.hpp"

struct block_field {
  uint32_t len{};
  long end{};
};

class block {
public:
  int num;
  int version;
  block_field b;

  void read_start(gdc_file *);
  void read_end(gdc_file *);
};
