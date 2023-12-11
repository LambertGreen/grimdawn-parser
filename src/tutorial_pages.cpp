#include "tutorial_pages.hpp"

#include "block_field.hpp"
#include "validation.hpp"

namespace {
const int BLOCK = 15;
const int VERSION = 1;
}  // namespace

void tutorial_pages::read(gdc_file* gdc) {
  block_field b;
  ENSURE(gdc->read_block_start(&b) == BLOCK,
         "tutorial_pages: Unexpected block number");
  ENSURE(gdc->read_int() == VERSION,
         "tutorial_pages: Unexpected version number");

  uint32_t n = gdc->read_int();
  pages.resize(n);

  for (uint32_t i = 0; i < n; i++) {
    pages[i] = gdc->read_int();
  }

  gdc->read_block_end(&b);
}

json tutorial_pages::get_json() const {
  json j;

  ADD_TO_JSON(j, pages);
  return j;
};
