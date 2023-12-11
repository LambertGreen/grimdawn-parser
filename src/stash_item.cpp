#include "stash_item.hpp"

#include "gdc_file.hpp"

void stash_item::read(gdc_file* gdc) {
  item::read(gdc);
  x = gdc->read_float();
  y = gdc->read_float();
}

json stash_item::get_json() const {
  json j = item::get_json();
  ADD_TO_JSON(j, x);
  ADD_TO_JSON(j, y);
  return j;
};
