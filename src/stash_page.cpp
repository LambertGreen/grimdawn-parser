#include "stash_page.hpp"

#include "block_field.hpp"
#include "gdc_file.hpp"
#include "validation.hpp"

namespace {
const int BLOCK = 0;
}

void stash_page::read(gdc_file_reader* gdc) {
  block_field b;
  ENSURE(gdc->read_block_start(&b) == BLOCK,
         "stash_page: Unexpected block number");

  width = gdc->read_int();
  height = gdc->read_int();
  items.read(gdc);
  gdc->read_block_end(&b);
}

void stash_page::write(gdc_file_writer* gdc) {
  block_field b;
  gdc->write_block_start(&b, BLOCK);

  gdc->write_int(width);
  gdc->write_int(height);
  items.write(gdc);

  gdc->write_block_end(&b);
}

json stash_page::to_json() const {
  json j;
  ADD_TO_JSON(j, width);
  ADD_TO_JSON(j, height);

  for (int i = 0; i < items.size(); i++) {
    j.emplace("stash_item_" + std::to_string(i), items[i].to_json());
  }
  return j;
};
