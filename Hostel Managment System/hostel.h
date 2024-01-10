#include <iostream>
#include <vector>
#include "invoice.h"
#include "room.h"
#include "staff.h"
#include "student.h"
#include "texttable.hpp" // External library class header file for creating tables in console

class Hostel
{
private:
    std::string hostelName;
    std::string hostelAddress;
    std::string hostelPhoneNumber;
    std::string hostelEmail;
    std::vector<Invoice> invoicesList;
    std::vector<Room> roomList;
    std::vector<Student> studentList;
    std::vector<Staff> staffList;

public:
    Hostel()
    {
    }

    Hostel(std::string hostelName, std::string hostelAddress, std::string hostelPhoneNumber, std::string hostelEmail)
    {
        this->hostelName = hostelName;
        this->hostelAddress = hostelAddress;
        this->hostelPhoneNumber = hostelPhoneNumber;
        this->hostelEmail = hostelEmail;
    }

    void setHostelName(std::string hostelName)
    {
        this->hostelName = hostelName;
    }

    void setHostelAddress(std::string hostelAddress)
    {
        this->hostelAddress = hostelAddress;
    }

    void setHostelPhoneNumber(std::string hostelPhoneNumber)
    {
        this->hostelPhoneNumber = hostelPhoneNumber;
    }

    void setHostelEmail(std::string hostelEmail)
    {
        this->hostelEmail = hostelEmail;
    }

    std::string getHostelName()
    {
        return hostelName;
    }

    std::string getHostelAddress()
    {
        return hostelAddress;
    }

    std::string getHostelPhoneNumber()
    {
        return hostelPhoneNumber;
    }

    std::string getHostelEmail()
    {
        return hostelEmail;
    }

    void addRoom(Room room)
    {
        roomList.push_back(room);
    }

    void addStudent(Student student)
    {
        studentList.push_back(student);
    }

    void addStaff(Staff staff)
    {
        staffList.push_back(staff);
    }

    void addInvoice(Invoice invoice)
    {
        invoicesList.push_back(invoice);
    }

    std::string getInvoiceStatusStr(Invoice invoice)
    {
        return invoice.getStatus() ? "Paid" : "UnPaid";
    }

