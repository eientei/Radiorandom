#include "fs.hpp"


bool util::fs::file_exists(std::string const& path) {
	return std::ifstream(path.c_str()) != NULL;
}

void util::fs::create_file(std::string const& path) {
	std::ofstream target(path.c_str());
	target.close();
}
