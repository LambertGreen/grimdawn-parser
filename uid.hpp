#pragma once

#include "common.hpp"

class uid {
public:
  uint8_t id[16];

  void read(gdc_file *);
};
