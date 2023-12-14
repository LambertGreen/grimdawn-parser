#include "faction_pack.hpp"

#include "block.hpp"
#include "format.hpp"
#include "validation.hpp"

namespace {
const int BLOCK = 13;
const int VERSION = 5;
}  // namespace

void faction_pack::read(gdc_file_reader* gdc) {
  block b;
  b.read_start(gdc);
  ENSURE(b.num == BLOCK, "faction_pack: Unexpected block number");
  ENSURE(b.version == VERSION, "faction_pack: Unexpected version number");

  faction = gdc->read_int();
  factions.read(gdc);

  b.read_end(gdc);
}

void faction_pack::write(gdc_file_writer* gdc) {
  block b;
  b.write_start(gdc, BLOCK, VERSION);

  gdc->write_int(faction);
  factions.write(gdc);

  b.write_end(gdc);
}

json faction_pack::get_json() const {
  json j;
  ADD_TO_JSON(j, faction);

  for (int i = 0; i < factions.size(); i++) {
    j.emplace("faction_" + formatNumber(2), factions[i].get_json());
  }
  return j;
};
