#include "stash_item.hpp"
#include "gdc_file.hpp"

void stash_item::read(gdc_file *gdc) {
  item::read(gdc);
  x = gdc->read_float();
  LOG_N(x);

  y = gdc->read_float();
  LOG_N(y);
}

