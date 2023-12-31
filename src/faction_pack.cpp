#include "faction_pack.hpp"

#include "block.hpp"
#include "format.hpp"
#include "validation.hpp"

void faction_pack::read(gdc_file_reader& gdc) {
  block b;
  b.read_start(gdc);
  ENSURE(b.num == BLOCK_13, "faction_pack: Unexpected block number");
  ENSURE(b.version == VERSION_5, "faction_pack: Unexpected version number");

  faction = gdc.read_int();
  factions.read(gdc);

  b.read_end(gdc);
}

void faction_pack::write(gdc_file_writer& gdc) const {
  block b;
  b.write_start(gdc, BLOCK_13, VERSION_5);

  gdc.write_int(faction);
  factions.write(gdc);

  b.write_end(gdc);
}

json faction_pack::to_json() const {
  json j;
  ADD_TO_JSON(j, faction);

  for (int i = 0; i < factions.size(); i++) {
    j.emplace("faction_" + formatNumber(2), factions[i].to_json());
  }
  return j;
};
