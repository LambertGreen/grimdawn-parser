
#pragma once

#include "common.hpp"
#include "string.hpp"

struct item {
 public:
  void read(gdc_file* gdc);

  virtual json get_json() const {
    json j;
    ADD_TO_JSON(j, baseName);
    ADD_TO_JSON(j, prefixName);
    ADD_TO_JSON(j, suffixName);
    ADD_TO_JSON(j, modifierName);
    ADD_TO_JSON(j, transmuteName);
    ADD_TO_JSON(j, relicName);
    ADD_TO_JSON(j, relicBonus);
    ADD_TO_JSON(j, augmentName);
    ADD_TO_JSON(j, stackCount);
    ADD_TO_JSON(j, seed);
    ADD_TO_JSON(j, relicSeed);
    ADD_TO_JSON(j, unknown);
    ADD_TO_JSON(j, augmentSeed);
    ADD_TO_JSON(j, var1);

    return j;
  };

 private:
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
};
