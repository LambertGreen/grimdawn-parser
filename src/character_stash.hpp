#pragma once

#include "common.hpp"
#include "stash_page.hpp"
#include "vector.hpp"

class character_stash {
 public:
  void read(gdc_file*);
  json get_json() const;

 private:
  vector<stash_page> pages;
};
