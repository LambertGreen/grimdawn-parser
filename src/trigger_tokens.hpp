#pragma once

#include "gdc_object.hpp"
#include "string.hpp"
#include "vector.hpp"

class trigger_tokens : gdc_object {
 public:
  void read(gdc_file_reader*);
  void write(gdc_file_writer*);
  json to_json() const;

 private:
  vector<string> tokens[3];
};
