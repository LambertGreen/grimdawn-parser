#include "trigger_tokens.hpp"

#include "block_field.hpp"
#include "validation.hpp"

namespace {
const int BLOCK = 10;
const int VERSION = 2;
}  // namespace

void trigger_tokens::read(gdc_file* gdc) {
  block_field b;
  ENSURE(gdc->read_block_start(&b) == BLOCK,
         "trigger_tokens: Unexpected block number");
  ENSURE(gdc->read_int() == VERSION,
         "trigger_tokens: Unexpected version number");

  for (unsigned i = 0; i < 3; i++) {
    tokens[i].read(gdc);
  }

  gdc->read_block_end(&b);
}

json trigger_tokens::get_json() const {
  json j;
  for (int i = 0; i < sizeof(tokens) / sizeof(tokens[0]); i++) {
    j.emplace("token_" + std::to_string(i), tokens[i]);
  }
  return j;
};
