#pragma once

#include "common.hpp"
#include "string.hpp"

class item_skill {
 public:
  void read(gdc_file*);
  json get_json() const;

 private:
  string name;
  string autoCastSkill;
  string autoCastController;
  string itemName;
  uint32_t itemSlot;
};
