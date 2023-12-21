#pragma once

#include "gdc_object.hpp"
#include "uid.hpp"
#include "vector.hpp"

class shrine_list : gdc_object {
 public:
  void read(gdc_file_reader*);
  void write(gdc_file_writer*) const;
  json to_json() const;

 private:
  static constexpr int BLOCK_17 = 17;
  static constexpr int VERSION_2 = 2;

  vector<uid> uids[6];
};
