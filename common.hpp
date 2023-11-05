#pragma once

#include <stdexcept>
#include <stdint.h>
#include <stdio.h>

#include <_types/_uint8_t.h>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

static std::exception e;
#define LOG(field) std::cout << #field << ": " << field << std::endl;
#define LOG_N(field)                                                           \
  std::cout << #field << ": " << std::to_string(field) << std::endl;

class gdc_file;
