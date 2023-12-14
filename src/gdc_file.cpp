#include "gdc_file.hpp"
#include "block_field.hpp"

#include <stdexcept>
#include <string>

static std::exception e;

namespace {
const int VERSION1 = 0x58434447;
const int VERSION2 = 0;
const int VERSION3 = 8;
const int NEXT_INT = 1;
const int XOR_BITMAP = 0x55555555;
}  // namespace

gdc_file_reader::gdc_file_reader(const char* filename) : f(filename, "rb") {
  if (!(this->fp = f.fp)) {
    throw std::runtime_error("gdc_file:read: failed!");
  }

  if (fseek(this->fp, 0, SEEK_END)) {
    throw std::runtime_error("gdc_file:read: failed fseek!");
  }

  end = ftell(this->fp);

  if (fseek(this->fp, 0, SEEK_SET)) {
    throw std::runtime_error("gdc_file:read: failed fseek!");
  }
}

void gdc_file_reader::read_start() {
  read_key();
  const auto v = read_int();
  if (v != VERSION1) {
    throw std::runtime_error("gdc_file:read: unexpected int value of " +
                             std::to_string(v));
  }
}

void gdc_file_reader::read_version() {
  const auto v2 = next_int();
  if (v2 != VERSION2) {
    throw std::runtime_error("gdc_file:read: unexpected int is values of " +
                             std::to_string(v2));
  }

  const auto v3 = read_int();
  if (v3 != VERSION3) {
    throw std::runtime_error("gdc_file:read: unexpected int value of " +
                             std::to_string(v3));
  }
}

void gdc_file_reader::read_end() {
  if (ftell(this->fp) != end)
    throw e;
}

void gdc_file_reader::read_key() {
  uint32_t k;

  if (fread(&k, 4, 1, this->fp) != 1) {
    throw std::runtime_error(
        "gdc_file_reader::read_key: failed to read uint32");
  }

  k ^= XOR_BITMAP;

  this->key = k;
  for (unsigned i = 0; i < 256; i++) {
    k = (k >> 1) | (k << 31);
    k *= 39916801;
    this->table[i] = k;
  }
}

uint32_t gdc_file_reader::next_int() {
  uint32_t ret;

  if (fread(&ret, 4, 1, fp) != NEXT_INT) {
    throw std::runtime_error("next_int: failed to read uint32");
  }

  ret ^= key;

  return ret;
}

void gdc_file_reader::update_key(void* ptr, uint32_t len) {
  uint8_t* p = (uint8_t*)ptr;

  for (uint32_t i = 0; i < len; i++) {
    this->key ^= table[p[i]];
  }
}

uint32_t gdc_file_reader::read_int() {
  uint32_t val;

  if (fread(&val, 4, 1, fp) != 1) {
    throw std::runtime_error("read_int: failed to read uint32");
  }

  uint32_t ret = val ^ key;

  update_key(&val, 4);

  return ret;
}

uint16_t gdc_file_reader::read_short() {
  uint16_t val;

  if (fread(&val, 2, 1, fp) != 1) {
    throw std::runtime_error("read_short: failed to read uint16");
  }

  uint16_t ret = val ^ key;

  update_key(&val, 2);

  return ret;
}

uint8_t gdc_file_reader::read_byte() {
  uint8_t val;

  if (fread(&val, 1, 1, fp) != 1) {
    throw std::runtime_error("read_byte: failed to read uint8");
  }

  uint8_t ret = val ^ key;

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

uint32_t gdc_file_reader::read_block_start(block_field* b) {
  uint32_t ret = read_int();

  b->len = next_int();
  b->end = ftell(fp) + b->len;

  return ret;
}

void gdc_file_reader::read_block_end(block_field* b) {
  if (ftell(fp) != b->end) {
    throw std::runtime_error("read_block_end: failed!");
  }

  if (next_int()) {
    throw std::runtime_error("read_block_end: failed!");
  }
}

gdc_file_writer::gdc_file_writer(const char* filename) : f(filename, "wb") {
  if (!(fp = f.fp))
    throw e;
}

void gdc_file_writer::write_start() {
  write_int(0x55555555);
  write_int(VERSION1);
  write_int(NEXT_INT);
}

void gdc_file_writer::write_version() {
  write_int(VERSION2);
  write_int(VERSION3);
}

void gdc_file_writer::write_end() {
  if (fflush(fp))
    throw e;
}

void gdc_file_writer::write_int(uint32_t val) {
  if (fwrite(&val, 4, 1, fp) != 1)
    throw e;
}

void gdc_file_writer::write_short(uint16_t val) {
  if (fwrite(&val, 2, 1, fp) != 1)
    throw e;
}

void gdc_file_writer::write_byte(uint8_t val) {
  if (fwrite(&val, 1, 1, fp) != 1)
    throw e;
}

void gdc_file_writer::write_float(float val) {
  if (fwrite(&val, 4, 1, fp) != 1)
    throw e;
}

void gdc_file_writer::write_block_start(block_field* b, uint32_t n) {
  write_int(n);
  write_int(0);
  b->end = ftell(fp);
}

void gdc_file_writer::write_block_end(block_field* b) {
  long pos = ftell(fp);

  if (fseek(fp, b->end - 4, SEEK_SET))
    throw e;

  write_int(pos - b->end);

  if (fseek(fp, pos, SEEK_SET))
    throw e;

  write_int(0);
}
