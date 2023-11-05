#pragma once

#include "common.hpp"
#include "string.hpp"
#include "vector.hpp"

class character_info {
public:
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

  void read(gdc_file *);
  void write(gdc_file *);
};