    void displayHostelInfo()
    {
        using namespace std;
        cout << "--------------- Hostel Deets -------------------" << endl;
        cout << "Hostel Name: " << hostelName << endl;
        cout << "Hostel Address: " << hostelAddress << endl;
        cout << "Hostel Phone Number: " << hostelPhoneNumber << endl;
        cout << "Hostel Email: " << hostelEmail << endl;

        cout << "--------------- Staff Deets -------------------" << endl;
        TextTable staffTable('-', '|', '+');
        staffTable.add("Staff ID");
        staffTable.add("Staff Name");
        staffTable.add("Staff CNIC");
        staffTable.add("Phone Number");
        staffTable.add("Role");
        staffTable.endOfRow();

        for (auto &staff : staffList)
        {
            staffTable.add(to_string(staff.getStaffID()));
            staffTable.add(staff.getStaffName());
            staffTable.add(staff.getStaffCNIC());
            staffTable.add(staff.getPhoneNumber());
            staffTable.add(staff.getRole());
            staffTable.endOfRow();
        }
        staffTable.setAlignment(2, TextTable::Alignment::RIGHT);

        cout << staffTable << endl;

        cout << "--------------- Room Deets -------------------" << endl;
        TextTable roomTable('-', '|', '+');
        roomTable.add("Room Number");
        roomTable.add("Student Count");
        roomTable.add("Student ID List");
        roomTable.endOfRow();

        for (auto &room : roomList)
        {
            roomTable.add(to_string(room.getRoomNumber()));
            roomTable.add(to_string(room.getStudentCount()));
            string studentsCSV = "";
            for (auto studentID : room.getStudentIDList())
            {
                studentsCSV += to_string(studentID) + ", ";
            }
            roomTable.add(studentsCSV);
            roomTable.endOfRow();
        }

        roomTable.setAlignment(2, TextTable::Alignment::RIGHT);

        cout << roomTable << endl;

        cout << "--------------- Student Deets -------------------" << endl;
        TextTable studentTable('-', '|', '+');
        studentTable.add("Student ID");
        studentTable.add("Student Name");
        studentTable.add("Student CNIC");
        studentTable.add("Phone Number");
        studentTable.add("School");
        studentTable.add("Semester");
        studentTable.endOfRow();

        for (auto &student : studentList)
        {
            studentTable.add(to_string(student.getStudentID()));
            studentTable.add(student.getStudentName());
            studentTable.add(student.getStudentCNIC());
            studentTable.add(student.getPhoneNumber());
            studentTable.add(student.getSchool());
            studentTable.add(to_string(student.getSem()));
            studentTable.endOfRow();
        }

        studentTable.setAlignment(2, TextTable::Alignment::RIGHT);
        cout << studentTable << endl;

        cout << "--------------- Invoice Deets -------------------" << endl;
        TextTable invoiceTable('-', '|', '+');
        invoiceTable.add("Invoice ID");
        invoiceTable.add("Student ID");
        invoiceTable.add("Student Name");
        invoiceTable.add("Invoice Date");
        invoiceTable.add("Due Date");
        invoiceTable.add("Status");
        invoiceTable.add("Amount Due");
        invoiceTable.add("Amount After Due");
        invoiceTable.endOfRow();

        for (auto &invoice : invoicesList)
        {
            invoiceTable.add(to_string(invoice.getInvoiceID()));
            invoiceTable.add(to_string(invoice.getStudentID()));
            for (auto student : studentList)
            {
                if (student.getStudentID() == invoice.getStudentID())
                {
                    invoiceTable.add(student.getStudentName());
                }
            }
            invoiceTable.add(invoice.getInvoiceDate());
            invoiceTable.add(invoice.getDueDate());
            invoiceTable.add(getInvoiceStatusStr(invoice));
            invoiceTable.add(to_string(invoice.getAmountDue()));
            invoiceTable.add(to_string(invoice.getAmountAfterDue()));
            invoiceTable.endOfRow();
        }

        invoiceTable.setAlignment(2, TextTable::Alignment::RIGHT);
        cout << invoiceTable << endl;
    }

    // ------------------------ Staff ------------------------

    void addStaff(int staffID, std::string staffName, std::string staffCNIC, std::string phoneNumber, std::string role)
    {

        if (staffID < 0)
        {
            std::cout << "Invalid staff ID!" << std::endl;
            return;
        }

        for (int i = 0; i < staffList.size(); i++)
        {
            if (staffList[i].getStaffID() == staffID)
            {
                std::cout << "Staff already exists!" << std::endl;
                return;
            }
        }

        Staff staff(staffID, staffName, staffCNIC, phoneNumber, role);
        staffList.push_back(staff);

        std::cout << "-------------- Staff Added -----------------" << std::endl;
    }

    void removeStaff(int staffID)
    {
        for (int i = 0; i < staffList.size(); i++)
        {
            if (staffList[i].getStaffID() == staffID)
            {
                staffList.erase(staffList.begin() + i);
                break;
            }
        }
    }

    void displayAllStaff()
    {
        TextTable staffTable('-', '|', '+');
        staffTable.add("Staff ID");
        staffTable.add("Staff Name");
        staffTable.add("Staff CNIC");
        staffTable.add("Phone Number");
        staffTable.add("Role");
        staffTable.endOfRow();

        for (auto &staff : staffList)
        {
            staffTable.add(std::to_string(staff.getStaffID()));
            staffTable.add(staff.getStaffName());
            staffTable.add(staff.getStaffCNIC());
            staffTable.add(staff.getPhoneNumber());
            staffTable.add(staff.getRole());
            staffTable.endOfRow();
        }
        staffTable.setAlignment(2, TextTable::Alignment::RIGHT);
        std::cout << staffTable << std::endl;
    }

    // ------------------------ Room ------------------------

    void addRoom(int roomNumber)
    {
        if (roomNumber < 0)
        {
            std::cout << "Invalid room number!" << std::endl;
            return;
        }

        for (int i = 0; i < roomList.size(); i++)
        {
            if (roomList[i].getRoomNumber() == roomNumber)
            {
                std::cout << "Room already exists!" << std::endl;
                return;
            }
        }

        Room room(roomNumber);
        roomList.push_back(room);

        std::cout << "Room Added" << std::endl;
    }

