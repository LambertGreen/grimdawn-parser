#include "inventory_item.hpp"

#include "gdc_file.hpp"


void inventory_item::read(gdc_file *gdc) {
  item::read(gdc);
  x = gdc->read_int();
  y = gdc->read_int();
}
