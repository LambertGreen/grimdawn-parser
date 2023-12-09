#include "header.hpp"

#include "gdc_file.hpp"


void header::read(gdc_file *gdc) {
  version = gdc->read_int();
  if (version != 1 && version != 2) {
    throw std::runtime_error("Unsupported version: " + std::to_string(version));
  }

  name.read(gdc);
  LOG_W(name);

  sex = gdc->read_byte();
  LOG_N(sex);

  classId.read(gdc);
  LOG(classId);

  level = gdc->read_int();
  LOG_N(level);

  hardcore = gdc->read_byte();
  LOG_N(hardcore);

  expansionStatus = gdc->read_byte();
  LOG_N(expansionStatus);
}
