#include "uid.hpp"

#include "gdc_file.hpp"
#include <string>

void uid::read(gdc_file *gdc) {
  for (unsigned i = 0; i < 16; i++) {
    id[i] = gdc->read_byte();
  }
}

json uid::get_json() const {
	std::string s = std::to_string(id[0]);
	for (int i = 1; i < sizeof(id) / sizeof(id[0]); i++) {
		s += "-" + std::to_string(i);
	}

	json j;
	j.emplace("uid", s);
	return j;
}
