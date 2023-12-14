#pragma once

#include <vector>
#include "gdc_file.hpp"

template <typename T>
class vector : public std::vector<T> {
 public:
  void read(gdc_file_reader* gdc) {
    uint32_t n = gdc->read_int();

    this->resize(n);
    T* ptr = this->data();

    for (uint32_t i = 0; i < n; i++) {
      ptr[i].read(gdc);
    }
  }

  void write(gdc_file_writer* gdc) {
    uint32_t n = this->size();
    gdc->write_int(n);

    T* ptr = this->data();
    for (uint32_t i = 0; i < n; i++) {
      ptr[i].write(gdc);
    }
  }
};
