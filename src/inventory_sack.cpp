#include "inventory_sack.hpp"

#include "block_field.hpp"
#include "gdc_file.hpp"
#include "validation.hpp"

namespace {
const int BLOCK = 0;
}

void inventory_sack::read(gdc_file_reader* gdc) {
  block_field b;
  ENSURE(gdc->read_block_start(&b) == BLOCK,
         "inventory_sack: Unexpected block number");

  tempBool = gdc->read_byte();
  items.read(gdc);

  gdc->read_block_end(&b);
}

void inventory_sack::write(gdc_file_writer* gdc) {
  block_field b;
  gdc->write_block_start(&b, BLOCK);

  gdc->write_byte(tempBool);
  items.write(gdc);

  gdc->write_block_end(&b);
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
