#pragma once

#include "item.hpp"

class stash_item : public item {
 public:
  void read(gdc_file*);
  json get_json() const;

 private:
  float x;
  float y;
};
