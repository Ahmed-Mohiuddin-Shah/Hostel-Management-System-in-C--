/*
#include "ProjectHeader.hpp"

int main() {
	std::string jsonFromText;
	folly::dynamic parsedJson;

	if (!FileReader::checkIfFileExists(ProjectInfo::fileName)) {

		std::cout << "File doesn't Exist\nCreating New File..." << std::endl;

		FileReader::writeToFile(ProjectInfo::fileName, ProjectInfo::DefaulHostelInfo);
	}

	std::cout << "Text File Contents:" << std::endl;

	jsonFromText = FileReader::readFromFile(ProjectInfo::fileName);

	try
	{
		parsedJson = folly::parseJson(jsonFromText);
	}
	catch (const std::exception e)
	{
		std::cout << e.what();
	}

	std::cout << "Hostel Name: " << parsedJson["hostel_name"] << std::endl;
	std::cout << "Hostel Email: " << parsedJson["hostel_email"] << std::endl;
	std::cout << "Hostel Phone Number: " << parsedJson["hostel_phone_number"] << std::endl;
	std::cout << "Hostel Address: " << parsedJson["hostel_address"] << std::endl;

	std::cout << std::endl << "students:" << std::endl;
	for (auto student : parsedJson["students"]) {
		std::cout << student << std::endl;
	}

	std::cout << std::endl << "staffs:" << std::endl;
	for (auto staff : parsedJson["staffs"]) {
		std::cout << staff << std::endl;
	}

	std::cout << std::endl << "rooms:" << std::endl;
	for (auto room : parsedJson["rooms"]) {
		std::cout << room << std::endl;
	}

	std::cout << std::endl << "invoices:" << std::endl;
	for (auto invoice : parsedJson["invoices"]) {
		std::cout << invoice << std::endl;
	}

	return 0;
}
*/