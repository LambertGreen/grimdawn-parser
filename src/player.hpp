#pragma once

#include "character_bio.hpp"
#include "character_info.hpp"
#include "character_skill.hpp"
#include "character_stash.hpp"
#include "faction_pack.hpp"
#include "header.hpp"
#include "inventory.hpp"
#include "lore_notes.hpp"
#include "marker_list.hpp"
#include "play_stats.hpp"
#include "respawn_list.hpp"
#include "shrine_list.hpp"
#include "teleport_list.hpp"
#include "trigger_tokens.hpp"
#include "tutorial_pages.hpp"
#include "ui_settings.hpp"
#include "uid.hpp"

class player {
 public:
  player(const char* filename);
  void write(const char* filename);
  json to_json() const;

 private:
  gdc_file_reader gdc;

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
};
