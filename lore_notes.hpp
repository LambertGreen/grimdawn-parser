#pragma once

#include "common.hpp"
#include "string.hpp"
#include "vector.hpp"

class lore_notes {
public:
  vector<string> names;

  void read(gdc_file *);
  void write(gdc_file *);
};
