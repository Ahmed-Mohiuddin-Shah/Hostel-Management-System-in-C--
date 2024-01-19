#include "room.h"

Room::Room(int roomNumber)
{
    this->roomNumber = roomNumber;
    this->studentCount = 0;
}

Room::Room(int roomNumber, int studentCount, std::vector<int> studentIDList) {
    this->roomNumber = roomNumber;
    this->studentCount = studentCount;
    this->studentIDList = studentIDList;
}

void Room::setRoomNumber(int roomNumber)
{
    this->roomNumber = roomNumber;
}

void Room::setStudentCount(int studentCount)
{
    this->studentCount = studentCount;
}

int Room::getRoomNumber()
{
    return roomNumber;
}

int Room::getStudentCount()
{
    return studentCount;
}

int Room::getStudentID(int index)
{
    return studentIDList[index];
}

std::vector<int> Room::getStudentIDList()
{
    return studentIDList;
}

void Room::addStudent(int studentID)
{
    if (studentCount == maxStudentCount)
    {
        std::cout << "Room is full" << std::endl;
        return;
    }

    studentIDList.push_back(studentID);
    studentCount++;
}

void Room::removeStudent(int studentID)
{
    if (studentCount == 0)
    {
        std::cout << "Room is empty" << std::endl;
        return;
    }

    for (int i = 0; i < studentIDList.size(); i++)
    {
        if (studentIDList[i] == studentID)
        {
            studentIDList.erase(studentIDList.begin() + i);
            studentCount--;
            break;
        }
    }
}