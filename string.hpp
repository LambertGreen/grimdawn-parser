
#pragma once

#include <string>

class gdc_file;

class string : public std::string {
public:
  void read(gdc_file *);
  void write(gdc_file *);
};
