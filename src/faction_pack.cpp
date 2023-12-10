#include "faction_pack.hpp"

json faction_pack::get_json() const {
  json j;
  ADD_TO_JSON(j, faction);

  for (int i = 0; i < factions.size(); i++) {
    j.emplace("faction_" + formatNumber(2), factions[i].get_json());
  }
  return j;
};
