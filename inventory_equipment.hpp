#pragma once

#include "common.hpp"
#include "item.hpp"

class inventory_equipment : public item {
public:
  uint8_t attached;

  void read(gdc_file *);
  void write(gdc_file *);
};
