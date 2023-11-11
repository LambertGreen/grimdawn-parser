#include "gdc_file.hpp"
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
  std::cout << "Next_int: " << std::to_string(vv) << std::endl;
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

  if (ftell(fp) != end)
    throw e;
}

template <typename T> void vector<T>::read(gdc_file *gdc) {
  uint32_t n = gdc->read_int();
  std::cout << "Vector size: " << std::to_string(n) << std::endl;

  this->resize(n);
  T *ptr = this->data();

  for (uint32_t i = 0; i < n; i++) {
    ptr[i].read(gdc);
  }
}

void header::read(gdc_file *gdc) {
  version = gdc->read_int();
  std::cout << "version:" << std::to_string(version) << std::endl;
  if (version != 1 && version != 2) {
    throw std::runtime_error("Unsupported version: " + std::to_string(version));
  }

  name.read(gdc);
  std::wcout << "name:" << name << std::endl;

  sex = gdc->read_byte();
  std::cout << "sex:" << std::to_string(sex) << std::endl;

  classId.read(gdc);
  std::cout << "classId:" << classId << std::endl;

  level = gdc->read_int();
  std::cout << "level:" << std::to_string(level) << std::endl;

  hardcore = gdc->read_byte();
  std::cout << "hardcore:" << std::to_string(hardcore) << std::endl;

  if (version >= 2) {
    expansionStatus = gdc->read_byte();
    std::cout << "expansionStatus:" << std::to_string(expansionStatus)
              << std::endl;
  }
}

void character_info::read(gdc_file *gdc) {
  block b;

  if (gdc->read_block_start(&b) != 1) {
    throw std::runtime_error("character_info: start block is not 1");
  }

  // version
  const auto v = gdc->read_int();
  if (v != 5) {
    throw std::runtime_error("character_info: version is not 5, but " +
                             std::to_string(v));
  }

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

  gdc->read_block_end(&b);
}

void character_bio::read(gdc_file *gdc) {
  block b;

  if (gdc->read_block_start(&b) != 2)
    throw e;

  if (gdc->read_int() != 8) // version
    throw e;

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

  gdc->read_block_end(&b);
}

void inventory::read(gdc_file *gdc) {
  block b;

  if (gdc->read_block_start(&b) != 3)
    throw e;

  if (gdc->read_int() != 4) // version
    throw e;

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

  gdc->read_block_end(&b);
}

void inventory_sack::read(gdc_file *gdc) {
  block b;

  if (gdc->read_block_start(&b))
    throw e;

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

  block b;
  const auto block_val = gdc->read_block_start(&b);
  if (block_val != BLOCK) {
    throw std::runtime_error(
        "character_stash:read: unexpected int BLOCK value of " +
        std::to_string(block_val));
  }

  width = gdc->read_int();
  height = gdc->read_int();

  items.read(gdc);

  gdc->read_block_end(&b);
}

void character_stash::read(gdc_file *gdc) {
  const int BLOCK = 4;
  const int VERSION = 6;

  block b;
  const auto block_val = gdc->read_block_start(&b);
  if (block_val != BLOCK) {
    throw std::runtime_error(
        "character_stash:read: unexpected int BLOCK value of " +
        std::to_string(block_val));
  }

  const auto v = gdc->read_int();
  if (v != VERSION) {
    throw std::runtime_error("character_stash:read: unexpected int value of " +
                             std::to_string(v));
  }

  pages.read(gdc);

  gdc->read_block_end(&b);
}

void stash_item::read(gdc_file *gdc) {
  item::read(gdc);
  x = gdc->read_float();
  y = gdc->read_float();
}

void respawn_list::read(gdc_file *gdc) {
  block b;

  if (gdc->read_block_start(&b) != 5)
    throw e;

  if (gdc->read_int() != 1) // version
    throw e;

  for (unsigned i = 0; i < 3; i++) {
    uids[i].read(gdc);
  }

  for (unsigned i = 0; i < 3; i++) {
    spawn[i].read(gdc);
  }

  gdc->read_block_end(&b);
}

void teleport_list::read(gdc_file *gdc) {
  block b;

  if (gdc->read_block_start(&b) != 6)
    throw e;

  if (gdc->read_int() != 1) // version
    throw e;

  for (unsigned i = 0; i < 3; i++) {
    uids[i].read(gdc);
  }

  gdc->read_block_end(&b);
}

void marker_list::read(gdc_file *gdc) {
  block b;

  if (gdc->read_block_start(&b) != 7)
    throw e;

  if (gdc->read_int() != 1) // version
    throw e;

  for (unsigned i = 0; i < 3; i++) {
    uids[i].read(gdc);
  }

  gdc->read_block_end(&b);
}

