#pragma once

#include "common.hpp"
#include "item.hpp"

class stash_item : public item {
 public:
  void read(gdc_file*);

  json get_json() const {
    json j = item::get_json();
    ADD_TO_JSON(j, x);
    ADD_TO_JSON(j, y);
    return j;
  };

 private:
  float x;
  float y;
};
