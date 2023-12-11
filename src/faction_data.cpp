#include "faction_data.hpp"

#include "gdc_file.hpp"

void faction_data::read(gdc_file* gdc) {
  modified = gdc->read_byte();
  unlocked = gdc->read_byte();
  value = gdc->read_float();
  positiveBoost = gdc->read_float();
  negativeBoost = gdc->read_float();
}

json faction_data::get_json() const {
  json j;
  ADD_TO_JSON(j, value);
  ADD_TO_JSON(j, positiveBoost);
  ADD_TO_JSON(j, negativeBoost);
  ADD_TO_JSON(j, modified);
  ADD_TO_JSON(j, unlocked);
  return j;
};
