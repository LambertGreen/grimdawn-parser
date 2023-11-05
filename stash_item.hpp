#pragma once

#include "common.hpp"
#include "item.hpp"

class stash_item : public item {
public:
  float x;
  float y;

  void read(gdc_file *);
  void write(gdc_file *);
};
