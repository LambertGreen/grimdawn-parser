
#pragma once

#include "common.hpp"
#include "string.hpp"

class skill_map {
public:
  string skill;
  int active;

  void read(gdc_file *);
};
