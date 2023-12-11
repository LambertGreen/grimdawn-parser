#pragma once

#include <_types/_uint8_t.h>
#include "gdc_object.hpp"
#include "skill_map.hpp"
#include "string.hpp"
#include "vector.hpp"

class play_stats : gdc_object {
 public:
  void read(gdc_file* gdc);
  json get_json() const;

 private:
  string greatestMonsterKilledName[3]{};
  string lastMonsterHit[3]{};
  string lastMonsterHitBy[3]{};
  uint32_t greatestMonsterKilledLevel[3]{};
  uint32_t greatestMonsterKilledLifeAndMana[3]{};
  uint32_t bossKills[3]{};
  uint32_t playTime{};
  uint32_t deaths{};
  uint32_t kills{};
  uint32_t experienceFromKills{};
  uint32_t healthPotionsUsed{};
  uint32_t manaPotionsUsed{};
  uint32_t maxLevel{};
  uint32_t hitsReceived{};
  uint32_t hitsInflicted{};
  uint32_t criticalHitsInflicted{};
  uint32_t criticalHitsReceived{};
  uint32_t championKills{};
  uint32_t heroKills{};
  uint32_t itemsCrafted{};
  uint32_t relicsCrafted{};
  uint32_t transcendentRelicsCrafted{};
  uint32_t mythicalRelicsCrafted{};
  uint32_t shrinesRestored{};
  uint32_t oneShotChestsOpened{};
  uint32_t loreNotesCollected{};
  float greatestDamageInflicted{};
  float lastHit{};
  float lastHitBy{};
  float greatestDamageReceived{};
  uint32_t survivalGreatestWave{};
  uint32_t survivalGreatestScore{};
  uint32_t survivalDefensesBuilt{};
  uint32_t survivalPowerUpsActivated{};
  vector<skill_map> skillMap{};
  uint32_t endlessSouls{};
  uint32_t endlessEssence{};
  uint8_t difficultySkip{};

  uint32_t unknown1{};
  uint32_t unknown2{};
};
