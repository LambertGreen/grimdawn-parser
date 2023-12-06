#pragma once

#include "common.hpp"
#include <string>

class uid {
public:
  json get_json() const;
  void read(gdc_file *);

private:
  uint8_t id[16];
};
