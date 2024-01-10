#include <iostream>
#include <folly/json.h>
#include <folly/dynamic.h>
#include "FileReader.h"

int main() {
	
	std::string jsonDocument = R"({"key":12,"key2":[false, null, true, "yay"]})";
	folly::dynamic parsedJson = folly::parseJson(jsonDocument);

	std::cout << parsedJson["key"] << std::endl;

	for (auto& elements : parsedJson["key2"]) {
		std::cout << elements << std::endl;
	}

	return 0;
}