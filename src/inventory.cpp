#include "inventory.hpp"

#include "block.hpp"
#include "gdc_file.hpp"

void inventory::read(gdc_file* gdc) {
  const int BLOCK = 3;
  const int VERSION = 4;

  block b;
  b.read_start(gdc);
  ENSURE(b.num == BLOCK, "Unexpected block number");
  ENSURE(b.version == VERSION, "Unexpected version number");

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

json inventory::get_json() const {
  json j;
  ADD_TO_JSON(j, focused);
  ADD_TO_JSON(j, selected);
  ADD_TO_JSON(j, flag);
  ADD_TO_JSON(j, useAlternate);
  ADD_TO_JSON(j, alternate1);
  ADD_TO_JSON(j, alternate2);

  for (int i = 0; i < 12; i++) {
    j.emplace("equipment_" + std::to_string(i), equipment[i].get_json());
  }

  for (int i = 0; i < 2; i++) {
    j.emplace("weapon1_" + std::to_string(i), weapon1[i].get_json());
  }

  for (int i = 0; i < 2; i++) {
    j.emplace("weapon2_" + std::to_string(i), weapon2[i].get_json());
  }

  for (int i = 0; i < sacks.size(); i++) {
    json m;
    m.emplace("sack_" + std::to_string(i), sacks[i].get_json());
  }
  return j;
};
