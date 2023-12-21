#include "character_bio.hpp"

#include "block.hpp"
#include "validation.hpp"

void character_bio::read(gdc_file_reader& gdc) {
  block b;
  b.read_start(gdc);
  ENSURE(b.num == BLOCK_2, "character_info: Unexpected block number");
  ENSURE(b.version == VERSION_8, "character_info: Unexpected version number");

  level = gdc.read_int();
  experience = gdc.read_int();
  modifierPoints = gdc.read_int();
  skillPoints = gdc.read_int();
  devotionPoints = gdc.read_int();
  totalDevotion = gdc.read_int();
  physique = gdc.read_float();
  cunning = gdc.read_float();
  spirit = gdc.read_float();
  health = gdc.read_float();
  energy = gdc.read_float();

  b.read_end(gdc);
}

void character_bio::write(gdc_file_writer& gdc) const {
  block b;
  b.write_start(gdc, BLOCK_2, VERSION_8);

  gdc.write_int(level);
  gdc.write_int(experience);
  gdc.write_int(modifierPoints);
  gdc.write_int(skillPoints);
  gdc.write_int(devotionPoints);
  gdc.write_int(totalDevotion);
  gdc.write_float(physique);
  gdc.write_float(cunning);
  gdc.write_float(spirit);
  gdc.write_float(health);
  gdc.write_float(energy);

  b.write_end(gdc);
}

json character_bio::to_json() const {
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
