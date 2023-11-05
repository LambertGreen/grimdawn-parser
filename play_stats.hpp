#pragma once

#include "common.hpp"
#include "string.hpp"

class play_stats {
public:
  string greatestMonsterKilledName[3];
  string lastMonsterHit[3];
  string lastMonsterHitBy[3];
  uint32_t greatestMonsterKilledLevel[3];
  uint32_t greatestMonsterKilledLifeAndMana[3];
  uint32_t bossKills[3];
  uint32_t playTime;
  uint32_t deaths;
  uint32_t kills;
  uint32_t experienceFromKills;
  uint32_t healthPotionsUsed;
  uint32_t manaPotionsUsed;
  uint32_t maxLevel;
  uint32_t hitsReceived;
  uint32_t hitsInflicted;
  uint32_t criticalHitsInflicted;
  uint32_t criticalHitsReceived;
  uint32_t championKills;
  uint32_t heroKills;
  uint32_t itemsCrafted;
  uint32_t relicsCrafted;
  uint32_t transcendentRelicsCrafted;
  uint32_t mythicalRelicsCrafted;
  uint32_t shrinesRestored;
  uint32_t oneShotChestsOpened;
  uint32_t loreNotesCollected;
  float greatestDamageInflicted;
  float lastHit;
  float lastHitBy;
  float greatestDamageReceived;
  uint32_t survivalWaveTier;
  uint32_t greatestSurvivalScore;
  uint32_t cooldownRemaining;
  uint32_t cooldownTotal;
  uint32_t unknown1;
  uint32_t unknown2;

  void read(gdc_file *);
  void write(gdc_file *);
};
