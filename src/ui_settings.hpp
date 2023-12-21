#pragma once

#include "gdc_object.hpp"
#include "hot_slot.hpp"

class ui_settings : gdc_object {
 public:
  void read(gdc_file_reader*);
  void write(gdc_file_writer*) const;
  json to_json() const;

 private:
  static constexpr int BLOCK_14 = 14;
  static constexpr int VERSION_5 = 5;

  hot_slot slots[46];
  string unknown4[5];
  string unknown5[5];
  uint32_t unknown2;
  float cameraDistance;
  uint8_t unknown6[5];
  uint8_t unknown1;
  uint8_t unknown3;
};
