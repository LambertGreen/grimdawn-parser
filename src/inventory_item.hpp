
#pragma once

#include "item.hpp"

class inventory_item : public item {
 public:
  uint32_t x;
  uint32_t y;

  void read(gdc_file_reader&);
  void write(gdc_file_writer&) const;
  json to_json() const;
};
