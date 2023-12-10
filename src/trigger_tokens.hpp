#pragma once

#include "common.hpp"
#include "string.hpp"
#include "vector.hpp"

class trigger_tokens {
 public:
  void read(gdc_file*);
  json get_json() const;

 private:
  vector<string> tokens[3];
};
