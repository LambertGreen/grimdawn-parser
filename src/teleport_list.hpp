#pragma once

#include "gdc_object.hpp"
#include "uid.hpp"
#include "vector.hpp"

class teleport_list : gdc_object {
 public:
  void read(gdc_file_reader&);
  void write(gdc_file_writer&) const;
  json to_json() const;

 private:
  static constexpr int BLOCK_6 = 6;
  static constexpr int VERSION_1 = 1;

  vector<uid> uids[3];
};
