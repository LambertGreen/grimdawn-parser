#pragma once

#include "faction_data.hpp"
#include "gdc_object.hpp"
#include "vector.hpp"

class faction_pack : gdc_object {
 public:
  void read(gdc_file*);
  json get_json() const;

 private:
  vector<faction_data> factions;
  uint32_t faction;
};
