#include "gdc_file_writer.hpp"

#include "block_field.hpp"

#include <cstdint>
#include <stdexcept>

gdc_file_writer::gdc_file_writer(const char* filename)
    : gdc_file(filename, "wb") {
  if (!(_fp = _f.fp)) {
    throw std::runtime_error("gdc_file_writer: error occurred!");
  }
}

void gdc_file_writer::write_start() {
  write_key(0x1fdbf1d3);
  build_table();
  write_int(VERSION);
  write_int(1);
}

void gdc_file_writer::write_version() {
  write_int(VERSION_0);
  write_int(VERSION_8);
}

void gdc_file_writer::write_key(uint32_t key) {
  _key = key;
  uint32_t k = key ^ XOR_BITMAP;

  if (fwrite(&k, 4, 1, _fp) != 1) {
    throw std::runtime_error("gdc_file_writer: error occurred!");
  }
}

void gdc_file_writer::update_key(void* ptr, uint32_t len) {
  uint8_t* p = (uint8_t*)ptr;

  for (uint32_t i = 0; i < len; i++) {
    int j = p[i];
    if (j < 0) {
      j += 256;
    }
    _key ^= _table[j];
  }
}

void gdc_file_writer::write_end() {
  if (fflush(_fp)) {
    throw std::runtime_error("gdc_file_writer: error occurred!");
  }
}

void gdc_file_writer::write_int(uint32_t val) {
  uint32_t encVal = val ^ _key;

  if (fwrite(&val, 4, 1, _fp) != 1) {
    throw std::runtime_error("gdc_file_writer: error occurred!");
  }

  // update_key(&val, 4);
}

void gdc_file_writer::write_short(uint16_t val) {
  uint16_t encVal = val ^ _key;

  if (fwrite(&encVal, 2, 1, _fp) != 1) {
    throw std::runtime_error("gdc_file_writer: error occurred!");
  }

  update_key(&val, 2);
}

void gdc_file_writer::write_byte(uint8_t val) {
  uint8_t encVal = val ^ _key;

  if (fwrite(&encVal, 1, 1, _fp) != 1) {
    throw std::runtime_error("gdc_file_writer: error occurred!");
  }

  update_key(&val, 1);
}

void gdc_file_writer::write_float(float val) {
  union {
    float f;
    int i;
  } u;
  u.f = val;
  write_int(u.i);
}

void gdc_file_writer::write_block_start(block_field& b, uint32_t n) {
  write_int(n);
  write_int(0);
  b.end = ftell(_fp);
}

void gdc_file_writer::write_block_end(const block_field& b) {
  long pos = ftell(_fp);

  if (fseek(_fp, b.end - 4, SEEK_SET)) {
    throw std::runtime_error("gdc_file_writer: error occurred!");
  }

  write_int(pos - b.end);

  if (fseek(_fp, pos, SEEK_SET)) {
    throw std::runtime_error("gdc_file_writer: error occurred!");
  }

  write_int(0);
}
