#pragma once

#include "gdc_object.hpp"
#include "stash_page.hpp"
#include "vector.hpp"

class character_stash : gdc_object {
 public:
  void read(gdc_file_reader*);
  void write(gdc_file_writer*) const;
  json to_json() const;

 private:
  static constexpr int BLOCK = 4;
  static constexpr int VERSION = 6;

  vector<stash_page> pages;
};
