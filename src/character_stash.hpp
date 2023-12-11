#pragma once

#include "gdc_object.hpp"
#include "stash_page.hpp"
#include "vector.hpp"

class character_stash : gdc_object {
 public:
  void read(gdc_file*);
  json get_json() const;

 private:
  vector<stash_page> pages;
};
