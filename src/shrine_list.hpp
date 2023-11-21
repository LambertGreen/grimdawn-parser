#pragma once

#include "common.hpp"
#include "uid.hpp"
#include "vector.hpp"

class shrine_list {

public:
  void read(gdc_file *);
  json get_json() const {
    json j;

    for (int i = 0; i < sizeof(uids) / sizeof(uids[0]); i++) {

      json m;
      for (int j = 0; j < uids[i].size(); j++) {
        m.emplace("uid_" + formatNumber(i), uids[i][j].get_json());
      }

      j.emplace(json{"uids", m});
    }

    return j;
  };

private:
  vector<uid> uids[6];
};
