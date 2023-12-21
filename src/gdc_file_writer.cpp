#include "gdc_file_writer.hpp"

#include "block_field.hpp"

#include <cstdint>
#include <stdexcept>

gdc_file_writer::gdc_file_writer(const char* filename)
    : gdc_file(filename, "wb") {
  if (!(fp = f.fp))
    throw std::runtime_error("gdc_file_writer: error occurred!");
}

void gdc_file_writer::write_start() {
  write_int(XOR_BITMAP);
  write_int(VERSION);
  write_int(1);
}

void gdc_file_writer::write_version() {
  write_int(VERSION_0);
  write_int(VERSION_8);
}

void gdc_file_writer::write_end() {
  if (fflush(fp))
    throw std::runtime_error("gdc_file_writer: error occurred!");
}

void gdc_file_writer::write_int(uint32_t val) {
  if (fwrite(&val, 4, 1, fp) != 1)
    throw std::runtime_error("gdc_file_writer: error occurred!");
}

void gdc_file_writer::write_short(uint16_t val) {
  if (fwrite(&val, 2, 1, fp) != 1)
    throw std::runtime_error("gdc_file_writer: error occurred!");
}

void gdc_file_writer::write_byte(uint8_t val) {
  if (fwrite(&val, 1, 1, fp) != 1)
    throw std::runtime_error("gdc_file_writer: error occurred!");
}

void gdc_file_writer::write_float(float val) {
  if (fwrite(&val, 4, 1, fp) != 1)
    throw std::runtime_error("gdc_file_writer: error occurred!");
}

void gdc_file_writer::write_block_start(block_field* b, uint32_t n) {
  write_int(n);
  write_int(0);
  b->end = ftell(fp);
}

void gdc_file_writer::write_block_end(block_field* b) {
  long pos = ftell(fp);

  if (fseek(fp, b->end - 4, SEEK_SET))
    throw std::runtime_error("gdc_file_writer: error occurred!");

  write_int(pos - b->end);

  if (fseek(fp, pos, SEEK_SET))
    throw std::runtime_error("gdc_file_writer: error occurred!");

  write_int(0);
}
