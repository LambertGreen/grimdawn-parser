#include "respawn_list.hpp"

#include "block.hpp"
#include "format.hpp"
#include "gdc_file.hpp"
#include "validation.hpp"

namespace {
const int BLOCK = 5;
const int VERSION = 1;
}  // namespace

void respawn_list::read(gdc_file_reader* gdc) {
  block b;
  b.read_start(gdc);
  ENSURE(b.num == BLOCK, "respawn_list: Unexpected block number");
  ENSURE(b.version == VERSION, "respawn_list: Unexpected version number");

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

void respawn_list::write(gdc_file_writer* gdc) {
  block b;
  b.write_start(gdc, BLOCK, VERSION);

  for (unsigned i = 0; i < 3; i++) {
    uids[i].write(gdc);
  }

  for (unsigned i = 0; i < 3; i++) {
    spawns[i].write(gdc);
  }

  b.write_end(gdc);
}

json respawn_list::get_json() const {
  json j;

  for (int i = 0; i < sizeof(uids) / sizeof(uids[0]); i++) {
    json m;
    for (int j = 0; j < uids[i].size(); j++) {
      m.emplace("uid_" + formatNumber(i), uids[i][j].get_json());
    }

    j.emplace(json{"uids", m});
  }

  for (int i = 0; i < sizeof(spawns) / sizeof(spawns[0]); i++) {
    j.emplace("spawn_" + std::to_string(i), spawns[i].get_json());
  }
  return j;
};
