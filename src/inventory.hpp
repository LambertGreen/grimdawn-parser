#pragma once

#include "common.hpp"
#include "inventory_equipment.hpp"
#include "inventory_sack.hpp"

class inventory {
 public:
  void read(gdc_file* gdc);
  json get_json() const;

 private:
  vector<inventory_sack> sacks;
  inventory_equipment equipment[12];
  inventory_equipment weapon1[2];
  inventory_equipment weapon2[2];
  uint32_t focused;
  uint32_t selected;
  uint8_t flag;
  uint8_t useAlternate;
  uint8_t alternate1;
  uint8_t alternate2;
};
