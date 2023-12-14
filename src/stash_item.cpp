#include "stash_item.hpp"

#include "gdc_file.hpp"

void stash_item::read(gdc_file_reader* gdc) {
  item::read(gdc);
  x = gdc->read_float();
  y = gdc->read_float();
}

void stash_item::write(gdc_file_writer* gdc) {
  item::write(gdc);
  gdc->write_float(x);
  gdc->write_float(y);
}

json stash_item::get_json() const {
  json j = item::get_json();
  ADD_TO_JSON(j, x);
  ADD_TO_JSON(j, y);
  return j;
};
