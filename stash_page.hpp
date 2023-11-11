
#pragma once

#include "common.hpp"
#include "stash_item.hpp"
#include "vector.hpp"

class stash_page {
public:
  vector<stash_item> items;
  uint32_t width;
  uint32_t height;

  void read(gdc_file *);
  void write(gdc_file *);
};
