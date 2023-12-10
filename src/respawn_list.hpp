#pragma once

#include "common.hpp"
#include "uid.hpp"
#include "vector.hpp"

class respawn_list {
 public:
  void read(gdc_file*);
  json get_json() const;

 private:
  vector<uid> uids[3];
  uid spawns[3];
};
