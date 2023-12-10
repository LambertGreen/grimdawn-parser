#pragma once

#include "common.hpp"
#include "faction_data.hpp"
#include "vector.hpp"

class faction_pack {
 public:
  void read(gdc_file*);
  json get_json() const;

 private:
  vector<faction_data> factions;
  uint32_t faction;
};
