#include "skill_map.hpp"

void skill_map::read(gdc_file* gdc) {
  skill.read(gdc);
  active = gdc->read_int();
}

json skill_map::get_json() const {
  auto j = json{{"skill", skill}, {"acitive", active}};
  return j;
}
