#pragma once

#include "common.hpp"
#include "string.hpp"
#include "vector.hpp"

class trigger_tokens {
public:
  void read(gdc_file *);
  json get_json() const {
    json j;
    for (int i = 0; i < sizeof(tokens) / sizeof(tokens[0]); i++) {
      j.emplace("token_" + std::to_string(i), tokens[i]);
    }
    return j;
  };

private:
  vector<string> tokens[3];
};
