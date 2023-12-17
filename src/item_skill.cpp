#include "item_skill.hpp"

void item_skill::read(gdc_file_reader* gdc) {
  name.read(gdc);
  autoCastSkill.read(gdc);
  autoCastController.read(gdc);
  itemSlot = gdc->read_int();
  itemName.read(gdc);
}

void item_skill::write(gdc_file_writer* gdc) {
  name.write(gdc);
  autoCastSkill.write(gdc);
  autoCastController.write(gdc);
  gdc->write_int(itemSlot);
  itemName.write(gdc);
}

json item_skill::to_json() const {
  json j;
  ADD_TO_JSON(j, name);
  ADD_TO_JSON(j, autoCastSkill);
  ADD_TO_JSON(j, autoCastController);
  ADD_TO_JSON(j, itemName);
  ADD_TO_JSON(j, itemSlot);
  return j;
};
