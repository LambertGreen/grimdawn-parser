#pragma once

#include "gdc_object.hpp"
#include "inventory_item.hpp"
#include "vector.hpp"

class inventory_sack : gdc_object {
 public:
  void read(gdc_file_reader*);
  void write(gdc_file_writer*);
  json get_json() const;

 private:
  vector<inventory_item> items{};
  uint8_t tempBool{};
};
