#include "wstring.hpp"

#include "gdc_file.hpp"

void wstring::read(gdc_file* gdc) {
  uint32_t len = gdc->read_int();

  clear();
  reserve(len);

  for (uint32_t i = 0; i < len; i++) {
    wchar_t c = gdc->read_byte();
    c |= gdc->read_byte() << 8;
    push_back(c);
  }
}
