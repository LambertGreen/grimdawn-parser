#include "character_bio.hpp"

#include "block.hpp"
#include "gdc_file.hpp"
#include "validation.hpp"

namespace {
const int BLOCK = 2;
const int VERSION = 8;
}  // namespace

void character_bio::read(gdc_file* gdc) {
  block b;
  b.read_start(gdc);
  ENSURE(b.num == BLOCK, "character_info: Unexpected block number");
  ENSURE(b.version == VERSION, "character_info: Unexpected version number");

  level = gdc->read_int();
  experience = gdc->read_int();
  modifierPoints = gdc->read_int();
  skillPoints = gdc->read_int();
  devotionPoints = gdc->read_int();
  totalDevotion = gdc->read_int();
  physique = gdc->read_float();
  cunning = gdc->read_float();
  spirit = gdc->read_float();
  health = gdc->read_float();
  energy = gdc->read_float();

  b.read_end(gdc);
}

json character_bio::get_json() const {
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
