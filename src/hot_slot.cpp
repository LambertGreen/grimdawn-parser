#include "hot_slot.hpp"

void hot_slot::read(gdc_file_reader* gdc) {
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

void hot_slot::write(gdc_file_writer* gdc) {
  gdc->write_int(type);

  if (type == 0) {
    skill.write(gdc);
    gdc->write_byte(isItemSkill);
    item.write(gdc);
    gdc->write_int(equipLocation);
  } else if (type == 4) {
    item.write(gdc);
    bitmapUp.write(gdc);
    bitmapDown.write(gdc);
    label.write(gdc);
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
