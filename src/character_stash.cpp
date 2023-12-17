#include "character_stash.hpp"

#include <string>
#include "block.hpp"
#include "gdc_file.hpp"
#include "validation.hpp"

namespace {
const int BLOCK = 4;
const int VERSION = 6;
}  // namespace

void character_stash::read(gdc_file_reader* gdc) {
  block b;
  b.read_start(gdc);
  ENSURE(b.num == BLOCK, "character_stash: Unexpected block number");
  ENSURE(b.version == VERSION, "character_stash: Unexpected version number");

  pages.read(gdc);

  b.read_end(gdc);
}

void character_stash::write(gdc_file_writer* gdc) {
  block b;
  b.write_start(gdc, BLOCK, VERSION);

  pages.write(gdc);

  b.write_end(gdc);
}

json character_stash::to_json() const {
  json j;
  for (int i = 0; i < pages.size(); i++) {
    j.emplace("page_" + std::to_string(i), pages[i].to_json());
  }
  return j;
};
