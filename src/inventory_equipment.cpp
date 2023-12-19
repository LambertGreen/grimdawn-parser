#include "inventory_equipment.hpp"

#include "gdc_file.hpp"

void inventory_equipment::read(gdc_file_reader* gdc) {
  item::read(gdc);
  attached = gdc->read_byte();
}

void inventory_equipment::write(gdc_file_writer* gdc) const {
  item::write(gdc);
  gdc->write_byte(attached);
}

json inventory_equipment::to_json() const {
  json j = item::to_json();
  ADD_TO_JSON(j, attached);
  return j;
};
