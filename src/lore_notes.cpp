#include "lore_notes.hpp"

json lore_notes::get_json() const {
  json j;

  for (int i = 0; i < names.size(); i++) {
    j.emplace("names_" + formatNumber(i, 3), names[i]);
  }

  return j;
};
