#include "header.hpp"

#include "gdc_file.hpp"

void header::read(gdc_file* gdc) {
  version = gdc->read_int();
  if (version != 1 && version != 2) {
    throw std::runtime_error("Unsupported version: " + std::to_string(version));
  }

  name.read(gdc);
  sex = gdc->read_byte();
  classId.read(gdc);
  level = gdc->read_int();
  hardcore = gdc->read_byte();
  expansionStatus = gdc->read_byte();
}
