#pragma once
#include <iostream>
#include <fstream>

class FileReader {

public:

	static bool checkIfFileExists(std::string fileName);

	static bool createFile(std::string fileName);

};