#pragma once

#include "common.hpp"
#include "string.hpp"
#include "vector.hpp"
#include <string>

class character_info {
public:
  void read(gdc_file *);

  json get_json() const {
    json j;
    ADD_TO_JSON(j, texture);
    ADD_TO_JSON(j, money);
    ADD_TO_JSON(j, currentTribute);
    ADD_TO_JSON(j, isInMainQuest);
    ADD_TO_JSON(j, hasBeenInGame);
    ADD_TO_JSON(j, difficulty);
    ADD_TO_JSON(j, greatestDifficulty);
    ADD_TO_JSON(j, compassState);
    ADD_TO_JSON(j, skillWindowShowHelp);
    ADD_TO_JSON(j, alternateConfig);
    ADD_TO_JSON(j, alternateConfigEnabled);

    json m;
    for (int i = 0; i < lootFilters.size(); i++) {
      m.emplace("lootFilter_" + std::to_string(i), lootFilters[i]);
    }

    j.emplace(json{"lootFilters", m});
    return j;
  }

private:
  string texture;
  uint32_t money;
  uint32_t currentTribute;
  uint8_t isInMainQuest;
  uint8_t hasBeenInGame;
  uint8_t difficulty;
  uint8_t greatestDifficulty;
  uint8_t greatestSurvivalDifficulty;
  uint8_t compassState;
  uint8_t skillWindowShowHelp;
  uint8_t alternateConfig;
  uint8_t alternateConfigEnabled;
  vector<uint8_t> lootFilters;
};
