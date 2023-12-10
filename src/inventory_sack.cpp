#include "inventory_sack.hpp"

#include "block_field.hpp"
#include "gdc_file.hpp"

void inventory_sack::read(gdc_file* gdc) {
  block_field b;

  ENSURE(gdc->read_block_start(&b) == 0, "Unexpected block number");

  tempBool = gdc->read_byte();
  items.read(gdc);

  gdc->read_block_end(&b);
}

json inventory_sack::get_json() const {
  json j;
  ADD_TO_JSON(j, tempBool);

  json m;
  for (int i = 0; i < items.size(); i++) {
    m.emplace("inventory_item_" + std::to_string(i), items[i].get_json());
  }

  j.emplace("inventory_items", m);
  return j;
};
