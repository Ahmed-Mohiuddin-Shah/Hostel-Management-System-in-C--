#include <iostream>
#include <folly/json.h>
#include <folly/dynamic.h>
#include <fstream>

int main() {
	
	std::string jsonDocument = R"({"key":12,"key2":[false, null, true, "yay"]})";
	folly::dynamic parsedJson = folly::parseJson(jsonDocument);

	std::cout << parsedJson["key"] << std::endl;

	for (auto& elements : parsedJson["key2"]) {
		std::cout << elements << std::endl;
	}

	// fstream is Stream class to both 
   // read and write from/to files. 
   // file is object of fstream class 
	std::fstream file;

	// opening file "Gfg.txt" 
	// in out(write) mode 
	// ios::out Open for output operations. 
	file.open("Gfg.txt", std::ios::out);

	// If no file is created, then 
	// show the error message. 
	if (!file)
	{
		std::cout << "Error in creating file!!!";
		return 0;
	}

	std::cout << "File created successfully.";

	// closing the file. 
	// The reason you need to call close() 
	// at the end of the loop is that trying 
	// to open a new file without closing the 
	// first file will fail. 
	file.close();

	return 0;
}