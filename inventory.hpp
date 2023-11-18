#pragma once

#include "common.hpp"
#include "inventory_equipment.hpp"
#include "inventory_sack.hpp"
#include <string>

class inventory {
public:
  void read(gdc_file *gdc);

  json get_json() const {
    json j;
    ADD_TO_JSON(j, focused);
    ADD_TO_JSON(j, selected);
    ADD_TO_JSON(j, flag);
    ADD_TO_JSON(j, useAlternate);
    ADD_TO_JSON(j, alternate1);
    ADD_TO_JSON(j, alternate2);

    for (int i = 0; i < 12; i++) {
      j.emplace("equipment_" + std::to_string(i), equipment[i].get_json());
    }

    for (int i = 0; i < 2; i++) {
      j.emplace("weapon1_" + std::to_string(i), weapon1[i].get_json());
    }

    for (int i = 0; i < 2; i++) {
      j.emplace("weapon2_" + std::to_string(i), weapon2[i].get_json());
    }

    for (int i = 0; i < sacks.size(); i++) {
      json m;
      m.emplace("sack_" + std::to_string(i), sacks[i].get_json());
    }
    return j;
  };

private:
  vector<inventory_sack> sacks;
  inventory_equipment equipment[12];
  inventory_equipment weapon1[2];
  inventory_equipment weapon2[2];
  uint32_t focused;
  uint32_t selected;
  uint8_t flag;
  uint8_t useAlternate;
  uint8_t alternate1;
  uint8_t alternate2;
};
