#include "skill_map.hpp"

void skill_map::read(gdc_file_reader* gdc) {
  skill.read(gdc);
  active = gdc->read_int();
}

void skill_map::write(gdc_file_writer* gdc) {
  skill.write(gdc);
  gdc->write_int(active);
}

json skill_map::get_json() const {
  auto j = json{{"skill", skill}, {"acitive", active}};
  return j;
}
