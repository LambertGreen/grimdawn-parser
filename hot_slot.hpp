#pragma once

#include "common.hpp"
#include "string.hpp"
#include "wstring.hpp"

class hot_slot {
public:
  void read(gdc_file *);
  json get_json() const {
    json j;
    ADD_TO_JSON(j, skill);
    ADD_TO_JSON(j, item);
    ADD_TO_JSON(j, bitmapUp);
    ADD_TO_JSON(j, bitmapDown);
    ADD_TO_JSON(j, label);
    ADD_TO_JSON(j, type);
    ADD_TO_JSON(j, equipLocation);
    ADD_TO_JSON(j, isItemSkill);
    return j;
  };

private:
  string skill;
  string item;
  string bitmapUp;
  string bitmapDown;
  wstring label;
  uint32_t type;
  uint32_t equipLocation;
  uint8_t isItemSkill;
};