    void removeRoom(int roomNumber)
    {
        for (int i = 0; i < roomList.size(); i++)
        {
            if (roomList[i].getRoomNumber() == roomNumber)
            {
                if (roomList[i].getStudentCount() > 0)
                {
                    std::cout << "Room is not empty!" << std::endl;
                    return;
                }
                else
                {
                    roomList.erase(roomList.begin() + i);
                    break;
                }
            }
        }
    }

    void displayAvailableRooms()
    {
        std::cout << "-------------- Available Rooms ------------------- " << std::endl;
        TextTable roomTable('-', '|', '+');
        roomTable.add("Room Number");
        roomTable.add("Student Count");
        roomTable.endOfRow();

        for (auto &room : roomList)
        {
            if (room.getStudentCount() < room.maxStudentCount)
            {
                roomTable.add(std::to_string(room.getRoomNumber()));
                roomTable.add(std::to_string(room.getStudentCount()));
                roomTable.endOfRow();
            }
        }

        roomTable.setAlignment(2, TextTable::Alignment::RIGHT);
        std::cout << roomTable << std::endl;
    }

    bool roomNumberExists(int roomNumber)
    {
        for (auto room : roomList)
        {
            if (room.getRoomNumber() == roomNumber)
            {
                return true;
            }
        }
        return false;
    }

    bool areRoomsAvailable()
    {
        for (auto room : roomList)
        {
            if (room.getStudentCount() < room.maxStudentCount)
            {
                return true;
            }
        }
        return false;
    }

    void displayAllRooms()
    {

        TextTable roomTable('-', '|', '+');
        roomTable.add("Room Number");
        roomTable.add("Student Count");
        roomTable.add("Student ID List");
        roomTable.endOfRow();

        for (auto &room : roomList)
        {
            roomTable.add(std::to_string(room.getRoomNumber()));
            roomTable.add(std::to_string(room.getStudentCount()));
            for (auto studentID : room.getStudentIDList())
            {
                roomTable.add(std::to_string(studentID));
            }
            roomTable.endOfRow();
        }

        roomTable.setAlignment(2, TextTable::Alignment::RIGHT);
        std::cout << roomTable << std::endl;
    }

    // ------------------------ Student ------------------------

    void addStudent(int studentID, std::string studentName, std::string studentCNIC, std::string phoneNumber, std::string school, std::string gender, short int sem, int roomNumber)
    {

        if (studentID < 0)
        {
            std::cout << "Invalid student ID!" << std::endl;
            return;
        }

        for (int i = 0; i < studentList.size(); i++)
        {
            if (studentList[i].getStudentID() == studentID)
            {
                std::cout << "Student already exists!" << std::endl;
                return;
            }
        }

        for (auto &room : roomList)
        {
            if (room.getRoomNumber() == roomNumber)
            {
                if (room.getStudentCount() == Room::maxStudentCount)
                {
                    std::cout << "Room is full!" << std::endl;
                    return;
                }
                else
                {
                    room.addStudent(studentID);
                }
            }
        }

        Student student(studentID, studentName, studentCNIC, phoneNumber, school, gender, sem);
        student.setGender(gender);
        student.setSem(sem);
        student.setSchool(school);
        student.setStudentCNIC(studentCNIC);
        student.setStudentID(studentID);
        student.setStudentName(studentName);
        studentList.push_back(student);
    }

    void displayAllStudents()
    {

        TextTable studentTable('-', '|', '+');
        studentTable.add("Student ID");
        studentTable.add("Student Name");
        studentTable.add("Student CNIC");
        studentTable.add("Phone Number");
        studentTable.add("School");
        studentTable.add("Semester");
        studentTable.add("Room Number");
        studentTable.endOfRow();

        for (auto &student : studentList)
        {
            studentTable.add(std::to_string(student.getStudentID()));
            studentTable.add(student.getStudentName());
            studentTable.add(student.getStudentCNIC());
            studentTable.add(student.getPhoneNumber());
            studentTable.add(student.getSchool());
            studentTable.add(std::to_string(student.getSem()));
            for (auto room : roomList)
            {
                for (auto studentID : room.getStudentIDList())
                {
                    if (studentID == student.getStudentID())
                    {
                        studentTable.add(std::to_string(room.getRoomNumber()));
                    }
                }
            }
            studentTable.endOfRow();
        }

        studentTable.setAlignment(2, TextTable::Alignment::RIGHT);
        std::cout << studentTable << std::endl;
    }

