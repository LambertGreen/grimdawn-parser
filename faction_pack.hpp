#pragma once

#include "common.hpp"
#include "faction_data.hpp"
#include "vector.hpp"

class faction_pack {
public:
  void read(gdc_file *);
  json get_json() const {
    json j;
    ADD_TO_JSON(j, faction);

    for (int i = 0; i < factions.size(); i++) {
      j.emplace("faction_" + formatNumber(2), factions[i].get_json());
    }
    return j;
  };

private:
  vector<faction_data> factions;
  uint32_t faction;
};
