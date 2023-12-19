#pragma once

#include <_types/_uint32_t.h>
#include <_types/_uint8_t.h>
#include "gdc_object.hpp"
#include "string.hpp"
#include "wstring.hpp"

class header : gdc_object {
 public:
  void read(gdc_file_reader*);
  void write(gdc_file_writer*) const;
  json to_json() const;

 private:
  static constexpr int VERSION1 = 1;
  static constexpr int VERSION2 = 2;

  uint32_t version{};
  wstring name;
  string classId;
  uint32_t level{};
  uint8_t sex{};
  uint8_t hardcore{};
  uint8_t expansionStatus{};
  uint8_t isInMainQuest{};
  string className;
};
