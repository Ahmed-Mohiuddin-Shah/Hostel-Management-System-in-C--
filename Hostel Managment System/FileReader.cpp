#include "FileReader.h"
#include <string>
#include <iostream>
#include <cstdio>
#include <stdexcept>

// ----------------------------------------------------------------
// As long as you have the static keyword in the header file,
//  the compiler knows it's a static class method, so you should
//  not and cannot specify it in the definition in the source file.
// ----------------------------------------------------------------

bool FileReader::checkIfFileExists(std::string fileName)
{
	return std::ifstream(fileName).good();
}

bool FileReader::createFile(std::string fileName) {
	std::fstream file;
	file.open(fileName, std::ios::out);
	if (!file)
	{
		throw std::runtime_error("Failed To Create " + fileName);
		return false;
	}
	file.close();
	return true;
}

void FileReader::deleteFile(std::string fileName) {
	std::remove(fileName.c_str());
}

std::string FileReader::readFromFile(std::string fileName) {
	std::fstream file;
	file.open(fileName, std::ios::in);
	if (!file)
	{
		throw std::runtime_error("Failed To Open " + fileName);
	}

	std::string data = "";
	std::string tempData;
	
	while (!file.eof()) {
		std::getline(file, tempData);
		data.append(tempData);
	}

	file.close();
	return data;
}

void FileReader::writeToFile(std::string fileName, std::string data) {
	std::ofstream file;
	file.open(fileName, std::ofstream::out | std::ofstream::trunc);
	if (!file)
	{
		throw std::runtime_error("Failed To Open " + fileName);
	}
	
	file << data << std::endl;

	file.close();
}