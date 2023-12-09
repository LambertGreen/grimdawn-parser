#include "block.hpp"

#include "gdc_file.hpp"


void block::read_start(gdc_file *gdc) {

	num = gdc->read_block_start(&b);
	version = gdc->read_int();
}

void block::read_end(gdc_file *gdc) { gdc->read_block_end(&b); }
