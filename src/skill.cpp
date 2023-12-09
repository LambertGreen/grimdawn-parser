#include "skill.hpp"
#include "gdc_file.hpp"

void skill::read(gdc_file *gdc) {
  name.read(gdc);
  LOG(name);

  level = gdc->read_int();
  LOG_N(level);

  enabled = gdc->read_byte();
  LOG_N(enabled);

  devotionLevel = gdc->read_int();
  LOG_N(devotionLevel);

  experience = gdc->read_int();
  LOG_N(experience);

  active = gdc->read_int();
  LOG_N(active);

  unknown1 = gdc->read_byte();
  LOG_N(unknown1);

  unknown2 = gdc->read_byte();
  LOG_N(unknown2);

  autoCastSkill.read(gdc);
  autoCastController.read(gdc);
}

