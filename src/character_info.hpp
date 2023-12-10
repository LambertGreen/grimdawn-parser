#pragma once

#include <string>
#include "common.hpp"
#include "string.hpp"
#include "vector.hpp"

class character_info {
 public:
  void read(gdc_file*);
  json get_json() const;

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
