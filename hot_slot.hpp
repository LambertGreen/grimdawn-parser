#pragma once

#include "common.hpp"
#include "string.hpp"
#include "wstring.hpp"

class hot_slot {
public:
  string skill;
  string item;
  string bitmapUp;
  string bitmapDown;
  wstring label;
  uint32_t type;
  uint32_t equipLocation;
  uint8_t isItemSkill;

  void read(gdc_file *);
  void write(gdc_file *);
};
