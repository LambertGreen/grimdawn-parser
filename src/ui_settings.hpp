#pragma once

#include "common.hpp"
#include "hot_slot.hpp"

class ui_settings {
 public:
  void read(gdc_file*);

  json get_json() const {
    json j;
    ADD_TO_JSON(j, unknown1);
    ADD_TO_JSON(j, unknown2);
    ADD_TO_JSON(j, unknown3);
    ADD_TO_JSON(j, unknown4);
    ADD_TO_JSON(j, unknown5);
    ADD_TO_JSON(j, unknown6);
    ADD_TO_JSON(j, cameraDistance);

    json m;
    ADD_TO_JSON(j, unknown1);
    for (int i = 0; i < sizeof(slots) / sizeof(slots[0]); i++) {
      m.emplace("hot_slot_" + formatNumber(i), slots[i].get_json());
    }
    j.emplace("hot_slots", m);

    return j;
  };

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
