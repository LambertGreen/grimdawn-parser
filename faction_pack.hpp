#pragma once

#include "common.hpp"
#include "faction_data.hpp"
#include "vector.hpp"

class faction_pack {
public:
  vector<faction_data> factions;
  uint32_t faction;

  void read(gdc_file *);
  void write(gdc_file *);
};
