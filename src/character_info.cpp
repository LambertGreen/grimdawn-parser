#include "character_info.hpp"

#include "block.hpp"
#include "format.hpp"
#include "validation.hpp"

void character_info::read(gdc_file_reader* gdc) {
  block b;
  b.read_start(gdc);
  ENSURE(b.num == BLOCK_1, "character_info: Unexpected block number");
  ENSURE(b.version == VERSION_5, "character_info: Unexpected version number");

  isInMainQuest = gdc->read_byte();
  hasBeenInGame = gdc->read_byte();
  difficulty = gdc->read_byte();
  greatestDifficulty = gdc->read_byte();
  money = gdc->read_int();
  greatestSurvivalDifficulty = gdc->read_byte();
  currentTribute = gdc->read_int();
  compassState = gdc->read_byte();
  skillWindowShowHelp = gdc->read_byte();
  alternateConfig = gdc->read_byte();
  alternateConfigEnabled = gdc->read_byte();
  texture.read(gdc);

  const auto lootFiltersSize = gdc->read_int();
  lootFilters.resize(lootFiltersSize);
  for (uint32_t i = 0; i < lootFiltersSize; i++) {
    lootFilters[i] = gdc->read_byte();
  }

  b.read_end(gdc);
}

void character_info::write(gdc_file_writer* gdc) const {
  block b;
  b.write_start(gdc, BLOCK_1, VERSION_5);

  gdc->write_byte(isInMainQuest);
  gdc->write_byte(hasBeenInGame);
  gdc->write_byte(difficulty);
  gdc->write_byte(greatestDifficulty);
  gdc->write_int(money);
  gdc->write_byte(greatestSurvivalDifficulty);
  gdc->write_int(currentTribute);
  gdc->write_byte(compassState);
  gdc->write_byte(skillWindowShowHelp);
  gdc->write_byte(alternateConfig);
  gdc->write_byte(alternateConfigEnabled);
  texture.write(gdc);

  const int lootFiltersSize = lootFilters.size();
  gdc->write_int(lootFiltersSize);
  for (uint32_t i = 0; i < lootFiltersSize; i++) {
    gdc->write_byte(lootFilters[i]);
  }

  b.write_end(gdc);
}

json character_info::to_json() const {
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
    m.emplace("lootFilter_" + formatNumber(i), lootFilters[i]);
  }

  j.emplace(json{"lootFilters", m});
  return j;
}
