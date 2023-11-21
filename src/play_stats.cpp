#include "play_stats.hpp"

#include "block.hpp"
#include "gdc_file.hpp"
#include <string>

json play_stats::get_json() const {
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
    j.emplace("skill_" + std::to_string(i), skillMap[i].get_json());
  }

  return j;
}
