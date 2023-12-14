#include "inventory_equipment.hpp"

#include "gdc_file.hpp"

void inventory_equipment::read(gdc_file_reader* gdc) {
  item::read(gdc);
  attached = gdc->read_byte();
}

void inventory_equipment::write(gdc_file_writer* gdc) {
  item::write(gdc);
  gdc->write_byte(attached);
}

json inventory_equipment::get_json() const {
  json j = item::get_json();
  ADD_TO_JSON(j, attached);
  return j;
};
