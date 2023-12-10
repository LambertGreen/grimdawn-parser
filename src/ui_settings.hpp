#pragma once

#include "common.hpp"
#include "hot_slot.hpp"

class ui_settings {
 public:
  void read(gdc_file*);
  json get_json() const;

 private:
  hot_slot slots[46];
  string unknown4[5];
  string unknown5[5];
  uint32_t unknown2;
  float cameraDistance;
  uint8_t unknown6[5];
  uint8_t unknown1;
  uint8_t unknown3;
};
