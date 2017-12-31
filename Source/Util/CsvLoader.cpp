#include "CsvLoader.h"

void CsvLoader::LoadFromFile(std::string filename, const size_t value_count, std::function<void(std::vector<std::string>)> func) {
	std::ifstream inFile(filename);

	// check open-ness
	if(!inFile.is_open()) {
		throw std::runtime_error("Unable to open file: " + filename + "!");
	}

	// read every line and get values
	std::string line;
	while(std::getline(inFile, line)) {
		std::string val;
		std::stringstream ss(line);
		std::vector<std::string> values;

		// take the line appart
		while(std::getline(ss, val, ';')) {
			values.push_back(val);
		}

        size_t vc = values.size();

		if(values.size() != value_count) {
			throw std::runtime_error("Number of values doesn't match!");
		}

		// execute lambda on line
		func(values);
	}
}
