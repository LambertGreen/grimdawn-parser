#include "inventory_sack.hpp"

json inventory_sack::get_json() const {
  json j;
  ADD_TO_JSON(j, tempBool);

  json m;
  for (int i = 0; i < items.size(); i++) {
    m.emplace("inventory_item_" + std::to_string(i), items[i].get_json());
  }

  j.emplace("inventory_items", m);
  return j;
};
