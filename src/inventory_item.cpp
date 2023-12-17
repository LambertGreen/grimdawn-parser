#include "inventory_item.hpp"

#include "gdc_file.hpp"

void inventory_item::read(gdc_file_reader* gdc) {
  item::read(gdc);
  x = gdc->read_int();
  y = gdc->read_int();
}

void inventory_item::write(gdc_file_writer* gdc) {
  item::write(gdc);
  gdc->write_int(x);
  gdc->write_int(y);
}

json inventory_item::to_json() const {
  json j = item::to_json();
  ADD_TO_JSON(j, x);
  ADD_TO_JSON(j, y);
  return j;
}
