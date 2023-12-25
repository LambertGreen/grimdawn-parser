#include "player.hpp"

player::player(const char* filename) : _gdc_reader(filename) {
  _gdc_reader.read_start();
  _hdr.read(_gdc_reader);
  _gdc_reader.read_version();
  _id.read(_gdc_reader);
  _info.read(_gdc_reader);
  _bio.read(_gdc_reader);
  _inv.read(_gdc_reader);
  _stash.read(_gdc_reader);
  _respawns.read(_gdc_reader);
  _teleports.read(_gdc_reader);
  _markers.read(_gdc_reader);
  _shrines.read(_gdc_reader);
  _skills.read(_gdc_reader);
  _notes.read(_gdc_reader);
  _factions.read(_gdc_reader);
  _ui.read(_gdc_reader);
  _tutorials.read(_gdc_reader);
  _stats.read(_gdc_reader);
  _tokens.read(_gdc_reader);
  _gdc_reader.read_end();
}

void player::write(const char* filename) {
  gdc_file_writer gdc_writer(filename);

  gdc_writer.write_start();
  _hdr.write(gdc_writer);
  gdc_writer.write_version();
  _id.write(gdc_writer);
  _info.write(gdc_writer);
  _bio.write(gdc_writer);
  _inv.write(gdc_writer);
  _stash.write(gdc_writer);
  _respawns.write(gdc_writer);
  _teleports.write(gdc_writer);
  _markers.write(gdc_writer);
  _shrines.write(gdc_writer);
  _skills.write(gdc_writer);
  _notes.write(gdc_writer);
  _factions.write(gdc_writer);
  _ui.write(gdc_writer);
  _tutorials.write(gdc_writer);
  _stats.write(gdc_writer);
  _tokens.write(gdc_writer);
}

json player::to_json() const {
  // -------------------------------------------------------------------------
  // clang-format off
  return json{
      {"header", _hdr.to_json()},
      {"id", _id.to_json()},
      {"info", _info.to_json()},
      {"bio", _bio.to_json()},
      {"inventory", _inv.to_json()},
      {"stash", _stash.to_json()},
      {"respawns", _respawns.to_json()},
      {"teleports", _teleports.to_json()},
      {"markers", _markers.to_json()},
      {"shrines", _shrines.to_json()},
      {"skills", _skills.to_json()},
      {"notes", _notes.to_json()},
      {"factions", _factions.to_json()},
      {"ui", _ui.to_json()},
      {"tutorials", _tutorials.to_json()},
      {"stats", _stats.to_json()},
      {"tokens", _tokens.to_json()}
    };
  // clang-format on
  // -------------------------------------------------------------------------
}
