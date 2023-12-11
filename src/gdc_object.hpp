#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;
class gdc_file;

#define ADD_TO_JSON(jsonObj, field) jsonObj[#field] = field
#define ADD_TO_JSON2(jsonObj, field1, field2) jsonObj[#field1] = field2

class gdc_object {
 protected:
  virtual ~gdc_object() = default;

  virtual json get_json() const = 0;
  virtual void read(gdc_file*) = 0;
};
