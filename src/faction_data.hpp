#pragma once

#include "gdc_object.hpp"

class faction_data : gdc_object {
 public:
  void read(gdc_file*);
  json get_json() const;

 private:
  float value;
  float positiveBoost;
  float negativeBoost;
  uint8_t modified;
  uint8_t unlocked;
};
