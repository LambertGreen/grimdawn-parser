#pragma once

#include "common.hpp"
#include "stash_page.hpp"
#include "vector.hpp"

class character_stash {
public:
  vector<stash_page> pages;

  void read(gdc_file *);
  void write(gdc_file *);
};
