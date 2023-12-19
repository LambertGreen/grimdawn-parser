#pragma once

#include "gdc_object.hpp"
#include "string.hpp"

class skill_map : gdc_object {
 public:
  void read(gdc_file_reader*);
  void write(gdc_file_writer*) const;
  json to_json() const;

 private:
  string skill;
  int active;
};
