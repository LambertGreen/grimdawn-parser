#include "block.hpp"
#include "common.hpp"
#include "gdc_file.hpp"
#include "skill_map.hpp"
#include <string>

void gdc_file::read(const char *filename) {
  file f(filename, "rb");

  if (!(fp = f.fp)) {
    throw std::runtime_error("gdc_file:read: failed!");
  }

  if (fseek(fp, 0, SEEK_END)) {
    throw std::runtime_error("gdc_file:read: failed fseek!");
  }

  long end = ftell(fp);

  if (fseek(fp, 0, SEEK_SET)) {
    throw std::runtime_error("gdc_file:read: failed fseek!");
  }

  read_key();
  const auto v = read_int();
  if (v != 0x58434447) {
    throw std::runtime_error("gdc_file:read: unexpected int value of " +
                             std::to_string(v));
  }

  hdr.read(this);

  const auto vv = next_int();
  if (vv != 0) {
    throw std::runtime_error("gdc_file:read: next int is not zero");
  }

  const auto v3 = read_int();
  if (v3 != 8) // version
  {
    throw std::runtime_error("gdc_file:read: unexpected int value of " +
                             std::to_string(v3));
  }

  id.read(this);
  info.read(this);
  bio.read(this);
  inv.read(this);
  stash.read(this);
  respawns.read(this);
  teleports.read(this);
  markers.read(this);
  shrines.read(this);
  skills.read(this);
  notes.read(this);
  factions.read(this);
  ui.read(this);
  tutorials.read(this);
  stats.read(this);
  tokens.read(this);

  // Write out Json
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
  j.emplace("notes", notes.get_json());
  j.emplace("factions", factions.get_json());
  j.emplace("stats", stats.get_json());
  std::cout << j.dump() << std::endl;

  if (ftell(fp) != end)
    throw e;
}

template <typename T> void vector<T>::read(gdc_file *gdc) {
  uint32_t n = gdc->read_int();

  this->resize(n);
  T *ptr = this->data();

  for (uint32_t i = 0; i < n; i++) {
    ptr[i].read(gdc);
  }
}

void block::read_start(gdc_file *gdc) {

  num = gdc->read_block_start(&b);
  version = gdc->read_int();
}

void block::read_end(gdc_file *gdc) { gdc->read_block_end(&b); }

void header::read(gdc_file *gdc) {
  version = gdc->read_int();
  if (version != 1 && version != 2) {
    throw std::runtime_error("Unsupported version: " + std::to_string(version));
  }

  name.read(gdc);
  LOG_W(name);

  sex = gdc->read_byte();
  LOG_N(sex);

  classId.read(gdc);
  LOG(classId);

  level = gdc->read_int();
  LOG_N(level);

  hardcore = gdc->read_byte();
  LOG_N(hardcore);

  expansionStatus = gdc->read_byte();
  LOG_N(expansionStatus);
}

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

void character_bio::read(gdc_file *gdc) {
  const int BLOCK = 2;
  const int VERSION = 8;

  block b;
  b.read_start(gdc);
  ENSURE(b.num == BLOCK, "Unexpected block number");
  ENSURE(b.version == VERSION, "Unexpected version number");

  level = gdc->read_int();
  experience = gdc->read_int();
  modifierPoints = gdc->read_int();
  skillPoints = gdc->read_int();
  devotionPoints = gdc->read_int();
  totalDevotion = gdc->read_int();
  physique = gdc->read_float();
  cunning = gdc->read_float();
  spirit = gdc->read_float();
  health = gdc->read_float();
  energy = gdc->read_float();

  b.read_end(gdc);
}

