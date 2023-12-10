#pragma once

#include "common.hpp"
#include "string.hpp"

class item_skill {
 public:
  void read(gdc_file*);
  json get_json() const {
    json j;
    ADD_TO_JSON(j, name);
    ADD_TO_JSON(j, autoCastSkill);
    ADD_TO_JSON(j, autoCastController);
    ADD_TO_JSON(j, itemName);
    ADD_TO_JSON(j, itemSlot);
    return j;
  };

 private:
  string name;
  string autoCastSkill;
  string autoCastController;
  string itemName;
  uint32_t itemSlot;
};
