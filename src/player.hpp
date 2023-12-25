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
  gdc_file_reader _gdc_reader;

  header _hdr{};
  uid _id{};
  character_info _info{};
  character_bio _bio{};
  inventory _inv{};
  character_stash _stash{};
  respawn_list _respawns{};
  teleport_list _teleports{};
  marker_list _markers{};
  shrine_list _shrines{};
  character_skills _skills{};
  lore_notes _notes{};
  faction_pack _factions{};
  ui_settings _ui{};
  tutorial_pages _tutorials{};
  play_stats _stats{};
  trigger_tokens _tokens{};
};
