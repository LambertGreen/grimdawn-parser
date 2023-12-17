#pragma once

#include "gdc_object.hpp"
#include "string.hpp"
#include "vector.hpp"

class lore_notes : gdc_object {
 public:
  void read(gdc_file_reader*);
  void write(gdc_file_writer*);
  json to_json() const;

 private:
  vector<string> names;
};
