#include "uid.hpp"

#include <string>
#include "gdc_file.hpp"

void uid::read(gdc_file_reader& gdc) {
  for (unsigned i = 0; i < 16; i++) {
    id[i] = gdc.read_byte();
  }
}

void uid::write(gdc_file_writer& gdc) const {
  for (unsigned i = 0; i < 16; i++) {
    gdc.write_byte(id[i]);
  }
}

json uid::to_json() const {
  std::string s = std::to_string(id[0]);
  for (int i = 1; i < sizeof(id) / sizeof(id[0]); i++) {
    s += "-" + std::to_string(i);
  }

  json j;
  j.emplace("uid", s);
  return j;
}
