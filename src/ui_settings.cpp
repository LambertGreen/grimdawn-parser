#include "ui_settings.hpp"

#include "block.hpp"
#include "format.hpp"
#include "validation.hpp"

void ui_settings::read(gdc_file_reader* gdc) {
  block b;
  b.read_start(gdc);
  ENSURE(b.num == BLOCK_14, "ui_settings: Unexpected block number");
  ENSURE(b.version == VERSION_5, "ui_settings: Unexpected version number");

  unknown1 = gdc->read_byte();
  unknown2 = gdc->read_int();
  unknown3 = gdc->read_byte();

  for (unsigned i = 0; i < 5; i++) {
    unknown4[i].read(gdc);
    unknown5[i].read(gdc);
    unknown6[i] = gdc->read_byte();
  }

  for (unsigned i = 0; i < 46; i++) {
    slots[i].read(gdc);
  }

  cameraDistance = gdc->read_float();

  b.read_end(gdc);
}

void ui_settings::write(gdc_file_writer* gdc) const {
  block b;
  b.write_start(gdc, BLOCK_14, VERSION_5);

  gdc->write_byte(unknown1);
  gdc->write_int(unknown2);
  gdc->write_byte(unknown3);

  for (unsigned i = 0; i < 5; i++) {
    unknown4[i].write(gdc);
    unknown5[i].write(gdc);
    gdc->write_byte(unknown6[i]);
  }

  for (unsigned i = 0; i < 46; i++) {
    slots[i].write(gdc);
  }

  gdc->write_float(cameraDistance);

  b.write_end(gdc);
}

json ui_settings::to_json() const {
  json j;
  ADD_TO_JSON(j, unknown1);
  ADD_TO_JSON(j, unknown2);
  ADD_TO_JSON(j, unknown3);
  ADD_TO_JSON(j, unknown4);
  ADD_TO_JSON(j, unknown5);
  ADD_TO_JSON(j, unknown6);
  ADD_TO_JSON(j, cameraDistance);

  json m;
  ADD_TO_JSON(j, unknown1);
  for (int i = 0; i < sizeof(slots) / sizeof(slots[0]); i++) {
    m.emplace("hot_slot_" + formatNumber(i), slots[i].to_json());
  }
  j.emplace("hot_slots", m);

  return j;
};
