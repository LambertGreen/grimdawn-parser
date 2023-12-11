#include "character_info.hpp"

#include "block.hpp"
#include "format.hpp"
#include "gdc_file.hpp"
#include "validation.hpp"

namespace {
const int BLOCK = 1;
const int VERSION = 5;
}  // namespace

void character_info::read(gdc_file* gdc) {
  block b;
  b.read_start(gdc);
  ENSURE(b.num == BLOCK, "character_info: Unexpected block number");
  ENSURE(b.version == VERSION, "character_info: Unexpected version number");

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

json character_info::get_json() const {
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
