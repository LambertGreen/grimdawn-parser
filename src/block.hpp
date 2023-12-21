#pragma once

#include "block_field.hpp"

class gdc_file_reader;
class gdc_file_writer;

class block {
 public:
  int num{};
  int version{};
  block_field b;

  void read_start(gdc_file_reader&);
  void write_start(gdc_file_writer&, int num, int version);
  void read_end(gdc_file_reader&);
  void write_end(gdc_file_writer&);
};
