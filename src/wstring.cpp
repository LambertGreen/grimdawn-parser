#include "wstring.hpp"

#include "gdc_file_reader.hpp"
#include "gdc_file_writer.hpp"

void wstring::read(gdc_file_reader* gdc) {
  uint32_t len = gdc->read_int();

  clear();
  reserve(len);

  for (uint32_t i = 0; i < len; i++) {
    wchar_t c = gdc->read_byte();
    c |= gdc->read_byte() << 8;
    push_back(c);
  }
}

void wstring::write(gdc_file_writer* gdc) {
  uint32_t len = size();
  const wchar_t* str = data();

  gdc->write_int(len);

  for (uint32_t i = 0; i < len; i++) {
    gdc->write_byte(str[i]);
    gdc->write_byte(str[i] >> 8);
  }
}
