#include "player.hpp"

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
