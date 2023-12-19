#include "string.hpp"

#include "gdc_file_reader.hpp"
#include "gdc_file_writer.hpp"

void string::read(gdc_file_reader* gdc) {
  uint32_t len = gdc->read_int();
  if (len > 256) {
    throw std::runtime_error("Length of string is suspiciously long: " +
                             std::to_string(len));
  }

  clear();
  reserve(len);

  for (uint32_t i = 0; i < len; i++) {
    push_back(gdc->read_byte());
  }
}

void string::write(gdc_file_writer* gdc) const {
  uint32_t len = size();
  const char* str = data();

  gdc->write_int(len);

  for (uint32_t i = 0; i < len; i++) {
    gdc->write_byte(str[i]);
  }
}
