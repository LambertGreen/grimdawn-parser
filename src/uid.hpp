#pragma once

#include "gdc_object.hpp"

class uid : gdc_object {
 public:
  void read(gdc_file_reader*);
  void write(gdc_file_writer*);
  json to_json() const;

 private:
  uint8_t id[16];
};
