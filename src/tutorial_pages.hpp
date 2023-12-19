#pragma once

#include "gdc_object.hpp"
#include "vector.hpp"

class tutorial_pages : gdc_object {
 public:
  void read(gdc_file_reader*);
  void write(gdc_file_writer*) const;
  json to_json() const;

 private:
  static constexpr int BLOCK = 15;
  static constexpr int VERSION = 1;

  vector<uint32_t> pages;
};
