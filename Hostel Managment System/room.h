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

    Room(int roomNumber);

    Room(int roomNumber, int studentCount, std::vector<int> studentIDList);

    void setRoomNumber(int roomNumber);

    void setStudentCount(int studentCount);

    int getRoomNumber();

    int getStudentCount();

    int getStudentID(int index);

    std::vector<int> getStudentIDList();

    void addStudent(int studentID);

    void removeStudent(int studentID);
};