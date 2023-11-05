#pragma once

#include "common.hpp"
#include "uid.hpp"
#include "vector.hpp"

class shrine_list {
public:
  vector<uid> uids[6];

  void read(gdc_file *);
  void write(gdc_file *);
};
