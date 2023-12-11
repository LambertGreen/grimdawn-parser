#pragma once

#include "gdc_object.hpp"

class uid : gdc_object {
 public:
  json get_json() const;
  void read(gdc_file*);

 private:
  uint8_t id[16];
};
