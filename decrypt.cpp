#include <_types/_uint8_t.h>
#include <stdexcept>
#include <stdint.h>
#include <stdio.h>

#include <exception>
#include <iostream>
#include <string>
#include <vector>

static std::exception e;
#define LOG(field) std::cout << #field << ": " << field << std::endl;
#define LOG_N(field)                                                           \
  std::cout << #field << ": " << std::to_string(field) << std::endl;

class gdc_file;

template <typename T> class vector : public std::vector<T> {
public:
  void read(gdc_file *);
  void write(gdc_file *);
};

class string : public std::string {
public:
  void read(gdc_file *);
  void write(gdc_file *);
};

class wstring : public std::wstring {
public:
  void read(gdc_file *);
  void write(gdc_file *);
};

class uid {
public:
  uint8_t id[16];

  void read(gdc_file *);
  void write(gdc_file *);
};

class item {
public:
  string baseName;
  string prefixName;
  string suffixName;
  string modifierName;
  string transmuteName;
  string relicName;
  string relicBonus;
  string augmentName;
  uint32_t stackCount;
  uint32_t seed;
  uint32_t relicSeed;
  uint32_t unknown;
  uint32_t augmentSeed;
  uint32_t var1;

  void read(gdc_file *);
  void write(gdc_file *);
};

class header {
public:
  uint32_t version{};
  wstring name;
  string classId;
  uint32_t level{};
  uint8_t sex{};
  uint8_t hardcore{};
  uint8_t expansionStatus{};
  uint8_t isInMainQuest{};
  string className;

  void read(gdc_file *);
  void write(gdc_file *);
};

class character_info {
public:
  string texture;
  uint32_t money;
  uint32_t currentTribute;
  uint8_t isInMainQuest;
  uint8_t hasBeenInGame;
  uint8_t difficulty;
  uint8_t greatestDifficulty;
  uint8_t greatestSurvivalDifficulty;
  uint8_t compassState;
  uint8_t skillWindowShowHelp;
  uint8_t alternateConfig;
  uint8_t alternateConfigEnabled;
  vector<uint8_t> lootFilters;

  void read(gdc_file *);
  void write(gdc_file *);
};

class character_bio {
public:
  uint32_t level;
  uint32_t experience;
  uint32_t modifierPoints;
  uint32_t skillPoints;
  uint32_t devotionPoints;
  uint32_t totalDevotion;
  float physique;
  float cunning;
  float spirit;
  float health;
  float energy;

  void read(gdc_file *);
  void write(gdc_file *);
};

class inventory_item : public item {
public:
  uint32_t x;
  uint32_t y;

  void read(gdc_file *);
  void write(gdc_file *);
};

class inventory_sack {
public:
  vector<inventory_item> items;
  uint8_t tempBool;

  void read(gdc_file *);
  void write(gdc_file *);
};

class inventory_equipment : public item {
public:
  uint8_t attached;

  void read(gdc_file *);
  void write(gdc_file *);
};

class inventory {
public:
  vector<inventory_sack> sacks;
  inventory_equipment equipment[12];
  inventory_equipment weapon1[2];
  inventory_equipment weapon2[2];
  uint32_t focused;
  uint32_t selected;
  uint8_t flag;
  uint8_t useAlternate;
  uint8_t alternate1;
  uint8_t alternate2;

  void read(gdc_file *);
  void write(gdc_file *);
};

class stash_item : public item {
public:
  float x;
  float y;

  void read(gdc_file *);
  void write(gdc_file *);
};

class character_stash {
public:
  vector<stash_item> items;
  uint32_t width;
  uint32_t height;

  void read(gdc_file *);
  void write(gdc_file *);
};

class respawn_list {
public:
  vector<uid> uids[3];
  uid spawn[3];

  void read(gdc_file *);
  void write(gdc_file *);
};

class teleport_list {
public:
  vector<uid> uids[3];

  void read(gdc_file *);
  void write(gdc_file *);
};

class marker_list {
public:
  vector<uid> uids[3];

  void read(gdc_file *);
  void write(gdc_file *);
};

class shrine_list {
public:
  vector<uid> uids[6];

  void read(gdc_file *);
  void write(gdc_file *);
};

class skill {
public:
  string name;
  string autoCastSkill;
  string autoCastController;
  uint32_t level;
  uint32_t devotionLevel;
  uint32_t experience;
  uint32_t active;
  uint8_t enabled;
  uint8_t unknown1;
  uint8_t unknown2;

