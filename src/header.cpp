#include "header.hpp"

#include "gdc_file_reader.hpp"
#include "gdc_file_writer.hpp"

void header::read(gdc_file_reader& gdc) {
  version = gdc.read_int();
  if (version != VERSION_1 && version != VERSION_2) {
    throw std::runtime_error("Unsupported version: " + std::to_string(version));
  }

  name.read(gdc);
  sex = gdc.read_byte();
  classId.read(gdc);
  level = gdc.read_int();
  hardcore = gdc.read_byte();
  expansionStatus = gdc.read_byte();
}

void header::write(gdc_file_writer& gdc) const {
  gdc.write_int(VERSION_2);
  name.write(gdc);
  gdc.write_byte(sex);
  classId.write(gdc);
  gdc.write_int(level);
  gdc.write_byte(hardcore);
  gdc.write_byte(expansionStatus);
}

json header::to_json() const {
  json j;
  ADD_TO_JSON(j, name);
  ADD_TO_JSON(j, sex);
  ADD_TO_JSON(j, classId);
  ADD_TO_JSON(j, level);
  ADD_TO_JSON(j, hardcore);
  ADD_TO_JSON(j, expansionStatus);
  return j;
}
