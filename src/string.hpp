#pragma once

#include <string>
#include "gdc_file.hpp"

class string : public std::string {
 public:
  void read(gdc_file*);
  void write(gdc_file*);
};