  void read(gdc_file *);
  void write(gdc_file *);
};

class item_skill {
public:
  string name;
  string autoCastSkill;
  string autoCastController;
  string itemName;
  uint32_t itemSlot;

  void read(gdc_file *);
  void write(gdc_file *);
};

class character_skills {
public:
  vector<skill> skills;
  vector<item_skill> itemSkills;
  uint32_t masteriesAllowed;
  uint32_t skillReclamationPointsUsed;
  uint32_t devotionReclamationPointsUsed;

  void read(gdc_file *);
  void write(gdc_file *);
};

class lore_notes {
public:
  vector<string> names;

  void read(gdc_file *);
  void write(gdc_file *);
};

class faction_data {
public:
  float value;
  float positiveBoost;
  float negativeBoost;
  uint8_t modified;
  uint8_t unlocked;

  void read(gdc_file *);
  void write(gdc_file *);
};

class faction_pack {
public:
  vector<faction_data> factions;
  uint32_t faction;

  void read(gdc_file *);
  void write(gdc_file *);
};

class hot_slot {
public:
  string skill;
  string item;
  string bitmapUp;
  string bitmapDown;
  wstring label;
  uint32_t type;
  uint32_t equipLocation;
  uint8_t isItemSkill;

  void read(gdc_file *);
  void write(gdc_file *);
};

class ui_settings {
public:
  hot_slot slots[36];
  string unknown4[5];
  string unknown5[5];
  uint32_t unknown2;
  float cameraDistance;
  uint8_t unknown6[5];
  uint8_t unknown1;
  uint8_t unknown3;

  void read(gdc_file *);
  void write(gdc_file *);
};

class tutorial_pages {
public:
  vector<uint32_t> pages;

  void read(gdc_file *);
  void write(gdc_file *);
};

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

class trigger_tokens {
public:
  vector<string> tokens[3];

  void read(gdc_file *);
  void write(gdc_file *);
};

class file {
public:
  FILE *fp;

  file(const char *name, const char *mode) { fp = fopen(name, mode); }

  ~file() {
    if (fp)
      fclose(fp);
  }

private:
  file(const file &);            // = delete;
  file &operator=(const file &); // = delete;
};

struct block {
  uint32_t len;
  long end;
};

class gdc_file {
private:
  FILE *fp;
  uint32_t key;
  uint32_t table[256];

public:
  header hdr;
  uid id;
  character_info info;
  character_bio bio;
  inventory inv;
  character_stash stash;
  respawn_list respawns;
  teleport_list teleports;
  marker_list markers;
  shrine_list shrines;
  character_skills skills;
  lore_notes notes;
  faction_pack factions;
  ui_settings ui;
  tutorial_pages tutorials;
  play_stats stats;
  trigger_tokens tokens;

  void read(const char *);
  void write(const char *);

private:
  void read_key() {
    uint32_t k;

    if (fread(&k, 4, 1, fp) != 1) {
      throw std::runtime_error("read_key: failed to read uint32");
    }

    k ^= 0x55555555;

    key = k;

    for (unsigned i = 0; i < 256; i++) {
      k = (k >> 1) | (k << 31);
      k *= 39916801;
      table[i] = k;
    }
  }

  uint32_t next_int() {
    uint32_t ret;

    if (fread(&ret, 4, 1, fp) != 1) {
      throw std::runtime_error("next_int: failed to read uint32");
    }

    ret ^= key;

    return ret;
  }

  void update_key(void *ptr, uint32_t len) {
    uint8_t *p = (uint8_t *)ptr;

    for (uint32_t i = 0; i < len; i++) {
      key ^= table[p[i]];
    }
  }

public:
  uint32_t read_int() {
    uint32_t val;

    if (fread(&val, 4, 1, fp) != 1) {
      throw std::runtime_error("read_int: failed to read uint32");
    }

    uint32_t ret = val ^ key;

    update_key(&val, 4);

    return ret;
  }

  uint16_t read_short() {
    uint16_t val;

    if (fread(&val, 2, 1, fp) != 1) {
      throw std::runtime_error("read_short: failed to read uint16");
    }

    uint16_t ret = val ^ key;

    update_key(&val, 2);

    return ret;
  }

  uint8_t read_byte() {
    uint8_t val;

    if (fread(&val, 1, 1, fp) != 1) {
      throw std::runtime_error("read_byte: failed to read uint8");
    }

    uint8_t ret = val ^ key;

    update_key(&val, 1);

    return ret;
  }

