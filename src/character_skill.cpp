#include "character_skill.hpp"

#include "block.hpp"
#include "format.hpp"
#include "validation.hpp"

void character_skills::read(gdc_file_reader& gdc) {
  block b;
  b.read_start(gdc);
  ENSURE(b.num == BLOCK_8, "character_skills: Unexpected block number");
  ENSURE(b.version == VERSION_5, "character_skills: Unexpected version number");

  skills.read(gdc);
  masteriesAllowed = gdc.read_int();
  skillReclamationPointsUsed = gdc.read_int();
  devotionReclamationPointsUsed = gdc.read_int();
  itemSkills.read(gdc);

  b.read_end(gdc);
}

void character_skills::write(gdc_file_writer& gdc) const {
  block b;
  b.write_start(gdc, BLOCK_8, VERSION_5);

  skills.write(gdc);
  gdc.write_int(masteriesAllowed);
  gdc.write_int(skillReclamationPointsUsed);
  gdc.write_int(devotionReclamationPointsUsed);
  itemSkills.write(gdc);

  b.write_end(gdc);
}

json character_skills::to_json() const {
  json j;
  ADD_TO_JSON(j, masteriesAllowed);
  ADD_TO_JSON(j, skillReclamationPointsUsed);
  ADD_TO_JSON(j, devotionReclamationPointsUsed);

  json m;
  for (int i = 0; i < skills.size(); i++) {
    m.emplace("skill_" + formatNumber(i, 3), skills[i].to_json());
  }
  j.emplace("skills", m);

  json m2;
  for (int i = 0; i < itemSkills.size(); i++) {
    m2.emplace("item_skill_" + std::to_string(i), itemSkills[i].to_json());
  }
  j.emplace("item_skills", m2);

  return j;
};
