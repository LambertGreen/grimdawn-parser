#pragma once

#include <string>

class gdc_file;

class wstring : public std::wstring {
 public:
  void read(gdc_file*);
  void write(gdc_file*);
};