  float read_float() {
    union {
      float f;
      int i;
    } u;
    u.i = read_int();
    return u.f;
  }

  uint32_t read_block_start(block *b) {
    uint32_t ret = read_int();

    b->len = next_int();
    b->end = ftell(fp) + b->len;

    return ret;
  }

  void read_block_end(block *b) {
    if (ftell(fp) != b->end) {
      throw std::runtime_error("read_block_end: failed!");
    }

    if (next_int()) {
      throw std::runtime_error("read_block_end: failed!");
    }
  }

  void write_int(uint32_t val) {
    if (fwrite(&val, 4, 1, fp) != 1)
      throw e;
  }

  void write_short(uint16_t val) {
    if (fwrite(&val, 2, 1, fp) != 1)
      throw e;
  }

  void write_byte(uint8_t val) {
    if (fwrite(&val, 1, 1, fp) != 1)
      throw e;
  }

  void write_float(float val) {
    if (fwrite(&val, 4, 1, fp) != 1)
      throw e;
  }

  void write_block_start(block *b, uint32_t n) {
    write_int(n);
    write_int(0);
    b->end = ftell(fp);
  }

  void write_block_end(block *b) {
    long pos = ftell(fp);

    if (fseek(fp, b->end - 4, SEEK_SET))
      throw e;

    write_int(pos - b->end);

    if (fseek(fp, pos, SEEK_SET))
      throw e;

    write_int(0);
  }
};

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

