#include <iostream>
#include <vector>

class Room
{
private:
    int roomNumber;
    std::vector<int> studentIDList;
    int studentCount;

public:
    static const int maxStudentCount = 3;

    Room(int roomNumber)
    {
        this->roomNumber = roomNumber;
        this->studentCount = 0;
    }

    void setRoomNumber(int roomNumber)
    {
        this->roomNumber = roomNumber;
    }

    void setStudentCount(int studentCount)
    {
        this->studentCount = studentCount;
    }

    int getRoomNumber()
    {
        return roomNumber;
    }

    int getStudentCount()
    {
        return studentCount;
    }

    int getStudentID(int index)
    {
        return studentIDList[index];
    }

    std::vector<int> getStudentIDList()
    {
        return studentIDList;
    }

    void addStudent(int studentID)
    {
        if (studentCount == maxStudentCount)
        {
            std::cout << "Room is full" << std::endl;
            return;
        }

        studentIDList.push_back(studentID);
        studentCount++;
    }

    void removeStudent(int studentID)
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
};