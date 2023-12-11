#include "lore_notes.hpp"

#include "block_field.hpp"
#include "format.hpp"
#include "validation.hpp"

namespace {
const int BLOCK = 12;
const int VERSION = 1;
}  // namespace

void lore_notes::read(gdc_file* gdc) {
  block_field b;
  ENSURE(gdc->read_block_start(&b) == BLOCK,
         "lore_notes: Unexpected block number");
  ENSURE(gdc->read_int() == VERSION, "lore_notes: Unexpected version number");

  names.read(gdc);

  gdc->read_block_end(&b);
}

json lore_notes::get_json() const {
  json j;

  for (int i = 0; i < names.size(); i++) {
    j.emplace("names_" + formatNumber(i, 3), names[i]);
  }

  return j;
};
