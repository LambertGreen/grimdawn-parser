#pragma once

#include <exception>
#include <string>

static std::exception e;

#define LOG(field)    // std::cout << #field << ": " << field << std::endl;
#define LOG_W(field)  // std::wcout << #field << ": " << field << std::endl;
#define LOG_N( \
    field)  //                                                          \
  std::cout << #field << ": " << std::to_string(field) << std::endl;

#define ENSURE(condition, message) \
  if (!(condition))                \
    throw std::runtime_error((message));

std::string formatNumber(int num, int count = 2);
