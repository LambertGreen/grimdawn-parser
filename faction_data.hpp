#pragma once

#include "common.hpp"

class faction_data {
public:
  float value;
  float positiveBoost;
  float negativeBoost;
  uint8_t modified;
  uint8_t unlocked;

  void read(gdc_file *);
  void write(gdc_file *);
};
