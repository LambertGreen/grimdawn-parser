#include "faction_data.hpp"

#include "gdc_file.hpp"

void faction_data::read(gdc_file_reader* gdc) {
  modified = gdc->read_byte();
  unlocked = gdc->read_byte();
  value = gdc->read_float();
  positiveBoost = gdc->read_float();
  negativeBoost = gdc->read_float();
}

void faction_data::write(gdc_file_writer* gdc) {
  gdc->write_byte(modified);
  gdc->write_byte(unlocked);
  gdc->write_float(value);
  gdc->write_float(positiveBoost);
  gdc->write_float(negativeBoost);
}

json faction_data::to_json() const {
  json j;
  ADD_TO_JSON(j, modified);
  ADD_TO_JSON(j, unlocked);
  ADD_TO_JSON(j, value);
  ADD_TO_JSON(j, positiveBoost);
  ADD_TO_JSON(j, negativeBoost);
  return j;
};
