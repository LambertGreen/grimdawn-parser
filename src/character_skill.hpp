#pragma once

#include "common.hpp"
#include "item_skill.hpp"
#include "skill.hpp"
#include "vector.hpp"

class character_skills {
 public:
  void read(gdc_file*);
  json get_json() const {
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

 private:
  vector<skill> skills;
  vector<item_skill> itemSkills;
  uint32_t masteriesAllowed;
  uint32_t skillReclamationPointsUsed;
  uint32_t devotionReclamationPointsUsed;
};
