#pragma once

#include "common.hpp"
#include "string.hpp"
#include "vector.hpp"

class trigger_tokens {
public:
  vector<string> tokens[3];

  void read(gdc_file *);
  void write(gdc_file *);
};
