#pragma once

#include "gdc_object.hpp"
#include "string.hpp"

class skill_map : gdc_object {
 public:
  void read(gdc_file*);
  json get_json() const;

 private:
  string skill;
  int active;
};
