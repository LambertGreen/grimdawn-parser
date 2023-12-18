#include "play_stats.hpp"

#include <string>
#include "block.hpp"
#include "validation.hpp"

void play_stats::read(gdc_file_reader* gdc) {
  block b;
  b.read_start(gdc);
  ENSURE(b.num == BLOCK, "play_stats: Unexpected block number");
  ENSURE(b.version == VERSION, "play_stats: Unexpected version number");

  playTime = gdc->read_int();
  deaths = gdc->read_int();
  kills = gdc->read_int();
  experienceFromKills = gdc->read_int();
  healthPotionsUsed = gdc->read_int();
  manaPotionsUsed = gdc->read_int();
  maxLevel = gdc->read_int();
  hitsReceived = gdc->read_int();
  hitsInflicted = gdc->read_int();
  criticalHitsInflicted = gdc->read_int();
  criticalHitsReceived = gdc->read_int();
  greatestDamageInflicted = gdc->read_float();

  for (unsigned i = 0; i < 3; i++) {
    greatestMonsterKilledName[i].read(gdc);
    greatestMonsterKilledLevel[i] = gdc->read_int();
    greatestMonsterKilledLifeAndMana[i] = gdc->read_int();
    lastMonsterHit[i].read(gdc);
    lastMonsterHitBy[i].read(gdc);
  }

  championKills = gdc->read_int();
  lastHit = gdc->read_float();
  lastHitBy = gdc->read_float();
  greatestDamageReceived = gdc->read_float();
  heroKills = gdc->read_int();
  itemsCrafted = gdc->read_int();
  relicsCrafted = gdc->read_int();
  transcendentRelicsCrafted = gdc->read_int();
  mythicalRelicsCrafted = gdc->read_int();
  shrinesRestored = gdc->read_int();
  oneShotChestsOpened = gdc->read_int();
  loreNotesCollected = gdc->read_int();

  for (unsigned i = 0; i < 3; i++) {
    bossKills[i] = gdc->read_int();
  }

  survivalGreatestWave = gdc->read_int();
  survivalGreatestScore = gdc->read_int();
  survivalDefensesBuilt = gdc->read_int();
  survivalPowerUpsActivated = gdc->read_int();

  skillMap.read(gdc);

  endlessSouls = gdc->read_int();
  endlessEssence = gdc->read_int();
  difficultySkip = gdc->read_byte();

  unknown1 = gdc->read_int();
  unknown2 = gdc->read_int();

  b.read_end(gdc);
}

void play_stats::write(gdc_file_writer* gdc) {
  block b;
  b.write_start(gdc, BLOCK, VERSION);

  gdc->write_int(playTime);
  gdc->write_int(deaths);
  gdc->write_int(kills);
  gdc->write_int(experienceFromKills);
  gdc->write_int(healthPotionsUsed);
  gdc->write_int(manaPotionsUsed);
  gdc->write_int(maxLevel);
  gdc->write_int(hitsReceived);
  gdc->write_int(hitsInflicted);
  gdc->write_int(criticalHitsInflicted);
  gdc->write_int(criticalHitsReceived);
  gdc->write_float(greatestDamageInflicted);

  for (unsigned i = 0; i < 3; i++) {
    greatestMonsterKilledName[i].write(gdc);
    gdc->write_int(greatestMonsterKilledLevel[i]);
    gdc->write_int(greatestMonsterKilledLifeAndMana[i]);
    lastMonsterHit[i].write(gdc);
    lastMonsterHitBy[i].write(gdc);
  }

  gdc->write_int(championKills);
  gdc->write_float(lastHit);
  gdc->write_float(lastHitBy);
  gdc->write_float(greatestDamageReceived);
  gdc->write_int(heroKills);
  gdc->write_int(itemsCrafted);
  gdc->write_int(relicsCrafted);
  gdc->write_int(transcendentRelicsCrafted);
  gdc->write_int(mythicalRelicsCrafted);
  gdc->write_int(shrinesRestored);
  gdc->write_int(oneShotChestsOpened);
  gdc->write_int(loreNotesCollected);

  for (unsigned i = 0; i < 3; i++) {
    gdc->write_int(bossKills[i]);
  }

  gdc->write_int(survivalGreatestWave);
  gdc->write_int(survivalGreatestScore);
  gdc->write_int(survivalDefensesBuilt);
  gdc->write_int(survivalPowerUpsActivated);

  skillMap.write(gdc);

  gdc->write_int(endlessSouls);
  gdc->write_int(endlessEssence);
  gdc->write_byte(difficultySkip);

  gdc->write_int(unknown1);
  gdc->write_int(unknown2);

  b.write_end(gdc);
}

json play_stats::to_json() const {
  json j;
  ADD_TO_JSON(j, playTime);
  ADD_TO_JSON(j, deaths);
  ADD_TO_JSON(j, kills);
  ADD_TO_JSON(j, experienceFromKills);
  ADD_TO_JSON(j, healthPotionsUsed);
  ADD_TO_JSON(j, manaPotionsUsed);
  ADD_TO_JSON(j, maxLevel);
  ADD_TO_JSON(j, hitsReceived);
  ADD_TO_JSON(j, hitsInflicted);
  ADD_TO_JSON(j, criticalHitsInflicted);
  ADD_TO_JSON(j, criticalHitsReceived);
  ADD_TO_JSON(j, championKills);
  ADD_TO_JSON(j, heroKills);
  ADD_TO_JSON(j, itemsCrafted);
  ADD_TO_JSON(j, relicsCrafted);
  ADD_TO_JSON(j, transcendentRelicsCrafted);
  ADD_TO_JSON(j, mythicalRelicsCrafted);
  ADD_TO_JSON(j, shrinesRestored);
  ADD_TO_JSON(j, oneShotChestsOpened);
  ADD_TO_JSON(j, loreNotesCollected);
  ADD_TO_JSON(j, greatestDamageInflicted);
  ADD_TO_JSON(j, lastHit);
  ADD_TO_JSON(j, lastHitBy);
  ADD_TO_JSON(j, greatestDamageReceived);
  ADD_TO_JSON(j, survivalGreatestWave);
  ADD_TO_JSON(j, survivalGreatestScore);
  ADD_TO_JSON(j, survivalDefensesBuilt);
  ADD_TO_JSON(j, survivalPowerUpsActivated);
  ADD_TO_JSON(j, endlessSouls);
  ADD_TO_JSON(j, endlessEssence);
  ADD_TO_JSON(j, difficultySkip);
  ADD_TO_JSON(j, unknown1);
  ADD_TO_JSON(j, unknown2);

  for (int i = 0; i < 3; i++) {
    json m;
    ADD_TO_JSON2(m, greatestMonsterKilledName, greatestMonsterKilledName[i]);
    ADD_TO_JSON2(m, lastMonsterHit, lastMonsterHit[i]);
    ADD_TO_JSON2(m, lastMonsterHitBy, lastMonsterHitBy[i]);
    ADD_TO_JSON2(m, greatestMonsterKilledLevel, greatestMonsterKilledLevel[i]);
    ADD_TO_JSON2(m, greatestMonsterKilledLifeAndMana,
                 greatestMonsterKilledLifeAndMana[i]);
    ADD_TO_JSON2(m, bossKills, bossKills[i]);

    auto difficulty = "difficulty_" + std::to_string(i);
    j.emplace(json{difficulty, m});
  }

  for (int i = 0; i < skillMap.size(); i++) {
    j.emplace("skill_" + std::to_string(i), skillMap[i].to_json());
  }

  return j;
}
