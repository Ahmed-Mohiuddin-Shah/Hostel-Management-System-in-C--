#pragma once
#include <iostream>
#include <cstdio>
#include <fstream>

class FileReader {

public:

	static bool checkIfFileExists(std::string fileName);

	static bool createFile(std::string fileName);

	static void deleteFile(std::string fileName);

	static std::string readFromFile(std::string fileName);

	static void writeToFile(std::string fileName, std::string data);

};