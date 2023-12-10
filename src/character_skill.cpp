#include "character_skill.hpp"

#include "block_field.hpp"
#include "gdc_file.hpp"

void character_skills::read(gdc_file* gdc) {
  const int BLOCK = 8;
  const int VERSION = 5;

  block_field b;
  ENSURE(gdc->read_block_start(&b) == BLOCK, "Unexpected block number");
  ENSURE(gdc->read_int() == VERSION, "Unexpected version number");

  skills.read(gdc);

  masteriesAllowed = gdc->read_int();
  LOG_N(masteriesAllowed);

  skillReclamationPointsUsed = gdc->read_int();
  LOG_N(skillReclamationPointsUsed);

  devotionReclamationPointsUsed = gdc->read_int();
  LOG_N(devotionReclamationPointsUsed);

  itemSkills.read(gdc);

  gdc->read_block_end(&b);
}