void inventory::read(gdc_file *gdc) {
  const int BLOCK = 3;
  const int VERSION = 4;

  block b;
  b.read_start(gdc);
  ENSURE(b.num == BLOCK, "Unexpected block number");
  ENSURE(b.version == VERSION, "Unexpected version number");

  if ((flag = gdc->read_byte())) {
    uint32_t n = gdc->read_int();
    focused = gdc->read_int();
    selected = gdc->read_int();

    sacks.resize(n);

    for (uint32_t i = 0; i < n; i++) {
      sacks[i].read(gdc);
    }

    useAlternate = gdc->read_byte();

    for (unsigned i = 0; i < 12; i++) {
      equipment[i].read(gdc);
    }

    alternate1 = gdc->read_byte();

    for (unsigned i = 0; i < 2; i++) {
      weapon1[i].read(gdc);
    }

    alternate2 = gdc->read_byte();

    for (unsigned i = 0; i < 2; i++) {
      weapon2[i].read(gdc);
    }
  }

  b.read_end(gdc);
}

void inventory_sack::read(gdc_file *gdc) {
  block_field b;

  ENSURE(gdc->read_block_start(&b) == 0, "Unexpected block number");

  tempBool = gdc->read_byte();
  items.read(gdc);

  gdc->read_block_end(&b);
}

void inventory_item::read(gdc_file *gdc) {
  item::read(gdc);
  x = gdc->read_int();
  y = gdc->read_int();
}

void inventory_equipment::read(gdc_file *gdc) {
  item::read(gdc);

  attached = gdc->read_byte();
}

void stash_page::read(gdc_file *gdc) {
  const int BLOCK = 0;

  block_field b;
  const auto block_val = gdc->read_block_start(&b);
  ENSURE(block_val == BLOCK, "Unexpected block number");

  width = gdc->read_int();
  height = gdc->read_int();

  items.read(gdc);

  gdc->read_block_end(&b);
}

void character_stash::read(gdc_file *gdc) {
  const int BLOCK = 4;
  const int VERSION = 6;

  block b;
  b.read_start(gdc);
  ENSURE(b.num == BLOCK, "Unexpected block number");
  ENSURE(b.version == VERSION, "Unexpected version number");

  pages.read(gdc);

  b.read_end(gdc);
}

void stash_item::read(gdc_file *gdc) {
  item::read(gdc);
  x = gdc->read_float();
  LOG_N(x);

  y = gdc->read_float();
  LOG_N(y);
}

void respawn_list::read(gdc_file *gdc) {
  const int BLOCK = 5;
  const int VERSION = 1;

  block b;
  b.read_start(gdc);
  ENSURE(b.num == BLOCK, "Unexpected block number");
  ENSURE(b.version == VERSION, "Unexpected version number");

  const int uids_len = sizeof(uids) / sizeof(uids[0]);
  for (unsigned i = 0; i < uids_len; i++) {
    uids[i].read(gdc);
  }

  const int spawn_len = sizeof(spawns) / sizeof(spawns[0]);
  for (unsigned i = 0; i < spawn_len; i++) {
    spawns[i].read(gdc);
  }

  b.read_end(gdc);
}

void teleport_list::read(gdc_file *gdc) {
  const int BLOCK = 6;
  const int VERSION = 1;

  block b;
  b.read_start(gdc);
  ENSURE(b.num == BLOCK, "Unexpected block number");
  ENSURE(b.version == VERSION, "Unexpected version number");

  const int uids_len = sizeof(uids) / sizeof(uids[0]);
  for (unsigned i = 0; i < uids_len; i++) {
    uids[i].read(gdc);
  }

  b.read_end(gdc);
}

void marker_list::read(gdc_file *gdc) {
  const int BLOCK = 7;
  const int VERSION = 1;

  block b;
  b.read_start(gdc);
  ENSURE(b.num == BLOCK, "Unexpected block number");
  ENSURE(b.version == VERSION, "Unexpected version number");

  for (unsigned i = 0; i < sizeof(uids) / sizeof(uids[0]); i++) {
    uids[i].read(gdc);
  }

  b.read_end(gdc);
}

