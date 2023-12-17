#pragma once

#include "gdc_object.hpp"
#include "string.hpp"

#include <_types/_uint8_t.h>
#include <stdint.h>

class skill : gdc_object {
 public:
  void read(gdc_file_reader*);
  void write(gdc_file_writer*);
  json to_json() const;

 private:
  string name;
  string autoCastSkill;
  string autoCastController;
  uint32_t level;
  uint32_t devotionLevel;
  uint32_t experience;
  uint32_t active;
  uint8_t enabled;
  uint8_t unknown1;
  uint8_t unknown2;
};
