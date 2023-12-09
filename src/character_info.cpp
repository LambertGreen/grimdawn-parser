#include "character_info.hpp"

#include "block.hpp"
#include "gdc_file.hpp"

void character_info::read(gdc_file *gdc) {
  const int BLOCK = 1;
  const int VERSION = 5;

  block b;
  b.read_start(gdc);
  ENSURE(b.num == BLOCK, "Unexpected block number");
  ENSURE(b.version == VERSION, "Unexpected version number");

  isInMainQuest = gdc->read_byte();
  LOG_N(isInMainQuest);

  hasBeenInGame = gdc->read_byte();
  LOG_N(hasBeenInGame);

  difficulty = gdc->read_byte();
  LOG_N(difficulty);

  greatestDifficulty = gdc->read_byte();
  LOG_N(greatestDifficulty);

  money = gdc->read_int();
  LOG_N(money);

  greatestSurvivalDifficulty = gdc->read_byte();
  LOG_N(greatestSurvivalDifficulty);

  currentTribute = gdc->read_int();
  LOG_N(currentTribute);

  compassState = gdc->read_byte();
  LOG_N(compassState);

  skillWindowShowHelp = gdc->read_byte();
  LOG_N(skillWindowShowHelp);

  alternateConfig = gdc->read_byte();
  LOG_N(alternateConfig);

  alternateConfigEnabled = gdc->read_byte();
  LOG_N(alternateConfigEnabled);

  texture.read(gdc);
  LOG(texture);

  const auto lootFiltersSize = gdc->read_int();
  lootFilters.resize(lootFiltersSize);
  LOG_N(lootFiltersSize);

  for (uint32_t i = 0; i < lootFiltersSize; i++) {
    lootFilters[i] = gdc->read_byte();
  }

  b.read_end(gdc);
}
