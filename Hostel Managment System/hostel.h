#include <iostream>
#include <vector>
#include "invoice.h"
#include "room.h"
#include "staff.h"
#include "student.h"
#include "texttable.hpp" // External library class header file for creating tables in console

#include "nlohmann/json.hpp"
#include "FileReader.h"

using JSON = nlohmann::json;

class Hostel
{
private:
    std::string hostelName;
    std::string hostelAddress;
    std::string hostelPhoneNumber;
    std::string hostelEmail;
    unsigned int invoiceIDTrack;
    bool seriousMode;
    std::vector<Invoice> invoicesList;
    std::vector<Room> roomList;
    std::vector<Student> studentList;
    std::vector<Staff> staffList;

public:
    Hostel();

    Hostel(std::string hostelName, std::string hostelAddress, std::string hostelPhoneNumber, std::string hostelEmail);

    Hostel(JSON hostelInfoJson);

    JSON toJson();

    void setHostelName(std::string hostelName);

    void setHostelAddress(std::string hostelAddress);

    void setHostelPhoneNumber(std::string hostelPhoneNumber);

    void setHostelEmail(std::string hostelEmail);

    unsigned int getInvoiceIDTrack()
    {
        return invoiceIDTrack;
    }

    std::string getHostelName();

    std::string getHostelAddress();

    std::string getHostelPhoneNumber();

    std::string getHostelEmail();

    void addRoom(Room room);

    void addStudent(Student student);

    void addStaff(Staff staff);

    void addInvoice(Invoice invoice);

    std::string getInvoiceStatusStr(Invoice invoice);

    void setMode(int mode);

    bool getMode();

    void displayHostelInfo();

    // ------------------------ Staff ------------------------

    void addStaff(int staffID, std::string staffName, std::string staffCNIC, std::string phoneNumber, std::string role);

    void removeStaff(int staffID);

    bool checkIfStaffExists(int staffID);

    std::string getAllStaffsTable();

    // ------------------------ Room ------------------------

    void addRoom(int roomNumber);

    void removeRoom(int roomNumber);

    void displayAvailableRooms();

    bool roomNumberExists(int roomNumber);

    bool areRoomsAvailable();

    bool roomExists(int roomNumber);

    bool isRoomSpaceAvailable(int roomNumber);

    bool isRoomEmpty(int roomNumber);

    std::string getAllRoomsTable();

    // ------------------------ Student ------------------------

    void addStudent(int studentID, std::string studentName, std::string studentCNIC, std::string phoneNumber, std::string school, std::string gender, short int sem, int roomNumber);

    void deleteStudent(int studentID);

    void promoteAllStudents();

    std::string getAllStudentsTable();

    // ------------------------ Invoice ------------------------

    bool checkIfStudentExists(int studentID);

    void addInvoice(int studentID, std::string invoiceDate, std::string dueDate, double amountDue, double amountAfterDue);

    void addInvoicesForAllStudents(std::string invoiceDate, std::string dueDate, double amountDue, double amountAfterDue);

    bool checkIfInvoiceExists(int invoiceID);

    bool checkIfInvoiceIsPaid(int invoiceID);

    void updateInvoiceStatus(int invoiceID, bool status);

    std::string getAllInvoicesTable();

    std::string getAllInvoicesByStudentID(int studentID, bool status);

    std::string getAllInvoicesByInvoiceID(unsigned int invoiceID);

    std::string getAllInvoicesByStatus(bool status);
};