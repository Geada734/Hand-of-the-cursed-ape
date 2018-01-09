
#include "InputFile.h"
#include <sstream>
#include <fstream>
#include <iostream>

bool InputFile::read(std::string _fileName) {
	bool open = false;
	std::ifstream inputFile;
	inputFile.open(_fileName);
	std::string _line;
	InputFile::_contents = "";

	if (inputFile.is_open()) {
		open = true;

		while (getline(inputFile, _line)) {
			InputFile::_contents = _contents + _line;
			InputFile::_contents = _contents + "\n";
		}
		inputFile.close();
	}
	return open;
}

std::string InputFile::getContents() {
	return InputFile::_contents;
}