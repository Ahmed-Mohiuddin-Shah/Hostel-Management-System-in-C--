#include "student.h"

Student::Student(int studentID, std::string studentName, std::string studentCNIC, std::string phoneNumber, std::string school, std::string gender, short int sem)
{
	this->studentID = studentID;
	this->studentName = studentName;
	this->studentCNIC = studentCNIC;
	this->phoneNumber = phoneNumber;
	this->school = school;
	this->gender = gender;
	this->sem = sem;
}

void Student::setStudentID(int studentID)
{
	this->studentID = studentID;
}

void Student::setStudentName(std::string studentName)
{
	this->studentName = studentName;
}

void Student::setStudentCNIC(std::string studentCNIC)
{
	this->studentCNIC = studentCNIC;
}

void Student::setPhoneNumber(std::string phoneNumber)
{
	this->phoneNumber = phoneNumber;
}

void Student::setSchool(std::string school)
{
	this->school = school;
}

void Student::setGender(std::string gender)
{
	this->gender = gender;
}

void Student::setSem(short int sem)
{
	this->sem = sem;
}

int Student::getStudentID()
{
	return studentID;
}

std::string Student::getStudentName()
{
	return studentName;
}

std::string Student::getStudentCNIC()
{
	return studentCNIC;
}

std::string Student::getPhoneNumber()
{
	return phoneNumber;
}

std::string Student::getSchool()
{
	return school;
}

std::string Student::getGender()
{
	return gender;
}

short int Student::getSem()
{
	return sem;
}

std::string Student::toCSV()
{
	std::string csv = "";
	csv += std::to_string(studentID) + ",";
	csv += studentName + ",";
	csv += studentCNIC + ",";
	csv += phoneNumber + ",";
	csv += school + ",";
	csv += gender + ",";
	csv += std::to_string(sem);
	return csv;
}