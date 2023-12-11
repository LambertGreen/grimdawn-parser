#include "hot_slot.hpp"

void hot_slot::read(gdc_file* gdc) {
  type = gdc->read_int();

  if (type == 0) {
    skill.read(gdc);
    isItemSkill = gdc->read_byte();
    item.read(gdc);
    equipLocation = gdc->read_int();
  } else if (type == 4) {
    item.read(gdc);
    bitmapUp.read(gdc);
    bitmapDown.read(gdc);
    label.read(gdc);
  }
}

json hot_slot::get_json() const {
  json j;
  ADD_TO_JSON(j, skill);
  ADD_TO_JSON(j, item);
  ADD_TO_JSON(j, bitmapUp);
  ADD_TO_JSON(j, bitmapDown);
  ADD_TO_JSON(j, label);
  ADD_TO_JSON(j, type);
  ADD_TO_JSON(j, equipLocation);
  ADD_TO_JSON(j, isItemSkill);
  return j;
};
