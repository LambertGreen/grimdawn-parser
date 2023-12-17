#pragma once

#include "item.hpp"

class inventory_equipment : public item {
 public:
  virtual void read(gdc_file_reader* gdc);
  virtual void write(gdc_file_writer* gdc);
  virtual json to_json() const;

 private:
  uint8_t attached;
};
