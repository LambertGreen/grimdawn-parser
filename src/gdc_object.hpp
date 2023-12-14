#pragma once

#include <nlohmann/json.hpp>

#include "gdc_file.hpp"

using json = nlohmann::json;
class gdc_file_reader;
class gdc_file_writer;

#define ADD_TO_JSON(jsonObj, field) jsonObj[#field] = field
#define ADD_TO_JSON2(jsonObj, field1, field2) jsonObj[#field1] = field2

class gdc_object {
 protected:
  virtual ~gdc_object() = default;

  virtual void read(gdc_file_reader*) = 0;
  virtual void write(gdc_file_writer*) = 0;
  virtual json get_json() const = 0;
};