    // ------------------------ Invoice ------------------------

    bool checkIfStudentExists(int studentID)
    {
        for (auto &student : studentList)
        {
            if (student.getStudentID() == studentID)
            {
                return true;
            }
        }
        return false;
    }

    void addInvoice(int invoiceID, int studentID, std::string invoiceDate, std::string dueDate, double amountDue, double amountAfterDue)
    {

        if (invoiceID < 0)
        {
            std::cout << "Invalid invoice ID!" << std::endl;
            return;
        }

        if (studentID < 0)
        {
            std::cout << "Invalid student ID!" << std::endl;
            return;
        }

        if (amountDue < 0)
        {
            std::cout << "Invalid amount due!" << std::endl;
            return;
        }

        if (amountAfterDue < 0 && amountAfterDue < amountDue)
        {
            std::cout << "Invalid amount after due!" << std::endl;
            return;
        }

        // TODO: Optimize this
        // if (invoiceDate > dueDate)
        // {
        //     std::cout << "Invalid invoice date!" << std::endl;
        //     return;
        // }

        if (!checkIfStudentExists(studentID))
        {
            std::cout << "Student does not exist!" << std::endl;
            return;
        }

        for (int i = 0; i < invoicesList.size(); i++)
        {
            if (invoicesList[i].getInvoiceID() == invoiceID)
            {
                std::cout << "Invoice already exists!" << std::endl;
                return;
            }
        }

        Invoice invoice(invoiceID, studentID, invoiceDate, dueDate, amountDue, amountAfterDue);
        invoicesList.push_back(invoice);
        std::cout << "----------------------Invoice Added!-------------" << std::endl;
    }

    void updateInvoiceStatus(int invoiceID, bool status)
    {

        if (invoiceID < 0)
        {
            std::cout << "Invalid invoice ID!" << std::endl;
            return;
        }

        if (status != 0 && status != 1)
        {
            std::cout << "Invalid status!" << std::endl;
            return;
        }

        for (int i = 0; i < invoicesList.size(); i++)
        {
            if (invoicesList[i].getInvoiceID() == invoiceID)
            {
                invoicesList[i].setStatus(status);
                std::cout << "----------------------Invoice status updated!-------------" << std::endl;
                return;
            }
        }

        std::cout << "----------- Invoice does not exist! -----------------" << std::endl;
        return;
    }

    void displayAllInvoices()
    {

        TextTable invoiceTable('-', '|', '+');
        invoiceTable.add("Invoice ID");
        invoiceTable.add("Student ID");
        invoiceTable.add("Student Name");
        invoiceTable.add("Invoice Date");
        invoiceTable.add("Due Date");
        invoiceTable.add("Status");
        invoiceTable.add("Amount Due");
        invoiceTable.add("Amount After Due");
        invoiceTable.endOfRow();

        for (auto &invoice : invoicesList)
        {
            invoiceTable.add(std::to_string(invoice.getInvoiceID()));
            invoiceTable.add(std::to_string(invoice.getStudentID()));
            for (auto student : studentList)
            {
                if (student.getStudentID() == invoice.getStudentID())
                {
                    invoiceTable.add(student.getStudentName());
                }
            }
            invoiceTable.add(invoice.getInvoiceDate());
            invoiceTable.add(invoice.getDueDate());
            invoiceTable.add(getInvoiceStatusStr(invoice));
            invoiceTable.add(std::to_string(invoice.getAmountDue()));
            invoiceTable.add(std::to_string(invoice.getAmountAfterDue()));
            invoiceTable.endOfRow();
        }

        invoiceTable.setAlignment(2, TextTable::Alignment::RIGHT);
        std::cout << invoiceTable << std::endl;
    }

