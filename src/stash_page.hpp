
#pragma once

#include <string>
#include "common.hpp"
#include "stash_item.hpp"
#include "vector.hpp"

class stash_page {
 public:
  void read(gdc_file*);

  json get_json() const {
    json j;
    ADD_TO_JSON(j, width);
    ADD_TO_JSON(j, height);

    for (int i = 0; i < items.size(); i++) {
      j.emplace("stash_item_" + std::to_string(i), items[i].get_json());
    }
    return j;
  };

 private:
  vector<stash_item> items;
  uint32_t width;
  uint32_t height;
};
