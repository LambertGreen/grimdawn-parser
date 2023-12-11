#include "inventory_equipment.hpp"

#include "gdc_file.hpp"

void inventory_equipment::read(gdc_file* gdc) {
  item::read(gdc);

  attached = gdc->read_byte();
}

json inventory_equipment::get_json() const {
  json j = item::get_json();
  ADD_TO_JSON(j, attached);
  return j;
};
