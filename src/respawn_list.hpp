#pragma once

#include "gdc_object.hpp"
#include "uid.hpp"
#include "vector.hpp"

class respawn_list : gdc_object {
 public:
  void read(gdc_file*);
  json get_json() const;

 private:
  vector<uid> uids[3];
  uid spawns[3];
};
