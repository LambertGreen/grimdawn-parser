#include "stash_page.hpp"

#include "block_field.hpp"
#include "gdc_file.hpp"
#include "validation.hpp"

namespace {
const int BLOCK = 0;
}

void stash_page::read(gdc_file* gdc) {
  block_field b;
  ENSURE(gdc->read_block_start(&b) == BLOCK,
         "stash_page: Unexpected block number");

  width = gdc->read_int();
  height = gdc->read_int();
  items.read(gdc);
  gdc->read_block_end(&b);
}

json stash_page::get_json() const {
  json j;
  ADD_TO_JSON(j, width);
  ADD_TO_JSON(j, height);

  for (int i = 0; i < items.size(); i++) {
    j.emplace("stash_item_" + std::to_string(i), items[i].get_json());
  }
  return j;
};
