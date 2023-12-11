#include "item_skill.hpp"

void item_skill::read(gdc_file* gdc) {
  name.read(gdc);
  autoCastSkill.read(gdc);
  autoCastController.read(gdc);
  itemSlot = gdc->read_int();
  itemName.read(gdc);
}

json item_skill::get_json() const {
  json j;
  ADD_TO_JSON(j, name);
  ADD_TO_JSON(j, autoCastSkill);
  ADD_TO_JSON(j, autoCastController);
  ADD_TO_JSON(j, itemName);
  ADD_TO_JSON(j, itemSlot);
  return j;
};
