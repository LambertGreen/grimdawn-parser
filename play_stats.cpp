#include "play_stats.hpp"

#include "block.hpp"
#include "gdc_file.hpp"

json play_stats::get_json() const {
  auto j = json{{"playTime", playTime},
                {"deaths", deaths},
                {"kills", kills},
                {"experienceFromKills", experienceFromKills},
                {"healthPotionsUsed", healthPotionsUsed},
                {"manaPotionsUsed", manaPotionsUsed},
                {"maxLevel", maxLevel},
                {"hitsReceived", hitsReceived},
                {"hitsInflicted", hitsInflicted},
                {"criticalHitsInflicted", criticalHitsInflicted},
                {"criticalHitsReceived", criticalHitsReceived},
                {"championKills", championKills},
                {"heroKills", heroKills},
                {"itemsCrafted", itemsCrafted},
                {"relicsCrafted", relicsCrafted},
                {"transcendentRelicsCrafted", transcendentRelicsCrafted},
                {"mythicalRelicsCrafted", mythicalRelicsCrafted},
                {"shrinesRestored", shrinesRestored},
                {"oneShotChestsOpened", oneShotChestsOpened},
                {"loreNotesCollected", loreNotesCollected},
                {"greatestDamageInflicted", greatestDamageInflicted},
                {"lastHit", lastHit},
                {"lastHitBy", lastHitBy},
                {"greatestDamageReceived", greatestDamageReceived},
                {"survivalGreatestWave", survivalGreatestWave},
                {"survivalGreatestScore", survivalGreatestScore},
                {"survivalDefensesBuilt", survivalDefensesBuilt},
                {"survivalPowerUpsActivated", survivalPowerUpsActivated},
                {"endlessSouls", endlessSouls},
                {"endlessEssence", endlessEssence},
                {"difficultySkip", difficultySkip},
                {"unknown1", unknown1},
                {"unknown2", unknown2}};

  for (int i = 0; i < 3; i++) {
    json m = json{
        {"greatestMonsterKilledName", greatestMonsterKilledName[i]},
        {"lastMonsterHit", lastMonsterHit[i]},
        {"lastMonsterHitBy", lastMonsterHitBy[i]},
        {"greatestMonsterKilledLevel", greatestMonsterKilledLevel[i]},
        {"greatestMonsterKilledLifeAndMana",
         greatestMonsterKilledLifeAndMana[i]},
        {"bossKills", bossKills[i]},
    };
    auto difficulty = "difficulty_" + std::to_string(i);
    j.emplace(json{difficulty, m});
  }

  // TODO: Add skill_map

  return json{"player_stats", j};
}
