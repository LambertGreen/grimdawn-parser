#include "tutorial_pages.hpp"

#include "block.hpp"
#include "validation.hpp"

namespace {
const int BLOCK = 15;
const int VERSION = 1;
}  // namespace

void tutorial_pages::read(gdc_file_reader* gdc) {
  block b;
  b.read_start(gdc);
  ENSURE(b.num == BLOCK, "tutorial_pages: Unexpected block number");
  ENSURE(b.version == VERSION, "tutorial_pages: Unexpected version number");

  uint32_t n = gdc->read_int();
  pages.resize(n);

  for (uint32_t i = 0; i < n; i++) {
    pages[i] = gdc->read_int();
  }

  b.read_end(gdc);
}

void tutorial_pages::write(gdc_file_writer* gdc) {
  block b;
  b.write_start(gdc, BLOCK, VERSION);

  uint32_t n = pages.size();
  gdc->write_int(n);

  for (uint32_t i = 0; i < n; i++) {
    gdc->write_int(pages[i]);
  }

  b.write_end(gdc);
}

json tutorial_pages::to_json() const {
  json j;

  ADD_TO_JSON(j, pages);
  return j;
};
