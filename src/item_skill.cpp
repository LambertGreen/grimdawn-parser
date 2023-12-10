#include "item_skill.hpp"

json item_skill::get_json() const {
  json j;
  ADD_TO_JSON(j, name);
  ADD_TO_JSON(j, autoCastSkill);
  ADD_TO_JSON(j, autoCastController);
  ADD_TO_JSON(j, itemName);
  ADD_TO_JSON(j, itemSlot);
  return j;
};
