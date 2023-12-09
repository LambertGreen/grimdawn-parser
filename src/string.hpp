#pragma once

#include "gdc_file.hpp"
#include <string>

class string : public std::string {
public:
  void read(gdc_file *);
  void write(gdc_file *);
};
