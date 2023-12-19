#pragma once

#include "faction_data.hpp"
#include "gdc_object.hpp"
#include "vector.hpp"

class faction_pack : gdc_object {
 public:
  void read(gdc_file_reader*);
  void write(gdc_file_writer*) const;
  json to_json() const;

 private:
  static constexpr int BLOCK = 13;
  static constexpr int VERSION = 5;

  vector<faction_data> factions;
  uint32_t faction;
};
