#pragma once

#include "gdc_object.hpp"
#include "string.hpp"

struct item : gdc_object {
 public:
  virtual void read(gdc_file_reader* gdc);
  virtual void write(gdc_file_writer* gdc) const;
  virtual json to_json() const;

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
