
#pragma once

#include <string>
#include "common.hpp"
#include "inventory_item.hpp"
#include "vector.hpp"

class inventory_sack {
 public:
  void read(gdc_file*);
  json get_json() const;

 private:
  vector<inventory_item> items{};
  uint8_t tempBool{};
};
