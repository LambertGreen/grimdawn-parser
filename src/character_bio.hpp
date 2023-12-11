
#pragma once

#include "gdc_object.hpp"

class character_bio : gdc_object {
 public:
  void read(gdc_file* gdc);
  json get_json() const;

 private:
  uint32_t level{};
  uint32_t experience{};
  uint32_t modifierPoints{};
  uint32_t skillPoints{};
  uint32_t devotionPoints{};
  uint32_t totalDevotion{};
  float physique{};
  float cunning{};
  float spirit{};
  float health{};
  float energy{};
};
