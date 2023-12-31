#pragma once

#include "gdc_object.hpp"
#include "string.hpp"
#include "vector.hpp"

class trigger_tokens : gdc_object {
 public:
  void read(gdc_file_reader&);
  void write(gdc_file_writer&) const;
  json to_json() const;

 private:
  static constexpr int BLOCK_10 = 10;
  static constexpr int VERSION_2 = 2;

  vector<string> tokens[3];
};