void gdc_file::write(const char *filename) {
  file f(filename, "wb");

  if (!(fp = f.fp))
    throw e;

  write_int(0x55555555);
  write_int(0x58434447);
  write_int(1);

  hdr.write(this);

  write_int(0);

  write_int(7); // version
  id.write(this);

  info.write(this);
  bio.write(this);
  inv.write(this);
  stash.write(this);
  respawns.write(this);
  teleports.write(this);
  markers.write(this);
  shrines.write(this);
  skills.write(this);
  notes.write(this);
  factions.write(this);
  ui.write(this);
  tutorials.write(this);
  stats.write(this);
  tokens.write(this);

  if (fflush(fp))
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

template <typename T> void vector<T>::write(gdc_file *gdc) {
  uint32_t n = this->size();
  gdc->write_int(n);

  T *ptr = this->data();
  for (uint32_t i = 0; i < n; i++) {
    ptr[i].write(gdc);
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

void header::write(gdc_file *gdc) {
  name.write(gdc);
  gdc->write_byte(sex);
  classId.write(gdc);
  gdc->write_int(level);
  gdc->write_byte(hardcore);
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

void character_info::write(gdc_file *gdc) {
  block b;

  gdc->write_block_start(&b, 1);
  gdc->write_int(4); // version

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

  gdc->write_block_end(&b);
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

void character_bio::write(gdc_file *gdc) {
  block b;

  gdc->write_block_start(&b, 2);
  gdc->write_int(8); // version

  gdc->write_int(level);
  gdc->write_int(experience);
  gdc->write_int(modifierPoints);
  gdc->write_int(skillPoints);
  gdc->write_int(devotionPoints);
  gdc->write_int(totalDevotion);
  gdc->write_float(physique);
  gdc->write_float(cunning);
  gdc->write_float(spirit);
  gdc->write_float(health);
  gdc->write_float(energy);

  gdc->write_block_end(&b);
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

void inventory::write(gdc_file *gdc) {
  block b;

  gdc->write_block_start(&b, 3);
  gdc->write_int(4); // version

  gdc->write_byte(flag);

  if (flag) {
    uint32_t n = sacks.size();
    gdc->write_int(n);
    gdc->write_int(focused);
    gdc->write_int(selected);

    for (uint32_t i = 0; i < n; i++) {
      sacks[i].write(gdc);
    }

    gdc->write_byte(useAlternate);

    for (unsigned i = 0; i < 12; i++) {
      equipment[i].write(gdc);
    }

    gdc->write_byte(alternate1);

    for (unsigned i = 0; i < 2; i++) {
      weapon1[i].write(gdc);
    }

    gdc->write_byte(alternate2);

    for (unsigned i = 0; i < 2; i++) {
      weapon2[i].write(gdc);
    }
  }

  gdc->write_block_end(&b);
}

void inventory_sack::read(gdc_file *gdc) {
  block b;

  if (gdc->read_block_start(&b))
    throw e;

  tempBool = gdc->read_byte();
  items.read(gdc);

  gdc->read_block_end(&b);
}

void inventory_sack::write(gdc_file *gdc) {
  block b;

  gdc->write_block_start(&b, 0);

  gdc->write_byte(tempBool);
  items.write(gdc);

  gdc->write_block_end(&b);
}

void inventory_item::read(gdc_file *gdc) {
  item::read(gdc);
  x = gdc->read_int();
  y = gdc->read_int();
}

void inventory_item::write(gdc_file *gdc) {
  item::write(gdc);
  gdc->write_int(x);
  gdc->write_int(y);
}

void inventory_equipment::read(gdc_file *gdc) {
  item::read(gdc);
  attached = gdc->read_byte();
}

void inventory_equipment::write(gdc_file *gdc) {
  item::write(gdc);
  gdc->write_byte(attached);
}

void character_stash::read(gdc_file *gdc) {
  block b;

  if (gdc->read_block_start(&b) != 4)
    throw e;

  if (gdc->read_int() != 5) // version
    throw e;

  width = gdc->read_int();
  height = gdc->read_int();
  items.read(gdc);

  gdc->read_block_end(&b);
}

void character_stash::write(gdc_file *gdc) {
  block b;

  gdc->write_block_start(&b, 4);
  gdc->write_int(5); // version

  gdc->write_int(width);
  gdc->write_int(height);
  items.write(gdc);

  gdc->write_block_end(&b);
}

void stash_item::read(gdc_file *gdc) {
  item::read(gdc);
  x = gdc->read_float();
  y = gdc->read_float();
}

void stash_item::write(gdc_file *gdc) {
  item::write(gdc);
  gdc->write_float(x);
  gdc->write_float(y);
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

void respawn_list::write(gdc_file *gdc) {
  block b;

  gdc->write_block_start(&b, 5);
  gdc->write_int(1); // version

  for (unsigned i = 0; i < 3; i++) {
    uids[i].write(gdc);
  }

  for (unsigned i = 0; i < 3; i++) {
    spawn[i].write(gdc);
  }

  gdc->write_block_end(&b);
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

void teleport_list::write(gdc_file *gdc) {
  block b;

  gdc->write_block_start(&b, 6);
  gdc->write_int(1); // version

  for (unsigned i = 0; i < 3; i++) {
    uids[i].write(gdc);
  }

  gdc->write_block_end(&b);
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

void marker_list::write(gdc_file *gdc) {
  block b;

  gdc->write_block_start(&b, 7);
  gdc->write_int(1); // version

  for (unsigned i = 0; i < 3; i++) {
    uids[i].write(gdc);
  }

  gdc->write_block_end(&b);
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

void shrine_list::write(gdc_file *gdc) {
  block b;

  gdc->write_block_start(&b, 17);
  gdc->write_int(2); // version

  for (unsigned i = 0; i < 6; i++) {
    uids[i].write(gdc);
  }

  gdc->write_block_end(&b);
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

void character_skills::write(gdc_file *gdc) {
  block b;

  gdc->write_block_start(&b, 8);
  gdc->write_int(5); // version

  skills.write(gdc);
  gdc->write_int(masteriesAllowed);
  gdc->write_int(skillReclamationPointsUsed);
  gdc->write_int(devotionReclamationPointsUsed);
  itemSkills.write(gdc);

  gdc->write_block_end(&b);
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

void skill::write(gdc_file *gdc) {
  name.write(gdc);
  gdc->write_int(level);
  gdc->write_byte(enabled);
  gdc->write_int(devotionLevel);
  gdc->write_int(experience);
  gdc->write_int(active);
  gdc->write_byte(unknown1);
  gdc->write_byte(unknown2);
  autoCastSkill.write(gdc);
  autoCastController.write(gdc);
}

void item_skill::read(gdc_file *gdc) {
  name.read(gdc);
  autoCastSkill.read(gdc);
  autoCastController.read(gdc);
  itemSlot = gdc->read_int();
  itemName.read(gdc);
}

void item_skill::write(gdc_file *gdc) {
  name.write(gdc);
  autoCastSkill.write(gdc);
  autoCastController.write(gdc);
  gdc->write_int(itemSlot);
  itemName.write(gdc);
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

void lore_notes::write(gdc_file *gdc) {
  block b;

  gdc->write_block_start(&b, 12);
  gdc->write_int(1); // version

  names.write(gdc);

  gdc->write_block_end(&b);
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

void faction_pack::write(gdc_file *gdc) {
  block b;

  gdc->write_block_start(&b, 13);
  gdc->write_int(5); // version

  gdc->write_int(faction);
  factions.write(gdc);

  gdc->write_block_end(&b);
}

void faction_data::read(gdc_file *gdc) {
  modified = gdc->read_byte();
  unlocked = gdc->read_byte();
  value = gdc->read_float();
  positiveBoost = gdc->read_float();
  negativeBoost = gdc->read_float();
}

void faction_data::write(gdc_file *gdc) {
  gdc->write_byte(modified);
  gdc->write_byte(unlocked);
  gdc->write_float(value);
  gdc->write_float(positiveBoost);
  gdc->write_float(negativeBoost);
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

void ui_settings::write(gdc_file *gdc) {
  block b;

  gdc->write_block_start(&b, 14);
  gdc->write_int(4); // version

  gdc->write_byte(unknown1);
  gdc->write_int(unknown2);
  gdc->write_byte(unknown3);

  for (unsigned i = 0; i < 5; i++) {
    unknown4[i].write(gdc);
    unknown5[i].write(gdc);
    gdc->write_byte(unknown6[i]);
  }

  for (unsigned i = 0; i < 36; i++) {
    slots[i].write(gdc);
  }

  gdc->write_float(cameraDistance);

  gdc->write_block_end(&b);
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

void hot_slot::write(gdc_file *gdc) {
  gdc->write_int(type);

  if (type == 0) {
    skill.write(gdc);
    gdc->write_byte(isItemSkill);
    item.write(gdc);
    gdc->write_int(equipLocation);
  } else if (type == 4) {
    item.write(gdc);
    bitmapUp.write(gdc);
    bitmapDown.write(gdc);
    label.write(gdc);
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

void tutorial_pages::write(gdc_file *gdc) {
  block b;

  gdc->write_block_start(&b, 15);
  gdc->write_int(1); // version

  uint32_t n = pages.size();
  gdc->write_int(n);

  for (uint32_t i = 0; i < n; i++) {
    gdc->write_int(pages[i]);
  }

  gdc->write_block_end(&b);
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

void play_stats::write(gdc_file *gdc) {
  block b;

  gdc->write_block_start(&b, 16);
  gdc->write_int(9); // version

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

  gdc->write_int(survivalWaveTier);
  gdc->write_int(greatestSurvivalScore);
  gdc->write_int(cooldownRemaining);
  gdc->write_int(cooldownTotal);

  gdc->write_int(unknown1);
  gdc->write_int(unknown2);

  gdc->write_block_end(&b);
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

void trigger_tokens::write(gdc_file *gdc) {
  block b;

  gdc->write_block_start(&b, 10);
  gdc->write_int(2); // version

  for (unsigned i = 0; i < 3; i++) {
    tokens[i].write(gdc);
  }

  gdc->write_block_end(&b);
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

void item::write(gdc_file *gdc) {
  baseName.write(gdc);
  prefixName.write(gdc);
  suffixName.write(gdc);
  modifierName.write(gdc);
  transmuteName.write(gdc);
  gdc->write_int(seed);
  relicName.write(gdc);
  relicBonus.write(gdc);
  gdc->write_int(relicSeed);
  augmentName.write(gdc);
  gdc->write_int(unknown);
  gdc->write_int(augmentSeed);
  gdc->write_int(var1);
  gdc->write_int(stackCount);
}

void uid::read(gdc_file *gdc) {
  for (unsigned i = 0; i < 16; i++) {
    id[i] = gdc->read_byte();
  }
}

void uid::write(gdc_file *gdc) {
  for (unsigned i = 0; i < 16; i++) {
    gdc->write_byte(id[i]);
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

void string::write(gdc_file *gdc) {
  uint32_t len = size();
  const char *str = data();

  gdc->write_int(len);

  for (uint32_t i = 0; i < len; i++) {
    gdc->write_byte(str[i]);
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

void wstring::write(gdc_file *gdc) {
  uint32_t len = size();
  const wchar_t *str = data();

  gdc->write_int(len);

  for (uint32_t i = 0; i < len; i++) {
    gdc->write_byte(str[i]);
    gdc->write_byte(str[i] >> 8);
  }
}

int main(int argc, char **argv) {
  if (argc != 3) {
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

  try {
    gdc.write(argv[2]);
  } catch (const std::runtime_error &e) {
    std::cout << "Exception:" << e.what() << std::endl;
  } catch (const std::exception &e) {
    printf("Error writing file: %s\n", argv[2]);
    return 1;
  }

  return 0;
}
