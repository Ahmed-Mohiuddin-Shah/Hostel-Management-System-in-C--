#include <iostream>
#include <sstream>

class Student
{

private:
	int studentID;
	std::string studentName;
	std::string studentCNIC;
	std::string phoneNumber;
	std::string school;
	std::string gender;
	short int sem;

public:
	Student(int studentID, std::string studentName, std::string studentCNIC, std::string phoneNumber, std::string school, std::string gender, short int sem);

	void setStudentID(int studentID);

	void setStudentName(std::string studentName);

	void setStudentCNIC(std::string studentCNIC);

	void setPhoneNumber(std::string phoneNumber);

	void setSchool(std::string school);

	void setGender(std::string gender);

	void setSem(short int sem);

	int getStudentID();

	std::string getStudentName();

	std::string getStudentCNIC();

	std::string getPhoneNumber();

	std::string getSchool();

	std::string getGender();

	short int getSem();

	std::string toCSV();
};