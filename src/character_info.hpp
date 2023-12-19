#pragma once

#include "gdc_object.hpp"
#include "string.hpp"
#include "vector.hpp"

class character_info : gdc_object {
 public:
  void read(gdc_file_reader*);
  void write(gdc_file_writer*) const;
  json to_json() const;

 private:
  static constexpr int BLOCK = 1;
  static constexpr int VERSION = 5;

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
