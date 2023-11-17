
#pragma once

#include "common.hpp"
#include "string.hpp"

struct item {
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

  nlohmann::json get_json() {
    nlohmann::json j;
    j["base-name"] = baseName;
    j["prefix-name"] = prefixName;
    j["suffix-name"] = suffixName;
    j["modifier-name"] = modifierName;
    j["transmute-name"] = transmuteName;

    return j;
  }
};
