#pragma once

#include "gdc_object.hpp"
#include "string.hpp"
#include "vector.hpp"

class trigger_tokens : gdc_object {
 public:
  void read(gdc_file*);
  json get_json() const;

 private:
  vector<string> tokens[3];
};
