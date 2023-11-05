#pragma once

#include "common.hpp"
#include "string.hpp"

class skill {
public:
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

  void read(gdc_file *);
  void write(gdc_file *);
};
