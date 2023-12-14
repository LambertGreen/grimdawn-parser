
#pragma once

#include "gdc_object.hpp"
#include "stash_item.hpp"
#include "vector.hpp"

class stash_page : gdc_object {
 public:
  void read(gdc_file_reader*);
  void write(gdc_file_writer*);
  json get_json() const;

 private:
  vector<stash_item> items;
  uint32_t width;
  uint32_t height;
};
