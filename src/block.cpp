#include "block.hpp"

#include "gdc_file.hpp"

void block::read_start(gdc_file* gdc) {
  num = gdc->read_block_start(&b);
  version = gdc->read_int();
}

void block::read_end(gdc_file* gdc) {
  gdc->read_block_end(&b);
}

void validate_block(const block& b, int expected_block, int expected_version) {
  ENSURE(b.num == expected_block, "Unexpected block number");
  ENSURE(b.version == expected_version, "Unexpected version number");
}
