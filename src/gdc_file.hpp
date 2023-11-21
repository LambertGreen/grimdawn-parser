#pragma once

#include "block.hpp"
#include "character_bio.hpp"
#include "character_info.hpp"
#include "character_skill.hpp"
#include "character_stash.hpp"
#include "common.hpp"
#include "faction_data.hpp"
#include "faction_pack.hpp"
#include "file.hpp"
#include "header.hpp"
#include "hot_slot.hpp"
#include "inventory.hpp"
#include "inventory_equipment.hpp"
#include "inventory_item.hpp"
#include "inventory_sack.hpp"
#include "item.hpp"
#include "item_skill.hpp"
#include "lore_notes.hpp"
#include "marker_list.hpp"
#include "play_stats.hpp"
#include "respawn_list.hpp"
#include "shrine_list.hpp"
#include "skill.hpp"
#include "stash_item.hpp"
#include "stash_page.hpp"
#include "teleport_list.hpp"
#include "trigger_tokens.hpp"
#include "tutorial_pages.hpp"
#include "ui_settings.hpp"
#include "uid.hpp"
#include "vector.hpp"

class gdc_file {
private:
  FILE *fp;
  uint32_t key;
  uint32_t table[256];

public:
  header hdr{};
  uid id{};
  character_info info{};
  character_bio bio{};
  inventory inv{};
  character_stash stash{};
  respawn_list respawns{};
  teleport_list teleports{};
  marker_list markers{};
  shrine_list shrines{};
  character_skills skills{};
  lore_notes notes{};
  faction_pack factions{};
  ui_settings ui{};
  tutorial_pages tutorials{};
  play_stats stats{};
  trigger_tokens tokens{};

  void read(const char *);
  json get_json() const;

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

  uint32_t read_block_start(block_field *b) {
    uint32_t ret = read_int();

    b->len = next_int();
    b->end = ftell(fp) + b->len;

    return ret;
  }

  void read_block_end(block_field *b) {
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

  void write_block_start(block_field *b, uint32_t n) {
    write_int(n);
    write_int(0);
    b->end = ftell(fp);
  }

  void write_block_end(block_field *b) {
    long pos = ftell(fp);

    if (fseek(fp, b->end - 4, SEEK_SET))
      throw e;

    write_int(pos - b->end);

    if (fseek(fp, pos, SEEK_SET))
      throw e;

    write_int(0);
  }
};
