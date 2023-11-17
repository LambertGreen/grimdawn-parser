
#pragma once

#include "common.hpp"
#include "string.hpp"

class character_bio {
public:
  void read(gdc_file *gdc);

  json get_json() const {
    json j;
    ADD_TO_JSON(j, level);
    ADD_TO_JSON(j, experience);
    ADD_TO_JSON(j, modifierPoints);
    ADD_TO_JSON(j, skillPoints);
    ADD_TO_JSON(j, devotionPoints);
    ADD_TO_JSON(j, totalDevotion);
    ADD_TO_JSON(j, physique);
    ADD_TO_JSON(j, cunning);
    ADD_TO_JSON(j, spirit);
    ADD_TO_JSON(j, health);
    ADD_TO_JSON(j, energy);

    return j;
  };

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
