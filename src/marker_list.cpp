#include "marker_list.hpp"

#include "block.hpp"
#include "format.hpp"
#include "validation.hpp"

void marker_list::read(gdc_file_reader* gdc) {
  block b;
  b.read_start(gdc);
  ENSURE(b.num == BLOCK_7, "marker_list: Unexpected block number");
  ENSURE(b.version == VERSION_1, "marker_list: Unexpected version number");

  for (unsigned i = 0; i < sizeof(uids) / sizeof(uids[0]); i++) {
    uids[i].read(gdc);
  }

  b.read_end(gdc);
}

void marker_list::write(gdc_file_writer* gdc) const {
  block b;
  b.write_start(gdc, BLOCK_7, VERSION_1);

  for (unsigned i = 0; i < 3; i++) {
    uids[i].write(gdc);
  }

  b.write_end(gdc);
}

json marker_list::to_json() const {
  json j;

  for (int i = 0; i < sizeof(uids) / sizeof(uids[0]); i++) {
    json m;

    for (int j = 0; j < uids[i].size(); j++) {
      m.emplace("uid_" + formatNumber(i), uids[i][j].to_json());
    }

    j.emplace(json{"uids", m});
  }

  return j;
};
