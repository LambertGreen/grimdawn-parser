#pragma once

#include "common.hpp"

template <typename T> class vector : public std::vector<T> {
public:
  void read(gdc_file *);
  void write(gdc_file *);
};
