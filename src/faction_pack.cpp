#include "faction_pack.hpp"

#include "block_field.hpp"
#include "format.hpp"
#include "validation.hpp"

namespace {
const int BLOCK = 13;
const int VERSION = 5;
}  // namespace

void faction_pack::read(gdc_file* gdc) {
  block_field b;
  ENSURE(gdc->read_block_start(&b) == BLOCK,
         "faction_pack: Unexpected block number");
  ENSURE(gdc->read_int() == VERSION, "faction_pack: Unexpected version number");

  faction = gdc->read_int();
  factions.read(gdc);

  gdc->read_block_end(&b);
}

json faction_pack::get_json() const {
  json j;
  ADD_TO_JSON(j, faction);

  for (int i = 0; i < factions.size(); i++) {
    j.emplace("faction_" + formatNumber(2), factions[i].get_json());
  }
  return j;
};
