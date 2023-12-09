#include "character_bio.hpp"

#include "block.hpp"
#include "gdc_file.hpp"

void character_bio::read(gdc_file *gdc) {
  const int BLOCK = 2;
  const int VERSION = 8;

  block b;
  b.read_start(gdc);
  ENSURE(b.num == BLOCK, "Unexpected block number");
  ENSURE(b.version == VERSION, "Unexpected version number");

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
