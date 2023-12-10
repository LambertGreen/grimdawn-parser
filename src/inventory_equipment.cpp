#include "inventory_equipment.hpp"
#include "gdc_file.hpp"

void inventory_equipment::read(gdc_file* gdc) {
  item::read(gdc);

  attached = gdc->read_byte();
}
