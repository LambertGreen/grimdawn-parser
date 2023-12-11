#pragma once

#include "gdc_object.hpp"
#include "vector.hpp"

class tutorial_pages : gdc_object {
 public:
  void read(gdc_file*);
  json get_json() const;

 private:
  vector<uint32_t> pages;
};
