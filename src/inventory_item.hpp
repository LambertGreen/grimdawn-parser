
#pragma once

#include "common.hpp"
#include "item.hpp"

class inventory_item : public item {
public:
  uint32_t x;
  uint32_t y;

  void read(gdc_file *);
  void write(gdc_file *);
};
