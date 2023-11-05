
#pragma once

#include "common.hpp"
#include "string.hpp"

class character_bio {
public:
  uint32_t level;
  uint32_t experience;
  uint32_t modifierPoints;
  uint32_t skillPoints;
  uint32_t devotionPoints;
  uint32_t totalDevotion;
  float physique;
  float cunning;
  float spirit;
  float health;
  float energy;

  void read(gdc_file *);
  void write(gdc_file *);
};
