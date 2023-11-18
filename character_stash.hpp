#pragma once

#include "common.hpp"
#include "stash_page.hpp"
#include "vector.hpp"
#include <string>

class character_stash {
public:
  void read(gdc_file *);

  json get_json() const {
    json j;
    for (int i = 0; i < pages.size(); i++) {
      j.emplace("page_" + std::to_string(i), pages[i].get_json());
    }
    return j;
  };

private:
  vector<stash_page> pages;
};
