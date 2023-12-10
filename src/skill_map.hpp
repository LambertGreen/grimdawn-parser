
#pragma once

#include "common.hpp"
#include "string.hpp"

class skill_map {
 public:
  string skill;
  int active;

  void read(gdc_file*);
  json get_json() const {
    auto j = json{{"skill", skill}, {"acitive", active}};
    return j;
  }
};
