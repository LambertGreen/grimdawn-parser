#pragma once

#include "gdc_object.hpp"
#include "string.hpp"
#include "wstring.hpp"

class hot_slot : gdc_object {
 public:
  void read(gdc_file_reader*);
  void write(gdc_file_writer*);
  json get_json() const;

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