    void displayInvoicesByStudentID(int studentID)
    {
        TextTable invoiceTable('-', '|', '+');
        invoiceTable.add("Invoice ID");
        invoiceTable.add("Student ID");
        invoiceTable.add("Student Name");
        invoiceTable.add("Invoice Date");
        invoiceTable.add("Due Date");
        invoiceTable.add("Status");
        invoiceTable.add("Amount Due");
        invoiceTable.add("Amount After Due");
        invoiceTable.endOfRow();

        for (auto &invoice : invoicesList)
        {
            if (invoice.getStudentID() == studentID)
            {
                invoiceTable.add(std::to_string(invoice.getInvoiceID()));
                invoiceTable.add(std::to_string(invoice.getStudentID()));
                for (auto student : studentList)
                {
                    if (student.getStudentID() == invoice.getStudentID())
                    {
                        invoiceTable.add(student.getStudentName());
                    }
                }
                invoiceTable.add(invoice.getInvoiceDate());
                invoiceTable.add(invoice.getDueDate());
                invoiceTable.add(getInvoiceStatusStr(invoice));
                invoiceTable.add(std::to_string(invoice.getAmountDue()));
                invoiceTable.add(std::to_string(invoice.getAmountAfterDue()));
                invoiceTable.endOfRow();
            }
        }

        invoiceTable.setAlignment(2, TextTable::Alignment::RIGHT);
        std::cout << invoiceTable << std::endl;
    }

    void displayInvoicesByStatus(bool status)
    {

        TextTable invoiceTable('-', '|', '+');
        invoiceTable.add("Invoice ID");
        invoiceTable.add("Student ID");
        invoiceTable.add("Student Name");
        invoiceTable.add("Invoice Date");
        invoiceTable.add("Due Date");
        invoiceTable.add("Status");
        invoiceTable.add("Amount Due");
        invoiceTable.add("Amount After Due");
        invoiceTable.endOfRow();

        for (auto &invoice : invoicesList)
        {
            if (invoice.getStatus() == status)
            {
                invoiceTable.add(std::to_string(invoice.getInvoiceID()));
                invoiceTable.add(std::to_string(invoice.getStudentID()));
                for (auto student : studentList)
                {
                    if (student.getStudentID() == invoice.getStudentID())
                    {
                        invoiceTable.add(student.getStudentName());
                    }
                }
                invoiceTable.add(invoice.getInvoiceDate());
                invoiceTable.add(invoice.getDueDate());
                invoiceTable.add(getInvoiceStatusStr(invoice));
                invoiceTable.add(std::to_string(invoice.getAmountDue()));
                invoiceTable.add(std::to_string(invoice.getAmountAfterDue()));
                invoiceTable.endOfRow();
            }
        }

        invoiceTable.setAlignment(2, TextTable::Alignment::RIGHT);
        std::cout << invoiceTable << std::endl;
    }

    void displayInvoicesByDate(std::string date)
    {

        TextTable invoiceTable('-', '|', '+');
        invoiceTable.add("Invoice ID");
        invoiceTable.add("Student ID");
        invoiceTable.add("Student Name");
        invoiceTable.add("Invoice Date");
        invoiceTable.add("Due Date");
        invoiceTable.add("Status");
        invoiceTable.add("Amount Due");
        invoiceTable.add("Amount After Due");
        invoiceTable.endOfRow();

        for (auto &invoice : invoicesList)
        {
            if (invoice.getInvoiceDate() == date)
            {
                invoiceTable.add(std::to_string(invoice.getInvoiceID()));
                invoiceTable.add(std::to_string(invoice.getStudentID()));
                for (auto student : studentList)
                {
                    if (student.getStudentID() == invoice.getStudentID())
                    {
                        invoiceTable.add(student.getStudentName());
                    }
                }
                invoiceTable.add(invoice.getInvoiceDate());
                invoiceTable.add(invoice.getDueDate());
                invoiceTable.add(getInvoiceStatusStr(invoice));
                invoiceTable.add(std::to_string(invoice.getAmountDue()));
                invoiceTable.add(std::to_string(invoice.getAmountAfterDue()));
                invoiceTable.endOfRow();
            }
        }

        invoiceTable.setAlignment(2, TextTable::Alignment::RIGHT);
        std::cout << invoiceTable << std::endl;
    }
};