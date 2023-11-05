#pragma once

#include "common.hpp"
#include "uid.hpp"
#include "vector.hpp"

class respawn_list {
public:
  vector<uid> uids[3];
  uid spawn[3];

  void read(gdc_file *);
  void write(gdc_file *);
};
