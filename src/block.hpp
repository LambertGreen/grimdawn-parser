#pragma once

#include "common.hpp"

#include "block_field.hpp"

class block {
public:
  int num{};
  int version{};
  block_field b;

  void read_start(gdc_file *);
  void read_end(gdc_file *);
};
