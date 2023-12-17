#pragma once

#include "gdc_object.hpp"
#include "vector.hpp"

class tutorial_pages : gdc_object {
 public:
  void read(gdc_file_reader*);
  void write(gdc_file_writer*);
  json to_json() const;

 private:
  vector<uint32_t> pages;
};
