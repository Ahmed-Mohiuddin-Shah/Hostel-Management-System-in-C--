#include <iostream>
#include <folly/json.h>
#include <folly/dynamic.h>
#include "FileReader.h"

int main() {
	std::string fileName = "HostelData.txt";
	std::string jsonDocument = R"({"key":12,"key2":[false, null, true, "yay"]})";

	FileReader::writeToFile(fileName, jsonDocument);

	std::string jsonFromText = FileReader::readFromFile(fileName);

	folly::dynamic parsedJson = folly::parseJson(jsonFromText);

	std::cout << parsedJson["key"] << std::endl;

	for (auto& elements : parsedJson["key2"]) {
		std::cout << elements << std::endl;
	}

	return 0;
}