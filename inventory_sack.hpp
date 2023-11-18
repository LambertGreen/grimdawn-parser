
#pragma once

#include "common.hpp"
#include "inventory_item.hpp"
#include "vector.hpp"
#include <string>

class inventory_sack {
public:
  void read(gdc_file *);

  json get_json() const {
    json j;
    ADD_TO_JSON(j, tempBool);

    json m;
    for (int i = 0; i < items.size(); i++) {
      m.emplace("inventory_item_" + std::to_string(i), items[i].get_json());
    }

    j.emplace("inventory_items", m);
    return j;
  };

private:
  vector<inventory_item> items{};
  uint8_t tempBool{};
};
