#include "inventory.hpp"

#include "block.hpp"
#include "validation.hpp"

void inventory::read(gdc_file_reader* gdc) {
  block b;
  b.read_start(gdc);
  ENSURE(b.num == BLOCK_3, "inventory: Unexpected block number");
  ENSURE(b.version == VERSION_4, "inventory: Unexpected version number");

  if ((flag = gdc->read_byte())) {
    uint32_t n = gdc->read_int();
    focused = gdc->read_int();
    selected = gdc->read_int();

    sacks.resize(n);

    for (uint32_t i = 0; i < n; i++) {
      sacks[i].read(gdc);
    }

    useAlternate = gdc->read_byte();

    for (unsigned i = 0; i < 12; i++) {
      equipment[i].read(gdc);
    }

    alternate1 = gdc->read_byte();

    for (unsigned i = 0; i < 2; i++) {
      weapon1[i].read(gdc);
    }

    alternate2 = gdc->read_byte();

    for (unsigned i = 0; i < 2; i++) {
      weapon2[i].read(gdc);
    }
  }

  b.read_end(gdc);
}

void inventory::write(gdc_file_writer* gdc) const {
  block b;
  b.write_start(gdc, BLOCK_3, VERSION_4);

  gdc->write_byte(flag);

  if (flag) {
    uint32_t n = sacks.size();
    gdc->write_int(n);
    gdc->write_int(focused);
    gdc->write_int(selected);

    for (uint32_t i = 0; i < n; i++) {
      sacks[i].write(gdc);
    }

    gdc->write_byte(useAlternate);

    for (unsigned i = 0; i < 12; i++) {
      equipment[i].write(gdc);
    }

    gdc->write_byte(alternate1);

    for (unsigned i = 0; i < 2; i++) {
      weapon1[i].write(gdc);
    }

    gdc->write_byte(alternate2);

    for (unsigned i = 0; i < 2; i++) {
      weapon2[i].write(gdc);
    }
  }

  b.write_end(gdc);
}

json inventory::to_json() const {
  json j;
  ADD_TO_JSON(j, focused);
  ADD_TO_JSON(j, selected);
  ADD_TO_JSON(j, flag);
  ADD_TO_JSON(j, useAlternate);
  ADD_TO_JSON(j, alternate1);
  ADD_TO_JSON(j, alternate2);

  for (int i = 0; i < 12; i++) {
    j.emplace("equipment_" + std::to_string(i), equipment[i].to_json());
  }

  for (int i = 0; i < 2; i++) {
    j.emplace("weapon1_" + std::to_string(i), weapon1[i].to_json());
  }

  for (int i = 0; i < 2; i++) {
    j.emplace("weapon2_" + std::to_string(i), weapon2[i].to_json());
  }

  for (int i = 0; i < sacks.size(); i++) {
    json m;
    m.emplace("sack_" + std::to_string(i), sacks[i].to_json());
  }
  return j;
};
