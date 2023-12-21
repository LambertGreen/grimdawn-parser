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
  gdc_file_writer gdc(filename);

  gdc.write_start();
  hdr.write(gdc);

  gdc.write_int(0);
  gdc.write_int(7);  // version

  id.write(gdc);
  info.write(gdc);
  bio.write(gdc);
  inv.write(gdc);
  stash.write(gdc);
  respawns.write(gdc);
  teleports.write(gdc);
  markers.write(gdc);
  shrines.write(gdc);
  skills.write(gdc);
  notes.write(gdc);
  factions.write(gdc);
  ui.write(gdc);
  tutorials.write(gdc);
  stats.write(gdc);
  tokens.write(gdc);
}

json player::to_json() const {
  return json{{"id", id.to_json()},
              {"info", info.to_json()},
              {"bio", bio.to_json()},
              {"inventory", inv.to_json()},
              {"stash", stash.to_json()},
              {"respawns", respawns.to_json()},
              {"teleports", teleports.to_json()},
              {"markers", markers.to_json()},
              {"shrines", shrines.to_json()},
              {"skills", skills.to_json()},
              {"notes", notes.to_json()},
              {"factions", factions.to_json()},
              {"ui", ui.to_json()},
              {"tutorials", tutorials.to_json()},
              {"stats", stats.to_json()},
              {"tokens", tokens.to_json()}};
}
