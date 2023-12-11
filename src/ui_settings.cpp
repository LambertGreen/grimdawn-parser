#include "ui_settings.hpp"

#include "block_field.hpp"
#include "format.hpp"
#include "validation.hpp"

namespace {
const int BLOCK = 14;
const int VERSION = 5;
}  // namespace

void ui_settings::read(gdc_file* gdc) {
  block_field b;
  ENSURE(gdc->read_block_start(&b) == BLOCK,
         "ui_settings: Unexpected block number");
  ENSURE(gdc->read_int() == VERSION, "ui_settings: Unexpected version number");

  unknown1 = gdc->read_byte();
  unknown2 = gdc->read_int();
  unknown3 = gdc->read_byte();

  for (unsigned i = 0; i < 5; i++) {
    unknown4[i].read(gdc);
    unknown5[i].read(gdc);
    unknown6[i] = gdc->read_byte();
  }
}
json ui_settings::get_json() const {
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
    m.emplace("hot_slot_" + formatNumber(i), slots[i].get_json());
  }
  j.emplace("hot_slots", m);

  return j;
};
