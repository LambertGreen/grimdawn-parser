#pragma once

#include "item.hpp"

class stash_item : public item {
 public:
  virtual void read(gdc_file_reader* gdc);
  virtual void write(gdc_file_writer* gdc);
  virtual json get_json() const;

 private:
  float x;
  float y;
};
