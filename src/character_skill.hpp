#pragma once

#include "gdc_object.hpp"
#include "item_skill.hpp"
#include "skill.hpp"
#include "vector.hpp"

class character_skills : gdc_object {
 public:
  void read(gdc_file*);
  json get_json() const;

 private:
  vector<skill> skills;
  vector<item_skill> itemSkills;
  uint32_t masteriesAllowed;
  uint32_t skillReclamationPointsUsed;
  uint32_t devotionReclamationPointsUsed;
};
