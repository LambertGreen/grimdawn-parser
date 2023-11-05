#pragma once

#include "common.hpp"
#include "string.hpp"

class item_skill {
public:
  string name;
  string autoCastSkill;
  string autoCastController;
  string itemName;
  uint32_t itemSlot;

  void read(gdc_file *);
  void write(gdc_file *);
};
