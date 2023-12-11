#include "character_skill.hpp"

#include "block_field.hpp"
#include "format.hpp"
#include "gdc_file.hpp"
#include "validation.hpp"

namespace {
const int BLOCK = 8;
const int VERSION = 5;
}  // namespace

void character_skills::read(gdc_file* gdc) {
  block_field b;
  ENSURE(gdc->read_block_start(&b) == BLOCK,
         "character_skills: Unexpected block number");
  ENSURE(gdc->read_int() == VERSION,
         "character_skills: Unexpected version number");

  skills.read(gdc);
  masteriesAllowed = gdc->read_int();
  skillReclamationPointsUsed = gdc->read_int();
  devotionReclamationPointsUsed = gdc->read_int();
  itemSkills.read(gdc);
  gdc->read_block_end(&b);
}

json character_skills::get_json() const {
  json j;
  ADD_TO_JSON(j, masteriesAllowed);
  ADD_TO_JSON(j, skillReclamationPointsUsed);
  ADD_TO_JSON(j, devotionReclamationPointsUsed);

  json m;
  for (int i = 0; i < skills.size(); i++) {
    m.emplace("skill_" + formatNumber(i, 3), skills[i].get_json());
  }
  j.emplace("skills", m);

  json m2;
  for (int i = 0; i < itemSkills.size(); i++) {
    m2.emplace("item_skill_" + std::to_string(i), itemSkills[i].get_json());
  }
  j.emplace("item_skills", m2);

  return j;
};
