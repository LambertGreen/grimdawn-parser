#include "block.hpp"

#include "gdc_file.hpp"

void block::read_start(gdc_file_reader* gdc) {
  num = gdc->read_block_start(&b);
  version = gdc->read_int();
}

void block::write_start(gdc_file_writer* gdc, int num, int version) {
  gdc->write_block_start(&b, num);
  gdc->write_int(version);
}

void block::read_end(gdc_file_reader* gdc) {
  gdc->read_block_end(&b);
}
void block::write_end(gdc_file_writer* gdc) {
  gdc->write_block_end(&b);
}
