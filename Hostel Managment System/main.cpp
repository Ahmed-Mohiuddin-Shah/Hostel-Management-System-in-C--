#include <iostream>
#include <folly/json.h>
#include <folly/dynamic.h>
#include "FileReader.h"

int main() {
	std::string fileName = "HostelData.txt";
	std::string jsonDocument = R"({"hostel_name":"Hostelo","hostel_email":"example@gmail.com","hostel_address":"Islamabad"})";
	std::string jsonFromText;
	folly::dynamic parsedJson;

	if (!FileReader::checkIfFileExists(fileName)) {

		std::cout << "File doesn't Exist\nCreating New File..." << std::endl;

		FileReader::writeToFile(fileName, jsonDocument);

		jsonFromText = FileReader::readFromFile(fileName);
		
		parsedJson = folly::parseJson(jsonFromText);
		
		folly::dynamic studentsArray = folly::dynamic::array;

		for (int i = 1; i <= 10; i++) {
			folly::dynamic studentData = folly::dynamic::object;
			studentData["s_id"] = i;
			studentData["s_name"] = "TestName";
			studentData["s_age"] = 18 + i;
			studentData["s_gender"] = i%2?"male":"female";
			studentsArray.push_back(studentData);
		}

		parsedJson["students"] = studentsArray;

		std::string jsonString = folly::toJson(parsedJson);
		std::cout << "File doesn't Exist" << std::endl;

		FileReader::writeToFile(fileName, jsonString);

	}

	std::cout << "Text File Contents:" << std::endl;

	jsonFromText = FileReader::readFromFile(fileName);

	parsedJson = folly::parseJson(jsonFromText);
	
	std::cout << parsedJson["hostel_name"] << std::endl;
	std::cout << parsedJson["hostel_email"] << std::endl;
	std::cout << parsedJson["hostel_address"] << std::endl;

	for (auto student : parsedJson["students"]) {
		std::cout << student << std::endl;
	}

	return 0;
}