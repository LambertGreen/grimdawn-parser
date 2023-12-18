#include "trigger_tokens.hpp"

#include "block.hpp"
#include "validation.hpp"

void trigger_tokens::read(gdc_file_reader* gdc) {
  block b;
  b.read_start(gdc);
  ENSURE(b.num == BLOCK, "trigger_tokens: Unexpected block number");
  ENSURE(b.version == VERSION, "trigger_tokens: Unexpected version number");

  for (unsigned i = 0; i < 3; i++) {
    tokens[i].read(gdc);
  }

  b.read_end(gdc);
}

void trigger_tokens::write(gdc_file_writer* gdc) {
  block b;
  b.write_start(gdc, BLOCK, VERSION);

  for (unsigned i = 0; i < 3; i++) {
    tokens[i].write(gdc);
  }

  b.write_end(gdc);
}

json trigger_tokens::to_json() const {
  json j;
  for (int i = 0; i < sizeof(tokens) / sizeof(tokens[0]); i++) {
    j.emplace("token_" + std::to_string(i), tokens[i]);
  }
  return j;
};
