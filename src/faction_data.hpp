#pragma once

#include "gdc_object.hpp"

class faction_data : gdc_object {
 public:
  void read(gdc_file_reader*);
  void write(gdc_file_writer*);
  json to_json() const;

 private:
  float value;
  float positiveBoost;
  float negativeBoost;
  uint8_t modified;
  uint8_t unlocked;
};
