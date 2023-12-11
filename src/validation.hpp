#pragma once

#define ENSURE(condition, message) \
  if (!(condition))                \
    throw std::runtime_error((message));
