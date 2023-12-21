#include "skill.hpp"

void skill::read(gdc_file_reader& gdc) {
  name.read(gdc);
  level = gdc.read_int();
  enabled = gdc.read_byte();
  devotionLevel = gdc.read_int();
  experience = gdc.read_int();
  active = gdc.read_int();
  unknown1 = gdc.read_byte();
  unknown2 = gdc.read_byte();
  autoCastSkill.read(gdc);
  autoCastController.read(gdc);
}

void skill::write(gdc_file_writer& gdc) const {
  name.write(gdc);
  gdc.write_int(level);
  gdc.write_byte(enabled);
  gdc.write_int(devotionLevel);
  gdc.write_int(experience);
  gdc.write_int(active);
  gdc.write_byte(unknown1);
  gdc.write_byte(unknown2);
  autoCastSkill.write(gdc);
  autoCastController.write(gdc);
}

json skill::to_json() const {
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
