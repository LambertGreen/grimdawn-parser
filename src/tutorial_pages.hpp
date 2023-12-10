#pragma once

#include "common.hpp"
#include "vector.hpp"

class tutorial_pages {
 public:
  void read(gdc_file*);
  json get_json() const;

 private:
  vector<uint32_t> pages;
};
