#include "marker_list.hpp"

#include "block.hpp"
#include "gdc_file.hpp"

namespace {
const int BLOCK = 7;
const int VERSION = 1;
}  // namespace

void marker_list::read(gdc_file* gdc) {
  block b;
  b.read_start(gdc);
  validate_block(b, BLOCK, VERSION);

  for (unsigned i = 0; i < sizeof(uids) / sizeof(uids[0]); i++) {
    uids[i].read(gdc);
  }

  b.read_end(gdc);
}

json marker_list::get_json() const {
  json j;

  for (int i = 0; i < sizeof(uids) / sizeof(uids[0]); i++) {
    json m;

    for (int j = 0; j < uids[i].size(); j++) {
      m.emplace("uid_" + formatNumber(i), uids[i][j].get_json());
    }

    j.emplace(json{"uids", m});
  }

  return j;
};
