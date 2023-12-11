#include "shrine_list.hpp"

#include "block.hpp"
#include "format.hpp"
#include "gdc_file.hpp"
#include "validation.hpp"

namespace {
const int BLOCK = 17;
const int VERSION = 2;
}  // namespace

void shrine_list::read(gdc_file* gdc) {
  block b;
  b.read_start(gdc);
  ENSURE(b.num == BLOCK, "shrine_list: Unexpected block number");
  ENSURE(b.version == VERSION, "shrine_list: Unexpected version number");

  for (unsigned i = 0; i < sizeof(uids) / sizeof(uids[0]); i++) {
    uids[i].read(gdc);
  }

  b.read_end(gdc);
}

json shrine_list::get_json() const {
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
