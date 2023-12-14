#include "player.hpp"
#include "gdc_file.hpp"

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

void player::write(const char* filename) {
  gdc_file_writer gdc_out(filename);

  gdc_out.write_int(0x55555555);
  gdc_out.write_int(0x58434447);
  gdc_out.write_int(1);

  hdr.write(&gdc_out);

  gdc_out.write_int(0);

  gdc_out.write_int(7);  // version
  id.write(&gdc_out);

  info.write(&gdc_out);
  bio.write(&gdc_out);
  inv.write(&gdc_out);
  stash.write(&gdc_out);
  respawns.write(&gdc_out);
  teleports.write(&gdc_out);
  markers.write(&gdc_out);
  shrines.write(&gdc_out);
  skills.write(&gdc_out);
  notes.write(&gdc_out);
  factions.write(&gdc_out);
  ui.write(&gdc_out);
  tutorials.write(&gdc_out);
  stats.write(&gdc_out);
  tokens.write(&gdc_out);
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
