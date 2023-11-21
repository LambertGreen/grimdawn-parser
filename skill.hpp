#pragma once

#include "common.hpp"
#include "string.hpp"

class skill {
public:
  void read(gdc_file *);

  json get_json() const {
    json j;
    ADD_TO_JSON(j, name);
    ADD_TO_JSON(j, autoCastSkill);
    ADD_TO_JSON(j, autoCastController);
    ADD_TO_JSON(j, level);
    ADD_TO_JSON(j, devotionLevel);
    ADD_TO_JSON(j, experience);
    ADD_TO_JSON(j, active);
    ADD_TO_JSON(j, enabled);
    ADD_TO_JSON(j, unknown1);
    ADD_TO_JSON(j, unknown2);
    return j;
  };

private:
  string name;
  string autoCastSkill;
  string autoCastController;
  uint32_t level;
  uint32_t devotionLevel;
  uint32_t experience;
  uint32_t active;
  uint8_t enabled;
  uint8_t unknown1;
  uint8_t unknown2;
};
