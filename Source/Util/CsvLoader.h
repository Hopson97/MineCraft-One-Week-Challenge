#ifndef CSVLOADER_H
#define CSVLOADER_H

#include <vector>
#include <functional>
#include <fstream>
#include <sstream>

class CsvLoader {
public:
	//template<typename T>
	static void LoadFromFile(std::string filename, const size_t value_count, std::function<void(std::vector<std::string>)> func);
};
#endif // !CSVLOADER_H
