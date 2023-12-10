#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdexcept>

#include <_types/_uint8_t.h>
#include <exception>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

static std::exception e;

#define LOG(field)    // std::cout << #field << ": " << field << std::endl;
#define LOG_W(field)  // std::wcout << #field << ": " << field << std::endl;
#define LOG_N( \
    field)  //                                                          \
  std::cout << #field << ": " << std::to_string(field) << std::endl;

#define ENSURE(condition, message) \
  if (!(condition))                \
    throw std::runtime_error((message));

#define ADD_TO_JSON(jsonObj, field) jsonObj[#field] = field
#define ADD_TO_JSON2(jsonObj, field1, field2) jsonObj[#field1] = field2

std::string formatNumber(int num, int count = 2);
class gdc_file;
