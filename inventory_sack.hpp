
#pragma once

#include "common.hpp"
#include "inventory_item.hpp"
#include "vector.hpp"

class inventory_sack {
public:
  vector<inventory_item> items;
  uint8_t tempBool;

  void read(gdc_file *);
  void write(gdc_file *);
};