void shrine_list::read(gdc_file *gdc) {
  block b;

  if (gdc->read_block_start(&b) != 17)
    throw e;

  if (gdc->read_int() != 2) // version
    throw e;

  for (unsigned i = 0; i < 6; i++) {
    uids[i].read(gdc);
  }

  gdc->read_block_end(&b);
}

void character_skills::read(gdc_file *gdc) {
  block b;

  if (gdc->read_block_start(&b) != 8)
    throw e;

  if (gdc->read_int() != 5) // version
    throw e;

  skills.read(gdc);
  masteriesAllowed = gdc->read_int();
  skillReclamationPointsUsed = gdc->read_int();
  devotionReclamationPointsUsed = gdc->read_int();
  itemSkills.read(gdc);

  gdc->read_block_end(&b);
}

void skill::read(gdc_file *gdc) {
  name.read(gdc);
  level = gdc->read_int();
  enabled = gdc->read_byte();
  devotionLevel = gdc->read_int();
  experience = gdc->read_int();
  active = gdc->read_int();
  unknown1 = gdc->read_byte();
  unknown2 = gdc->read_byte();
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
  block b;

  if (gdc->read_block_start(&b) != 12)
    throw e;

  if (gdc->read_int() != 1) // version
    throw e;

  names.read(gdc);

  gdc->read_block_end(&b);
}

void faction_pack::read(gdc_file *gdc) {
  block b;

  if (gdc->read_block_start(&b) != 13)
    throw e;

  if (gdc->read_int() != 5) // version
    throw e;

  faction = gdc->read_int();
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
  block b;

  if (gdc->read_block_start(&b) != 14)
    throw e;

  if (gdc->read_int() != 4) // version
    throw e;

  unknown1 = gdc->read_byte();
  unknown2 = gdc->read_int();
  unknown3 = gdc->read_byte();

  for (unsigned i = 0; i < 5; i++) {
    unknown4[i].read(gdc);
    unknown5[i].read(gdc);
    unknown6[i] = gdc->read_byte();
  }

  for (unsigned i = 0; i < 36; i++) {
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
  block b;

  if (gdc->read_block_start(&b) != 15)
    throw e;

  if (gdc->read_int() != 1) // version
    throw e;

  uint32_t n = gdc->read_int();
  pages.resize(n);

  for (uint32_t i = 0; i < n; i++) {
    pages[i] = gdc->read_int();
  }

  gdc->read_block_end(&b);
}

void play_stats::read(gdc_file *gdc) {
  block b;

  if (gdc->read_block_start(&b) != 16)
    throw e;

  if (gdc->read_int() != 9) // version
    throw e;

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

  survivalWaveTier = gdc->read_int();
  greatestSurvivalScore = gdc->read_int();
  cooldownRemaining = gdc->read_int();
  cooldownTotal = gdc->read_int();

  unknown1 = gdc->read_int();
  unknown2 = gdc->read_int();

  gdc->read_block_end(&b);
}

void trigger_tokens::read(gdc_file *gdc) {
  block b;

  if (gdc->read_block_start(&b) != 10)
    throw e;

  if (gdc->read_int() != 2) // version
    throw e;

  for (unsigned i = 0; i < 3; i++) {
    tokens[i].read(gdc);
  }

  gdc->read_block_end(&b);
}

void item::read(gdc_file *gdc) {
  baseName.read(gdc);
  prefixName.read(gdc);
  suffixName.read(gdc);
  modifierName.read(gdc);
  transmuteName.read(gdc);
  seed = gdc->read_int();
  relicName.read(gdc);
  relicBonus.read(gdc);
  relicSeed = gdc->read_int();
  augmentName.read(gdc);
  unknown = gdc->read_int();
  augmentSeed = gdc->read_int();
  var1 = gdc->read_int();
  stackCount = gdc->read_int();
}

void uid::read(gdc_file *gdc) {
  for (unsigned i = 0; i < 16; i++) {
    id[i] = gdc->read_byte();
  }
}

void string::read(gdc_file *gdc) {
  uint32_t len = gdc->read_int();
  // LOG_N(len);
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
    fprintf(stderr, "Usage: %s <in file> <out file>\n", argv[0]);
    return 1;
  }

  gdc_file gdc;

  try {
    gdc.read(argv[1]);
  } catch (const std::runtime_error &e) {
    std::cout << "Exception:" << e.what() << std::endl;
  } catch (const std::exception &e) {
    printf("Error reading file: %s\n", argv[1]);
    return 1;
  }

  return 0;
}
