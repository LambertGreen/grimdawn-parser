#pragma once

#include "common.hpp"

class faction_data {
public:
  void read(gdc_file *);

  json get_json() const {
    json j;
    ADD_TO_JSON(j, value);
    ADD_TO_JSON(j, positiveBoost);
    ADD_TO_JSON(j, negativeBoost);
    ADD_TO_JSON(j, modified);
    ADD_TO_JSON(j, unlocked);
    return j;
  };

private:
  float value;
  float positiveBoost;
  float negativeBoost;
  uint8_t modified;
  uint8_t unlocked;
};
