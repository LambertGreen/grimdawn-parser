#include "item.hpp"

void item::read(gdc_file_reader* gdc) {
  baseName.read(gdc);
  prefixName.read(gdc);
  suffixName.read(gdc);
  modifierName.read(gdc);
  transmuteName.read(gdc);
  seed = gdc->read_int();
  relicName.read(gdc);
  relicBonus.read(gdc);
  relicSeed = gdc->read_int();
  augmentName.read(gdc);
  unknown = gdc->read_int();
  augmentSeed = gdc->read_int();
  var1 = gdc->read_int();
  stackCount = gdc->read_int();
}

void item::write(gdc_file_writer* gdc) const {
  baseName.write(gdc);
  prefixName.write(gdc);
  suffixName.write(gdc);
  modifierName.write(gdc);
  transmuteName.write(gdc);
  gdc->write_int(seed);
  relicName.write(gdc);
  relicBonus.write(gdc);
  gdc->write_int(relicSeed);
  augmentName.write(gdc);
  gdc->write_int(unknown);
  gdc->write_int(augmentSeed);
  gdc->write_int(var1);
  gdc->write_int(stackCount);
}

json item::to_json() const {
  json j;
  ADD_TO_JSON(j, baseName);
  ADD_TO_JSON(j, prefixName);
  ADD_TO_JSON(j, suffixName);
  ADD_TO_JSON(j, modifierName);
  ADD_TO_JSON(j, transmuteName);
  ADD_TO_JSON(j, relicName);
  ADD_TO_JSON(j, relicBonus);
  ADD_TO_JSON(j, augmentName);
  ADD_TO_JSON(j, stackCount);
  ADD_TO_JSON(j, seed);
  ADD_TO_JSON(j, relicSeed);
  ADD_TO_JSON(j, unknown);
  ADD_TO_JSON(j, augmentSeed);
  ADD_TO_JSON(j, var1);

  return j;
};
