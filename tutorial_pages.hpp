#pragma once

#include "common.hpp"
#include "vector.hpp"

class tutorial_pages {
public:
  vector<uint32_t> pages;

  void read(gdc_file *);
  void write(gdc_file *);
};
