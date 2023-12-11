#pragma once

#include "item.hpp"

class inventory_equipment : public item {
 public:
  void read(gdc_file* gdc);
  json get_json() const;

 private:
  uint8_t attached;
};
