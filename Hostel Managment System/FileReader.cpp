#include "FileReader.h"

// ----------------------------------------------------------------
// As long as you have the static keyword in the header file,
//  the compiler knows it's a static class method, so you should
//  not and cannot specify it in the definition in the source file.
// ----------------------------------------------------------------

bool FileReader::checkIfFileExists(std::string fileName)
{
	return std::ifstream(fileName).good();
}

bool createFile(std::string fileName) { 
	std::fstream file;
	file.open(fileName, std::ios::out);
	if (!file)
	{
		std::cout << "Error in creating file!!!";
		throw "Failed To Create " + fileName;
	}
	std::cout << "File created successfully."; 
	file.close();
	return true;
}