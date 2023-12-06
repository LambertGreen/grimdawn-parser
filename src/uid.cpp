#include "uid.hpp"

#include <string>

json uid::get_json() const {
	std::string s = std::to_string(id[0]);
	for (int i = 1; i < sizeof(id) / sizeof(id[0]); i++) {
		s += "-" + std::to_string(i);
	}

	json j;
	j.emplace("uid", s);
	return j;
}
