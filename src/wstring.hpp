#pragma once

#include <string>

class gdc_file_reader;
class gdc_file_writer;

class wstring : public std::wstring {
 public:
  void read(gdc_file_reader*);
  void write(gdc_file_writer*);
};
