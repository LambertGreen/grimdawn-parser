#include "trigger_tokens.hpp"

json trigger_tokens::get_json() const {
  json j;
  for (int i = 0; i < sizeof(tokens) / sizeof(tokens[0]); i++) {
    j.emplace("token_" + std::to_string(i), tokens[i]);
  }
  return j;
};
