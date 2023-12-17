#pragma once

#include "gdc_object.hpp"
#include "uid.hpp"
#include "vector.hpp"

class respawn_list : gdc_object {
 public:
  void read(gdc_file_reader*);
  void write(gdc_file_writer*);
  json to_json() const;

 private:
  vector<uid> uids[3];
  uid spawns[3];
};
