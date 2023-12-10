#pragma once

#include "common.hpp"

class file {
 public:
  FILE* fp;

  file(const char* name, const char* mode) { fp = fopen(name, mode); }

  ~file() {
    if (fp)
      fclose(fp);
  }

 private:
  file(const file&);             // = delete;
  file& operator=(const file&);  // = delete;
};
