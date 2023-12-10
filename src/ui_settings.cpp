#include "ui_settings.hpp"

json ui_settings::get_json() const {
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
