#pragma once

#include "common.hpp"
#include "string.hpp"
#include "vector.hpp"

class lore_notes {
 public:
  void read(gdc_file*);
  json get_json() const;

 private:
  vector<string> names;
};
