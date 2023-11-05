#pragma once

#include "string.hpp"
#include "wstring.hpp"
#include <_types/_uint32_t.h>
#include <_types/_uint8_t.h>

class gdc_file;

class header {
public:
  uint32_t version{};
  wstring name;
  string classId;
  uint32_t level{};
  uint8_t sex{};
  uint8_t hardcore{};
  uint8_t expansionStatus{};
  uint8_t isInMainQuest{};
  string className;

  void read(gdc_file *);
  void write(gdc_file *);
};
