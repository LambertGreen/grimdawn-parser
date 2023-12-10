#pragma once

#include "common.hpp"
#include "string.hpp"
#include "vector.hpp"

class lore_notes {
 public:
  void read(gdc_file*);
  json get_json() const {
    json j;

    for (int i = 0; i < names.size(); i++) {
      j.emplace("names_" + formatNumber(i, 3), names[i]);
    }
    return j;
  };

 private:
  vector<string> names;
};
