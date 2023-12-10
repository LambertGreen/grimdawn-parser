#pragma once

#include "common.hpp"
#include "vector.hpp"

class tutorial_pages {
 public:
  void read(gdc_file*);

  json get_json() const {
    json j;

    ADD_TO_JSON(j, pages);
    return j;
  };

 private:
  vector<uint32_t> pages;
};
