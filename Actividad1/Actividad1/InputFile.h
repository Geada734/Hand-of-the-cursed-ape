#pragma once

#pragma once
#include <string>

class InputFile {
private:
	std::string _contents;

public:
	bool read(std::string _fileName);
	std::string getContents();
};