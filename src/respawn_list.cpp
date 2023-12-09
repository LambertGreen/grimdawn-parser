#include "respawn_list.hpp"

#include "block.hpp"
#include "gdc_file.hpp"

void respawn_list::read(gdc_file *gdc) {
  const int BLOCK = 5;
  const int VERSION = 1;

  block b;
  b.read_start(gdc);
  ENSURE(b.num == BLOCK, "Unexpected block number");
  ENSURE(b.version == VERSION, "Unexpected version number");

  const int uids_len = sizeof(uids) / sizeof(uids[0]);
  for (unsigned i = 0; i < uids_len; i++) {
    uids[i].read(gdc);
  }

  const int spawn_len = sizeof(spawns) / sizeof(spawns[0]);
  for (unsigned i = 0; i < spawn_len; i++) {
    spawns[i].read(gdc);
  }

  b.read_end(gdc);
}
