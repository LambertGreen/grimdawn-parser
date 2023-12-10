#include "shrine_list.hpp"

#include "block.hpp"
#include "gdc_file.hpp"

void shrine_list::read(gdc_file* gdc) {
  const int BLOCK = 17;
  const int VERSION = 2;

  block b;
  b.read_start(gdc);
  ENSURE(b.num == BLOCK, "Unexpected block number");
  ENSURE(b.version == VERSION, "Unexpected version number");

  for (unsigned i = 0; i < sizeof(uids) / sizeof(uids[0]); i++) {
    uids[i].read(gdc);
  }

  b.read_end(gdc);
}
