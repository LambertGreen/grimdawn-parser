#pragma once

#include <string>

class gdc_file_reader;
class gdc_file_writer;

class string : public std::string {
 public:
  void read(gdc_file_reader&);
  void write(gdc_file_writer&) const;
};