void shrine_list::read(gdc_file *gdc) {
  const int BLOCK = 17;
  const int VERSION = 2;

  block b;
  b.read_start(gdc);
  ENSURE(b.num == BLOCK, "Unexpected block number");
  ENSURE(b.version == VERSION, "Unexpected version number");

  for (unsigned i = 0; i < sizeof(uids) / sizeof(uids[0]); i++) {
    uids[i].read(gdc);
  }

  b.read_end(gdc);
}

void character_skills::read(gdc_file *gdc) {
  const int BLOCK = 8;
  const int VERSION = 5;

  block_field b;
  ENSURE(gdc->read_block_start(&b) == BLOCK, "Unexpected block number");
  ENSURE(gdc->read_int() == VERSION, "Unexpected version number");

  skills.read(gdc);

  masteriesAllowed = gdc->read_int();
  LOG_N(masteriesAllowed);

  skillReclamationPointsUsed = gdc->read_int();
  LOG_N(skillReclamationPointsUsed);

  devotionReclamationPointsUsed = gdc->read_int();
  LOG_N(devotionReclamationPointsUsed);

  itemSkills.read(gdc);

  gdc->read_block_end(&b);
}

void skill::read(gdc_file *gdc) {
  name.read(gdc);
  LOG(name);

  level = gdc->read_int();
  LOG_N(level);

  enabled = gdc->read_byte();
  LOG_N(enabled);

  devotionLevel = gdc->read_int();
  LOG_N(devotionLevel);

  experience = gdc->read_int();
  LOG_N(experience);

  active = gdc->read_int();
  LOG_N(active);

  unknown1 = gdc->read_byte();
  LOG_N(unknown1);

  unknown2 = gdc->read_byte();
  LOG_N(unknown2);

  autoCastSkill.read(gdc);
  autoCastController.read(gdc);
}

void item_skill::read(gdc_file *gdc) {
  name.read(gdc);
  autoCastSkill.read(gdc);
  autoCastController.read(gdc);
  itemSlot = gdc->read_int();
  itemName.read(gdc);
}

void lore_notes::read(gdc_file *gdc) {
  const int BLOCK = 12;
  const int VERSION = 1;

  block_field b;
  ENSURE(gdc->read_block_start(&b) == BLOCK, "Unexpected block number");
  ENSURE(gdc->read_int() == VERSION, "Unexpected version number");

  names.read(gdc);

  gdc->read_block_end(&b);
}

void faction_pack::read(gdc_file *gdc) {
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

void faction_data::read(gdc_file *gdc) {
  modified = gdc->read_byte();
  unlocked = gdc->read_byte();
  value = gdc->read_float();
  positiveBoost = gdc->read_float();
  negativeBoost = gdc->read_float();
}

void ui_settings::read(gdc_file *gdc) {
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

void hot_slot::read(gdc_file *gdc) {
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

void tutorial_pages::read(gdc_file *gdc) {
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

void play_stats::read(gdc_file *gdc) {
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

void skill_map::read(gdc_file *gdc) {
  skill.read(gdc);
  active = gdc->read_int();
}

void trigger_tokens::read(gdc_file *gdc) {
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

void item::read(gdc_file *gdc) {
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

void uid::read(gdc_file *gdc) {
  for (unsigned i = 0; i < 16; i++) {
    id[i] = gdc->read_byte();
  }
}

void string::read(gdc_file *gdc) {
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

void wstring::read(gdc_file *gdc) {
  uint32_t len = gdc->read_int();

  clear();
  reserve(len);

  for (uint32_t i = 0; i < len; i++) {
    wchar_t c = gdc->read_byte();
    c |= gdc->read_byte() << 8;
    push_back(c);
  }
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <player.gdc file>\n", argv[0]);
    return 1;
  }

  try {
    gdc_file gdc;
    gdc.read(argv[1]);
  } catch (const std::runtime_error &e) {
    std::cout << "Exception:" << e.what() << std::endl;
  } catch (const std::exception &e) {
    printf("Error reading file: %s\n", argv[1]);
    return 1;
  }

  return 0;
}
