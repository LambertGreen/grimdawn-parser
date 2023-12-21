#pragma once

#include "gdc_object.hpp"
#include "inventory_equipment.hpp"
#include "inventory_sack.hpp"

class inventory : gdc_object {
 public:
  virtual void read(gdc_file_reader* gdc);
  virtual void write(gdc_file_writer* gdc) const;
  virtual json to_json() const;

 private:
  static constexpr int BLOCK_3 = 3;
  static constexpr int VERSION_4 = 4;

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
