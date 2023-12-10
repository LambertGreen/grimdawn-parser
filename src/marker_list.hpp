#pragma once

#include "common.hpp"
#include "uid.hpp"
#include "vector.hpp"

class marker_list {
 public:
  void read(gdc_file*);
  json get_json() const;

 private:
  vector<uid> uids[3];
};
