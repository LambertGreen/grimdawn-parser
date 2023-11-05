#pragma once

#include "common.hpp"
#include "item_skill.hpp"
#include "skill.hpp"
#include "vector.hpp"

class character_skills {
public:
  vector<skill> skills;
  vector<item_skill> itemSkills;
  uint32_t masteriesAllowed;
  uint32_t skillReclamationPointsUsed;
  uint32_t devotionReclamationPointsUsed;

  void read(gdc_file *);
  void write(gdc_file *);
};
