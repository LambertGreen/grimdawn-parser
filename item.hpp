
#pragma once

#include "common.hpp"
#include "string.hpp"

class item {
public:
  string baseName;
  string prefixName;
  string suffixName;
  string modifierName;
  string transmuteName;
  string relicName;
  string relicBonus;
  string augmentName;
  uint32_t stackCount;
  uint32_t seed;
  uint32_t relicSeed;
  uint32_t unknown;
  uint32_t augmentSeed;
  uint32_t var1;

  void read(gdc_file *);
  void write(gdc_file *);
};
