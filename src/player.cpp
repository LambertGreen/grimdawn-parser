#include "player.hpp"

#include "block_field.hpp"

player::player(const char* filename) : gdc(filename) {
  gdc.read_start();
  hdr.read(&gdc);
  gdc.read_version();
  id.read(&gdc);
  info.read(&gdc);
  bio.read(&gdc);
  inv.read(&gdc);
  stash.read(&gdc);
  respawns.read(&gdc);
  teleports.read(&gdc);
  markers.read(&gdc);
  shrines.read(&gdc);
  skills.read(&gdc);
  notes.read(&gdc);
  factions.read(&gdc);
  ui.read(&gdc);
  tutorials.read(&gdc);
  stats.read(&gdc);
  tokens.read(&gdc);
  gdc.read_end();
}

json player::get_json() const {
  json j;
  j.emplace("id", id.get_json());
  j.emplace("info", info.get_json());
  j.emplace("bio", bio.get_json());
  j.emplace("inventory", inv.get_json());
  j.emplace("stash", stash.get_json());
  j.emplace("respawns", respawns.get_json());
  j.emplace("teleports", teleports.get_json());
  j.emplace("markers", markers.get_json());
  j.emplace("shrines", shrines.get_json());
  j.emplace("skills", skills.get_json());
  j.emplace("notes", notes.get_json());
  j.emplace("factions", factions.get_json());
  j.emplace("ui", ui.get_json());
  j.emplace("tutorials", tutorials.get_json());
  j.emplace("stats", stats.get_json());
  j.emplace("tokens", tokens.get_json());
  return j;
}

void item_skill::read(gdc_file* gdc) {
  name.read(gdc);
  autoCastSkill.read(gdc);
  autoCastController.read(gdc);
  itemSlot = gdc->read_int();
  itemName.read(gdc);
}

void lore_notes::read(gdc_file* gdc) {
  const int BLOCK = 12;
  const int VERSION = 1;

  block_field b;
  ENSURE(gdc->read_block_start(&b) == BLOCK, "Unexpected block number");
  ENSURE(gdc->read_int() == VERSION, "Unexpected version number");

  names.read(gdc);

  gdc->read_block_end(&b);
}

void faction_pack::read(gdc_file* gdc) {
  const int BLOCK = 13;
  const int VERSION = 5;

  block_field b;
  ENSURE(gdc->read_block_start(&b) == BLOCK, "Unexpected block number");
  ENSURE(gdc->read_int() == VERSION, "Unexpected version number");

  faction = gdc->read_int();
  LOG_N(faction);

  factions.read(gdc);

  gdc->read_block_end(&b);
}

void faction_data::read(gdc_file* gdc) {
  modified = gdc->read_byte();
  unlocked = gdc->read_byte();
  value = gdc->read_float();
  positiveBoost = gdc->read_float();
  negativeBoost = gdc->read_float();
}

void ui_settings::read(gdc_file* gdc) {
  const int BLOCK = 14;
  const int VERSION = 5;

  block_field b;
  ENSURE(gdc->read_block_start(&b) == BLOCK, "Unexpected block number");
  ENSURE(gdc->read_int() == VERSION, "Unexpected version number");

  unknown1 = gdc->read_byte();
  unknown2 = gdc->read_int();
  unknown3 = gdc->read_byte();

  for (unsigned i = 0; i < 5; i++) {
    unknown4[i].read(gdc);
    unknown5[i].read(gdc);
    unknown6[i] = gdc->read_byte();
  }

  const int slots_len = sizeof(slots) / sizeof(slots[0]);
  for (unsigned i = 0; i < slots_len; i++) {
    slots[i].read(gdc);
  }

  cameraDistance = gdc->read_float();

  gdc->read_block_end(&b);
}

void hot_slot::read(gdc_file* gdc) {
  type = gdc->read_int();

  if (type == 0) {
    skill.read(gdc);
    isItemSkill = gdc->read_byte();
    item.read(gdc);
    equipLocation = gdc->read_int();
  } else if (type == 4) {
    item.read(gdc);
    bitmapUp.read(gdc);
    bitmapDown.read(gdc);
    label.read(gdc);
  }
}

void tutorial_pages::read(gdc_file* gdc) {
  const int BLOCK = 15;
  const int VERSION = 1;

  block_field b;
  ENSURE(gdc->read_block_start(&b) == BLOCK, "Unexpected block number");
  ENSURE(gdc->read_int() == VERSION, "Unexpected version number");

  uint32_t n = gdc->read_int();
  pages.resize(n);

  for (uint32_t i = 0; i < n; i++) {
    pages[i] = gdc->read_int();
  }

  gdc->read_block_end(&b);
}

void play_stats::read(gdc_file* gdc) {
  const int BLOCK = 16;
  const int VERSION = 11;

  block_field b;
  ENSURE(gdc->read_block_start(&b) == BLOCK, "Unexpected block number");
  ENSURE(gdc->read_int() == VERSION, "Unexpected version number");

  playTime = gdc->read_int();
  LOG_N(playTime);

  deaths = gdc->read_int();
  LOG_N(deaths);

  kills = gdc->read_int();
  LOG_N(kills);

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

  gdc->read_block_end(&b);
}

void skill_map::read(gdc_file* gdc) {
  skill.read(gdc);
  active = gdc->read_int();
}

void trigger_tokens::read(gdc_file* gdc) {
  const int BLOCK = 10;
  const int VERSION = 2;

  block_field b;
  ENSURE(gdc->read_block_start(&b) == BLOCK, "Unexpected block number");
  ENSURE(gdc->read_int() == VERSION, "Unexpected version number");

  for (unsigned i = 0; i < 3; i++) {
    tokens[i].read(gdc);
  }

  gdc->read_block_end(&b);
}

void item::read(gdc_file* gdc) {
  baseName.read(gdc);
  LOG(baseName);

  prefixName.read(gdc);
  LOG(prefixName);

  suffixName.read(gdc);
  LOG(suffixName);

  modifierName.read(gdc);
  LOG(modifierName);

  transmuteName.read(gdc);
  LOG(transmuteName);

  seed = gdc->read_int();
  LOG_N(seed);

  relicName.read(gdc);
  LOG(relicName);

  relicBonus.read(gdc);
  LOG(relicBonus);

  relicSeed = gdc->read_int();
  LOG_N(relicSeed);

  augmentName.read(gdc);
  LOG(augmentName);

  unknown = gdc->read_int();
  LOG_N(unknown);

  augmentSeed = gdc->read_int();
  LOG_N(augmentSeed);

  var1 = gdc->read_int();
  LOG_N(var1);

  stackCount = gdc->read_int();
  LOG_N(stackCount);
}

void string::read(gdc_file* gdc) {
  uint32_t len = gdc->read_int();
  if (len > 256) {
    throw std::runtime_error("Length of string is suspiciously long: " +
                             std::to_string(len));
  }

  clear();
  reserve(len);

  for (uint32_t i = 0; i < len; i++) {
    push_back(gdc->read_byte());
  }
}

void wstring::read(gdc_file* gdc) {
  uint32_t len = gdc->read_int();

  clear();
  reserve(len);

  for (uint32_t i = 0; i < len; i++) {
    wchar_t c = gdc->read_byte();
    c |= gdc->read_byte() << 8;
    push_back(c);
  }
}
