#include "character_stash.hpp"

#include "block.hpp"
#include "gdc_file.hpp"

void character_stash::read(gdc_file *gdc) {
  const int BLOCK = 4;
  const int VERSION = 6;

  block b;
  b.read_start(gdc);
  ENSURE(b.num == BLOCK, "Unexpected block number");
  ENSURE(b.version == VERSION, "Unexpected version number");

  pages.read(gdc);

  b.read_end(gdc);
}
