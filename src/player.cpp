#include "player.hpp"

player::player(const char* filename) : gdc(filename) {
  gdc.read_start();
  hdr.read(gdc);
  gdc.read_version();
  id.read(gdc);
  info.read(gdc);
  bio.read(gdc);
  inv.read(gdc);
  stash.read(gdc);
  respawns.read(gdc);
  teleports.read(gdc);
  markers.read(gdc);
  shrines.read(gdc);
  skills.read(gdc);
  notes.read(gdc);
  factions.read(gdc);
  ui.read(gdc);
  tutorials.read(gdc);
  stats.read(gdc);
  tokens.read(gdc);
  gdc.read_end();
}

void player::write(const char* filename) {
  gdc_file_writer gdc_out(filename);

  gdc_out.write_start();
  hdr.write(gdc_out);

  gdc_out.write_int(0);
  gdc_out.write_int(7);  // version

  id.write(gdc_out);
  info.write(gdc_out);
  bio.write(gdc_out);
  inv.write(gdc_out);
  stash.write(gdc_out);
  respawns.write(gdc_out);
  teleports.write(gdc_out);
  markers.write(gdc_out);
  shrines.write(gdc_out);
  skills.write(gdc_out);
  notes.write(gdc_out);
  factions.write(gdc_out);
  ui.write(gdc_out);
  tutorials.write(gdc_out);
  stats.write(gdc_out);
  tokens.write(gdc_out);
}

json player::to_json() const {
  json j;
  j.emplace("id", id.to_json());
  j.emplace("info", info.to_json());
  j.emplace("bio", bio.to_json());
  j.emplace("inventory", inv.to_json());
  j.emplace("stash", stash.to_json());
  j.emplace("respawns", respawns.to_json());
  j.emplace("teleports", teleports.to_json());
  j.emplace("markers", markers.to_json());
  j.emplace("shrines", shrines.to_json());
  j.emplace("skills", skills.to_json());
  j.emplace("notes", notes.to_json());
  j.emplace("factions", factions.to_json());
  j.emplace("ui", ui.to_json());
  j.emplace("tutorials", tutorials.to_json());
  j.emplace("stats", stats.to_json());
  j.emplace("tokens", tokens.to_json());
  return j;
}
