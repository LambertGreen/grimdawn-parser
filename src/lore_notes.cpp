#include "lore_notes.hpp"

#include "block.hpp"
#include "format.hpp"
#include "validation.hpp"

void lore_notes::read(gdc_file_reader& gdc) {
  block b;
  b.read_start(gdc);
  ENSURE(b.num == BLOCK_12, "lore_notes: Unexpected block number");
  ENSURE(b.version == VERSION_1, "lore_notes: Unexpected version number");

  names.read(gdc);

  b.read_end(gdc);
}

void lore_notes::write(gdc_file_writer& gdc) const {
  block b;
  b.write_start(gdc, BLOCK_12, VERSION_1);

  names.write(gdc);

  b.write_end(gdc);
}

json lore_notes::to_json() const {
  json j;

  for (int i = 0; i < names.size(); i++) {
    j.emplace("names_" + formatNumber(i, 3), names[i]);
  }

  return j;
};
