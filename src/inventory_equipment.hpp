#pragma once

#include "common.hpp"
#include "item.hpp"

class inventory_equipment : public item {
public:
  void read(gdc_file *gdc);

  json get_json() const {
    json j = item::get_json();
    ADD_TO_JSON(j, attached);
    return j;
  };

private:
  uint8_t attached;
};
