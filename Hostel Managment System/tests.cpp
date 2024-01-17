
// File reader test
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


// Basic Hostel system test

/*
#include "ProjectHeader.hpp"

// ----------- global variables -----------
Hostel hostel;
#define MAX_BUFFER_SIZE 150

static void waitForEnteringKey()
{
	std::cout << "Press enter to continue...";
	std::cin.ignore();
	std::cin.get();
}

// ----------- function prototypes -----------
void initializeHostel();
void displayMenu();
void studentRegistration();
void roomCreation();
void staffCreation();
void generateInvoice();
void updateInvoiceStatus();

int main()
{
	initializeHostel();
	displayMenu();
	return 0;
}

// ----------- function definitions -----------

// ----------- initializeHostel -----------
void initializeHostel()
{
	std::cout << "System Start Up" << std::endl;
	std::cout << "Enter details of Hostel: " << std::endl;

	std::cout << "Enter Hostel Name: ";
	std::string hostelName;
	getline(std::cin, hostelName);

	std::cout << "Enter Hostel Address: ";
	std::string hostelAddress;
	getline(std::cin, hostelAddress);

	std::cout << "Enter Hostel Phone Number: ";
	std::string hostelPhoneNumber;
	getline(std::cin, hostelPhoneNumber);

	std::cout << "Enter email address of Hostel: ";
	std::string hostelEmail;
	getline(std::cin, hostelEmail);

	hostel = Hostel(hostelName, hostelAddress, hostelPhoneNumber, hostelEmail);

	std::cout << "Hostel Details Entered" << std::endl;

	system("cls");

	hostel.displayHostelInfo();

	getchar();
}

// ----------- displayMenu -----------
void displayMenu()
{
	using namespace std;

	bool shouldExit = false;
	int choice;
	string choiceString;

	while (!shouldExit)
	{
		system("cls");
		cout << "1. Student Registration" << endl;
		cout << "2. Room Creation" << endl;
		cout << "3. Fee Generation" << endl;
		cout << "4. Invoice Status Update" << endl;
		cout << "5. Staff Creation" << endl;
		cout << "6. Display Tables" << endl;
		cout << "7. Exit" << endl;
		cout << "Enter your choice: ";

		try
		{
			cin >> choiceString;
			choice = stoi(choiceString);
		}
		catch (const std::exception e)
		{
			cout << "choice should be a number" << endl;
			waitForEnteringKey();
			continue;
		}

		switch (choice)
		{
		case 1:
			// TODO: Handle exception for different datatypes and entries.
			studentRegistration();
			break;
		case 2:
			// TODO: Handle exception for different datatypes and entries.
			roomCreation();
			break;
		case 3:
			generateInvoice();
			break;
		case 4:
			updateInvoiceStatus();
			break;
		case 5:
			staffCreation();
			break;
		case 6:
			hostel.displayHostelInfo();
			waitForEnteringKey();
			break;
		case 7:
			shouldExit = true;
			break;
		default:
			cout << "Invalid choice" << endl;
			break;
		}
	}
}

// ----------- studentRegistration -----------
void studentRegistration()
{
	using namespace std;

	if (!hostel.areRoomsAvailable())
	{
		system("cls");
		cout << "No rooms available" << endl;
		waitForEnteringKey();
		return;
	}

	system("cls");
	hostel.displayAvailableRooms();

	int studentId, roomNumber;
	short int studentSem;
	string studentIdString, roomNumberString, studentSemString;
	string studentName, studentCNIC, studentPhoneNumber, studentSchool, studentGender;

	cout
		<< "------------ Student Registration -------------" << endl;
	cout << "Enter Student ID: ";

	try
	{
		cin >> studentIdString;
		studentId = stoi(studentIdString);
	}
	catch (const std::exception e)
	{
		cout << "StudentID should be a number" << endl;
		waitForEnteringKey();
		return;
	}

	cout << "Enter Student Name: ";
	cin.ignore();
	getline(cin, studentName);

	cout << "Enter Student CNIC (1234512312121): ";
	cin.ignore();
	cin >> studentCNIC;

	cout << "Enter Student Phone Number: ";
	cin >> studentPhoneNumber;

	cout << "Enter Student School: ";
	cin >> studentSchool;

	cout << "Enter Student Gender: ";
	cin >> studentGender;

	cout << "Enter Student Semester: ";

	try
	{
		cin >> studentSemString;
		studentSem = stoi(studentSemString);
	}
	catch (const std::exception e)
	{
		cout << "Semester should be a number" << endl;
		waitForEnteringKey();
		return;
	}

	cout << "Enter Room Number: ";

	try
	{
		cin >> roomNumberString;
		roomNumber = stoi(roomNumberString);
	}
	catch (const std::exception e)
	{
		cout << "roomNumber should be a number" << endl;
		waitForEnteringKey();
		return;
	}

	if (!hostel.roomNumberExists(roomNumber))
	{
		cout << "Pick a valid room number" << endl;
		waitForEnteringKey();
		return;
	}

	hostel.addStudent(studentId, studentName, studentCNIC, studentPhoneNumber, studentSchool, studentGender, studentSem, roomNumber);

	cout << "---------------- Student Added ------------------" << endl;
	waitForEnteringKey();
}

// ----------- roomCreation -----------
void roomCreation()
{
	int roomNumber;
	std::string roomNumberString;
	system("cls");

	std::cout << "Enter Room Number: ";
	try
	{
		std::cin >> roomNumberString;
		roomNumber = std::stoi(roomNumberString);
	}
	catch (const std::exception e)
	{
		std::cout << "roomNumber should be a number" << std::endl;
		waitForEnteringKey();
		return;
	}
	hostel.addRoom(roomNumber);

	waitForEnteringKey();
}

// ----------- staffCreation -----------
void staffCreation()
{
	int staffID;
	std::string staffIDString;
	std::string staffName, staffCNIC, staffPhoneNumber, staffRole;

	system("cls");

	std::cout << "Enter Staff ID: ";

	try
	{
		std::cin >> staffIDString;
		staffID = stoi(staffIDString);
	}
	catch (const std::exception e)
	{
		std::cout << "StaffID should be a number" << std::endl;
		waitForEnteringKey();
		return;
	}

	std::cout << "Enter Staff Name: ";
	std::cin.ignore();
	getline(std::cin, staffName);

	std::cout << "Enter Staff CNIC: ";
	std::cin >> staffCNIC;

	std::cout << "Enter Staff Role: ";
	std::cin.ignore();
	getline(std::cin, staffRole);

	std::cout << "Enter Staff Phone Number: ";
	std::cin >> staffPhoneNumber;

	hostel.addStaff(staffID, staffName, staffCNIC, staffPhoneNumber, staffRole);

	waitForEnteringKey();
}

// ----------- generateInvoice -----------
void generateInvoice()
{

	using namespace std;

	system("cls");
	int studentID;
	int invoiceID;
	string studentIDString;
	string invoiceIDString;

	string invoiceDate;
	string dueDate;

	double amountDue;
	double amountAfterDue;
	string amountDueString;
	string amountAfterDueString;

	cout << "Enter Student ID: ";

	try
	{
		cin >> studentIDString;
		studentID = stoi(studentIDString);
	}
	catch (const std::exception e)
	{
		cout << "StudentID should be a number" << endl;
		waitForEnteringKey();
		return;
	}

	cout << "Enter Invoice ID: ";

	try
	{
		cin >> invoiceIDString;
		invoiceID = stoi(invoiceIDString);
	}
	catch (const std::exception e)
	{
		cout << "invoiceID should be a number" << endl;
		waitForEnteringKey();
		return;
	}

	cout << "Enter Invoice Date: ";
	cin.ignore();
	getline(cin, invoiceDate);

	cout << "Enter Due Date: ";
	cin.ignore();
	getline(cin, dueDate);

	cout << "Enter Amount Due: ";

	try
	{
		cin >> amountDueString;
		amountDue = stod(amountDueString);
	}
	catch (const std::exception e)
	{
		cout << "amountDue should be a number" << endl;
		waitForEnteringKey();
		return;
	}

	cout << "Enter Amount After Due: ";

	try
	{
		cin >> amountAfterDueString;
		amountAfterDue = stod(amountAfterDueString);
	}
	catch (const std::exception e)
	{
		cout << "amountAfterDue should be a number" << endl;
		waitForEnteringKey();
		return;
	}

	hostel.addInvoice(invoiceID, studentID, invoiceDate, dueDate, amountDue, amountAfterDue);
	waitForEnteringKey();
}

void updateInvoiceStatus()
{
	system("cls");

	std::cout << "----------------- Update Invoice Status ------------------" << std::endl;

	int invoiceID;
	std::string invoiceIDString;
	std::string status;

	std::cout << "Enter Invoice ID: ";
	std::cin >> invoiceIDString;

	try
	{
		invoiceID = std::stoi(invoiceIDString);
	}
	catch (const std::exception e)
	{
		std::cout << "invoiceID should be a number" << std::endl;
		waitForEnteringKey();
		return;
	}

	hostel.updateInvoiceStatus(invoiceID, true);
	waitForEnteringKey();
}
*/
