#pragma once

#include "common.hpp"
#include "gdc_file.hpp"

template <typename T>
class vector : public std::vector<T> {
 public:
  void read(gdc_file* gdc) {
    uint32_t n = gdc->read_int();

    this->resize(n);
    T* ptr = this->data();

    for (uint32_t i = 0; i < n; i++) {
      ptr[i].read(gdc);
    }
  }
};
