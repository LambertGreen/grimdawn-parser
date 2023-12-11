#include "character_stash.hpp"

#include <string>
#include "block.hpp"
#include "gdc_file.hpp"
#include "validation.hpp"

namespace {
const int BLOCK = 4;
const int VERSION = 6;
}  // namespace

void character_stash::read(gdc_file* gdc) {
  block b;
  b.read_start(gdc);
  ENSURE(b.num == BLOCK, "character_stash: Unexpected block number");
  ENSURE(b.version == VERSION, "character_stash: Unexpected version number");

  pages.read(gdc);
  b.read_end(gdc);
}

json character_stash::get_json() const {
  json j;
  for (int i = 0; i < pages.size(); i++) {
    j.emplace("page_" + std::to_string(i), pages[i].get_json());
  }
  return j;
};
