#pragma once

#include "common.hpp"

#include "character_bio.hpp"
#include "character_info.hpp"
#include "character_skill.hpp"
#include "character_stash.hpp"
#include "common.hpp"
#include "faction_data.hpp"
#include "faction_pack.hpp"
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

class player {

public:
  player(const char *filename);
  json get_json() const;

private:
  gdc_file gdc;

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
