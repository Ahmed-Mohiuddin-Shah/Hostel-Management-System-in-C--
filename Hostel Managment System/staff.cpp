#include "staff.h"

Staff::Staff(int staffID, std::string staffName, std::string staffCNIC, std::string phoneNumber, std::string role)
{
    this->staffID = staffID;
    this->staffName = staffName;
    this->staffCNIC = staffCNIC;
    this->phoneNumber = phoneNumber;
    this->role = role;
}

void Staff::setStaffID(int staffID)
{
    this->staffID = staffID;
}

void Staff::setStaffName(std::string staffName)
{
    this->staffName = staffName;
}

void Staff::setStaffCNIC(std::string staffCNIC)
{
    this->staffCNIC = staffCNIC;
}

void Staff::setPhoneNumber(std::string phoneNumber)
{
    this->phoneNumber = phoneNumber;
}

void Staff::setRole(std::string role)
{
    this->role = role;
}

int Staff::getStaffID()
{
    return staffID;
}

std::string Staff::getStaffName()
{
    return staffName;
}

std::string Staff::getStaffCNIC()
{
    return staffCNIC;
}

std::string Staff::getPhoneNumber()
{
    return phoneNumber;
}

std::string Staff::getRole()
{
    return role;
}