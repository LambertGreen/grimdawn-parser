#include "skill.hpp"

#include "gdc_file.hpp"

void skill::read(gdc_file* gdc) {
  name.read(gdc);
  level = gdc->read_int();
  enabled = gdc->read_byte();
  devotionLevel = gdc->read_int();
  experience = gdc->read_int();
  active = gdc->read_int();
  unknown1 = gdc->read_byte();
  unknown2 = gdc->read_byte();
  autoCastSkill.read(gdc);
  autoCastController.read(gdc);
}

json skill::get_json() const {
  json j;
  ADD_TO_JSON(j, name);
  ADD_TO_JSON(j, autoCastSkill);
  ADD_TO_JSON(j, autoCastController);
  ADD_TO_JSON(j, level);
  ADD_TO_JSON(j, devotionLevel);
  ADD_TO_JSON(j, experience);
  ADD_TO_JSON(j, active);
  ADD_TO_JSON(j, enabled);
  ADD_TO_JSON(j, unknown1);
  ADD_TO_JSON(j, unknown2);
  return j;
};
