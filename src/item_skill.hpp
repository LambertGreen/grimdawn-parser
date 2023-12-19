#pragma once

#include "gdc_object.hpp"
#include "string.hpp"

class item_skill : gdc_object {
 public:
  void read(gdc_file_reader*);
  void write(gdc_file_writer*) const;
  json to_json() const;

 private:
  string name;
  string autoCastSkill;
  string autoCastController;
  string itemName;
  uint32_t itemSlot;
};
