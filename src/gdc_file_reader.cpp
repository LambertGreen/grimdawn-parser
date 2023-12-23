#include "gdc_file_reader.hpp"

#include "block_field.hpp"

#include <cstdint>
#include <stdexcept>
#include <string>

gdc_file_reader::gdc_file_reader(const char* filename)
    : gdc_file(filename, "rb") {
  if (!(_fp = _f.fp)) {
    throw std::runtime_error("gdc_file:read: failed!");
  }

  if (fseek(_fp, 0, SEEK_END)) {
    throw std::runtime_error("gdc_file:read: failed fseek!");
  }

  _end = ftell(_fp);

  if (fseek(_fp, 0, SEEK_SET)) {
    throw std::runtime_error("gdc_file:read: failed fseek!");
  }
}

void gdc_file_reader::read_start() {
  read_key();
  build_table();
  const auto v = read_int();
  if (v != VERSION) {
    throw std::runtime_error("gdc_file:read: unexpected int value of " +
                             std::to_string(v));
  }
}

void gdc_file_reader::read_version() {
  const auto v2 = next_int();
  if (v2 != VERSION_0) {
    throw std::runtime_error("gdc_file:read: unexpected int is values of " +
                             std::to_string(v2));
  }

  const auto v3 = read_int();
  if (v3 != VERSION_8) {
    throw std::runtime_error("gdc_file:read: unexpected int value of " +
                             std::to_string(v3));
  }
}

void gdc_file_reader::read_end() {
  if (ftell(_fp) != _end)
    throw std::runtime_error("gdc_file_reader: unexpected end of file.");
}

void gdc_file_reader::read_key() {
  uint32_t k;

  if (fread(&k, 4, 1, _fp) != 1) {
    throw std::runtime_error(
        "gdc_file_reader::read_key: failed to read uint32");
  }

  k ^= XOR_BITMAP;
  _key = k;
}

uint32_t gdc_file_reader::next_int() {
  uint32_t ret;

  if (fread(&ret, 4, 1, _fp) != 1) {
    throw std::runtime_error("next_int: failed to read uint32");
  }

  ret ^= _key;

  return ret;
}

void gdc_file_reader::update_key(void* ptr, uint32_t len) {
  uint8_t* p = (uint8_t*)ptr;

  for (uint32_t i = 0; i < len; i++) {
    int j = p[i];
    if (j < 0) {
      j += 256;
    }
    _key ^= _table[j];
  }
}

uint32_t gdc_file_reader::read_int() {
  uint32_t val;

  if (fread(&val, 4, 1, _fp) != 1) {
    throw std::runtime_error("read_int: failed to read uint32");
  }

  uint32_t ret = val ^ _key;

  update_key(&val, 4);

  return ret;
}

uint16_t gdc_file_reader::read_short() {
  uint16_t val;

  if (fread(&val, 2, 1, _fp) != 1) {
    throw std::runtime_error("read_short: failed to read uint16");
  }

  uint16_t ret = val ^ _key;

  update_key(&val, 2);

  return ret;
}

uint8_t gdc_file_reader::read_byte() {
  uint8_t val;

  if (fread(&val, 1, 1, _fp) != 1) {
    throw std::runtime_error("read_byte: failed to read uint8");
  }

  uint8_t ret = val ^ _key;

  update_key(&val, 1);

  return ret;
}

float gdc_file_reader::read_float() {
  union {
    float f;
    int i;
  } u;
  u.i = read_int();
  return u.f;
}

uint32_t gdc_file_reader::read_block_start(block_field& b) {
  uint32_t ret = read_int();

  b.len = next_int();
  b.end = ftell(_fp) + b.len;

  return ret;
}

void gdc_file_reader::read_block_end(block_field& b) {
  if (ftell(_fp) != b.end) {
    throw std::runtime_error("read_block_end: ftell failed!");
  }

  if (next_int()) {
    throw std::runtime_error("read_block_end: next_int failed!");
  }
}
