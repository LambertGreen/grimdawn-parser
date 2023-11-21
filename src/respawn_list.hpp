#pragma once

#include "common.hpp"
#include "uid.hpp"
#include "vector.hpp"

class respawn_list {
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

    for (int i = 0; i < sizeof(spawns) / sizeof(spawns[0]); i++) {
      j.emplace("spawn_" + std::to_string(i), spawns[i].get_json());
    }
    return j;
  };

private:
  vector<uid> uids[3];
  uid spawns[3];
};
