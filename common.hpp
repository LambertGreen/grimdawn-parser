#pragma once

#include <stdexcept>
#include <stdint.h>
#include <stdio.h>

#include <_types/_uint8_t.h>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

static std::exception e;

#define LOG(field)   // std::cout << #field << ": " << field << std::endl;
#define LOG_W(field) // std::wcout << #field << ": " << field << std::endl;
#define LOG_N(                                                                 \
    field) //                                                          \
  std::cout << #field << ": " << std::to_string(field) << std::endl;

#define ENSURE(condition, message)                                             \
  if (!(condition))                                                            \
    throw std::runtime_error((message));

class gdc_file;
