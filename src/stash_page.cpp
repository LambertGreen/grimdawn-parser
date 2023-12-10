#include "stash_page.hpp"

#include "block_field.hpp"
#include "gdc_file.hpp"

void stash_page::read(gdc_file* gdc) {
  const int BLOCK = 0;

  block_field b;
  const auto block_val = gdc->read_block_start(&b);
  ENSURE(block_val == BLOCK, "Unexpected block number");

  width = gdc->read_int();
  height = gdc->read_int();

  items.read(gdc);

  gdc->read_block_end(&b);
}
