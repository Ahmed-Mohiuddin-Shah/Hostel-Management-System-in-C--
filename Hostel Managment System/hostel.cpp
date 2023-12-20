#include "hostel.h"

Hostel::Hostel()
{
    this->seriousMode = true;
}

Hostel::Hostel(std::string hostelName, std::string hostelAddress, std::string hostelPhoneNumber, std::string hostelEmail)
{
    this->hostelName = hostelName;
    this->hostelAddress = hostelAddress;
    this->hostelPhoneNumber = hostelPhoneNumber;
    this->hostelEmail = hostelEmail;
    this->invoiceIDTrack = 0;
    this->seriousMode = true;
}

Hostel::Hostel(JSON hostelInfoJson)
{
    this->hostelName = hostelInfoJson["hostel_name"];
    this->hostelAddress = hostelInfoJson["hostel_address"];
    this->hostelPhoneNumber = hostelInfoJson["hostel_ph_no"];
    this->hostelEmail = hostelInfoJson["hostel_email"];

    this->invoiceIDTrack = hostelInfoJson["inv_id_track"];
    this->seriousMode = hostelInfoJson["mode"];

    // Initialize other data members using jsonData
    for (auto json : hostelInfoJson["rooms"])
    {
        std::vector<int> sIDList;
        for (auto entry : json["s_id_list"])
        {
            sIDList.push_back(entry);
        }
        roomList.push_back(Room(json["room_num"], json["s_count"], sIDList));
    }

    for (auto json : hostelInfoJson["students"])
    {
        studentList.push_back(Student(
            json["s_id"],
            json["s_name"],
            json["s_cnic"],
            json["s_ph_no"],
            json["school"],
            json["gender"],
            json["sem"]));
    }

    for (auto json : hostelInfoJson["staffs"])
    {
        staffList.push_back(Staff(
            json["st_id"],
            json["st_name"],
            json["st_cnic"],
            json["st_ph_no"],
            json["role"]));
    }

    for (auto json : hostelInfoJson["invoices"])
    {
        invoicesList.push_back(Invoice(
            json["i_id"],
            json["s_id"],
            json["i_date"],
            json["i_due_date"],
            json["status"],
            json["am_due"],
            json["am_aft_due"]));
    }
}

JSON Hostel::toJson()
{
    JSON hostelJSON;

    hostelJSON["hostel_name"] = getHostelName();
    hostelJSON["hostel_address"] = getHostelAddress();
    hostelJSON["hostel_ph_no"] = getHostelPhoneNumber();
    hostelJSON["hostel_email"] = getHostelEmail();

    hostelJSON["inv_id_track"] = getInvoiceIDTrack();
    hostelJSON["mode"] = getMode();

    std::vector<JSON> roomsVector;

    for (auto room : roomList)
    {
        JSON j;
        j["room_num"] = room.getRoomNumber();
        j["s_count"] = room.getStudentCount();
        JSON j_vector(room.getStudentIDList());
        j["s_id_list"] = j_vector;
        roomsVector.push_back(j);
    }

    JSON roomsJSONVector(roomsVector);

    hostelJSON["rooms"] = roomsJSONVector;

    std::vector<JSON> studentsVector;

    for (auto student : studentList)
    {
        JSON j;
        j["s_id"] = student.getStudentID();
        j["s_name"] = student.getStudentName();
        j["s_cnic"] = student.getStudentCNIC();
        j["s_ph_no"] = student.getPhoneNumber();
        j["school"] = student.getSchool();
        j["gender"] = student.getGender();
        j["sem"] = student.getSem();
        studentsVector.push_back(j);
    }

    JSON studentsJSONVector(studentsVector);

    hostelJSON["students"] = studentsJSONVector;

    std::vector<JSON> staffsVector;

    for (auto staff : staffList)
    {
        JSON j;
        j["st_id"] = staff.getStaffID();
        j["st_name"] = staff.getStaffName();
        j["st_cnic"] = staff.getStaffCNIC();
        j["st_ph_no"] = staff.getPhoneNumber();
        j["role"] = staff.getRole();
        staffsVector.push_back(j);
    }

    JSON staffsJSONVector(staffsVector);

    hostelJSON["staffs"] = staffsJSONVector;

    hostelJSON["invoices"] = {};

    std::vector<JSON> invoicesVector;

    for (auto invoice : invoicesList)
    {
        JSON j;
        j["i_id"] = invoice.getInvoiceID();
        j["s_id"] = invoice.getStudentID();
        j["i_date"] = invoice.getInvoiceDate();
        j["i_due_date"] = invoice.getDueDate();
        j["status"] = invoice.getStatus();
        j["am_due"] = invoice.getAmountDue();
        j["am_aft_due"] = invoice.getAmountAfterDue();
        invoicesVector.push_back(j);
    }

    JSON invoicesJSONVector(invoicesVector);

    hostelJSON["invoices"] = invoicesJSONVector;

    return hostelJSON;
}

void Hostel::setHostelName(std::string hostelName)
{
    this->hostelName = hostelName;
}

void Hostel::setHostelAddress(std::string hostelAddress)
{
    this->hostelAddress = hostelAddress;
}

void Hostel::setHostelPhoneNumber(std::string hostelPhoneNumber)
{
    this->hostelPhoneNumber = hostelPhoneNumber;
}

void Hostel::setHostelEmail(std::string hostelEmail)
{
    this->hostelEmail = hostelEmail;
}

std::string Hostel::getHostelName()
{
    return hostelName;
}

std::string Hostel::getHostelAddress()
{
    return hostelAddress;
}

std::string Hostel::getHostelPhoneNumber()
{
    return hostelPhoneNumber;
}

std::string Hostel::getHostelEmail()
{
    return hostelEmail;
}

void Hostel::setMode(int mode)
{
    seriousMode = mode;
}

bool Hostel::getMode()
{
    return seriousMode;
}

void Hostel::addRoom(Room room)
{
    roomList.push_back(room);
}

void Hostel::addStudent(Student student)
{
    studentList.push_back(student);
}

void Hostel::addStaff(Staff staff)
{
    staffList.push_back(staff);
}

void Hostel::addInvoice(Invoice invoice)
{
    invoicesList.push_back(invoice);
}

std::string Hostel::getInvoiceStatusStr(Invoice invoice)
{
    return invoice.getStatus() ? "Paid" : "UnPaid";
}

void Hostel::displayHostelInfo()
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

void Hostel::addStaff(int staffID, std::string staffName, std::string staffCNIC, std::string phoneNumber, std::string role)
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
}

void Hostel::removeStaff(int staffID)
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

bool Hostel::checkIfStaffExists(int staffID)
{
    for (auto &staff : staffList)
    {
        if (staff.getStaffID() == staffID)
        {
            return true;
        }
    }
    return false;
}

std::string Hostel::getAllStaffsTable()
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
    std::string s;
    std::ostringstream os;
    os << staffTable;
    s = os.str();
    return s;
}

// ------------------------ Room ------------------------

void Hostel::addRoom(int roomNumber)
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
}

void Hostel::removeRoom(int roomNumber)
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

void Hostel::displayAvailableRooms()
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

bool Hostel::roomNumberExists(int roomNumber)
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

bool Hostel::areRoomsAvailable()
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

bool Hostel::roomExists(int roomNumber)
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

bool Hostel::isRoomSpaceAvailable(int roomNumber)
{
    for (auto &room : roomList)
    {
        if (room.getRoomNumber() == roomNumber)
        {
            if (room.getStudentCount() == Room::maxStudentCount)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}

bool Hostel::isRoomEmpty(int roomNumber)
{
    for (auto &room : roomList)
    {
        if (room.getRoomNumber() == roomNumber)
        {
            if (room.getStudentCount() == 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    return false;
}

std::string Hostel::getAllRoomsTable()
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
        std::string studentListString;
        for (auto studentID : room.getStudentIDList())
        {
            studentListString.append(std::string(", ") + std::to_string(studentID));
        }
        if (!studentListString.empty())
        {
            studentListString = studentListString.substr(2, studentListString.length()); // to remove the beginning comma
        }
        roomTable.add(studentListString);
        roomTable.endOfRow();
    }

    roomTable.setAlignment(2, TextTable::Alignment::RIGHT);
    std::string s;
    std::ostringstream os;
    os << roomTable;
    s = os.str();
    return s;
}

// ------------------------ Student ------------------------

void Hostel::addStudent(int studentID, std::string studentName, std::string studentCNIC, std::string phoneNumber, std::string school, std::string gender, short int sem, int roomNumber)
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

void Hostel::promoteAllStudents()
{
    for (auto &student : studentList)
    {
        student.setSem(student.getSem() + 1);
        if (student.getSem() > 8)
        {
            student.setSem(8);
        }
    }
}

void Hostel::deleteStudent(int studentID)
{
    for (int i = 0; i < studentList.size(); i++)
    {
        if (studentList[i].getStudentID() == studentID)
        {
            studentList.erase(studentList.begin() + i);
            break;
        }
    }

    for (auto &room : roomList)
    {
        for (int i = 0; i < room.getStudentIDList().size(); i++)
        {
            if (room.getStudentIDList()[i] == studentID)
            {
                room.removeStudent(studentID);
                break;
            }
        }
    }
}

std::string Hostel::getAllStudentsTable()
{

    TextTable studentTable('-', '|', '+');
    studentTable.add("Student ID");
    studentTable.add("Student Name");
    studentTable.add("Student CNIC");
    studentTable.add("Phone Number");
    studentTable.add("School");
    studentTable.add("Gender");
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
        studentTable.add(student.getGender());
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
    std::string s;
    std::ostringstream os;
    os << studentTable;
    s = os.str();
    return s;
}

// ------------------------ Invoice ------------------------

bool Hostel::checkIfStudentExists(int studentID)
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

void Hostel::addInvoice(int studentID, std::string invoiceDate, std::string dueDate, double amountDue, double amountAfterDue)
{

    if (!checkIfStudentExists(studentID))
    {
        std::cout << "Student does not exist!" << std::endl;
        return;
    }

    Invoice invoice(invoiceIDTrack++, studentID, invoiceDate, dueDate, amountDue, amountAfterDue);
    invoicesList.push_back(invoice);
}

void Hostel::addInvoicesForAllStudents(std::string invoiceDate, std::string dueDate, double amountDue, double amountAfterDue)
{
    for (auto &student : studentList)
    {
        Invoice invoice(invoiceIDTrack++, student.getStudentID(), invoiceDate, dueDate, amountDue, amountAfterDue);
        invoicesList.push_back(invoice);
    }
}

bool Hostel::checkIfInvoiceExists(int invoiceID)
{
    for (auto &invoice : invoicesList)
    {
        if (invoice.getInvoiceID() == invoiceID)
        {
            return true;
        }
    }
    return false;
}

bool Hostel::checkIfInvoiceIsPaid(int invoiceID)
{
    for (auto &invoice : invoicesList)
    {
        if (invoice.getInvoiceID() == invoiceID)
        {
            return invoice.getStatus();
        }
    }
    return false;
}

void Hostel::updateInvoiceStatus(int invoiceID, bool status)
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
            return;
        }
    }

    std::cout << "----------- Invoice does not exist! -----------------" << std::endl;
    return;
}

std::string Hostel::getAllInvoicesTable()
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

    std::sort(invoicesList.begin(), invoicesList.end(), [](Invoice a, Invoice b)
              {
        // First, sort by isPaid (false comes before true)
        if (a.getStatus() != b.getStatus()) {
            return a.getStatus() < b.getStatus();
        }

        // If isPaid is the same, sort by invoiceID
        return a.getInvoiceID() > b.getInvoiceID(); });

    for (auto &invoice : invoicesList)
    {
        invoiceTable.add(std::to_string(invoice.getInvoiceID()));
        invoiceTable.add(std::to_string(invoice.getStudentID()));
        if (!checkIfStudentExists(invoice.getStudentID()))
        {
            invoiceTable.add("Student Deleted");
        }
        else
        {
            for (auto student : studentList)
            {
                if (student.getStudentID() == invoice.getStudentID())
                {
                    invoiceTable.add(student.getStudentName());
                    break;
                }
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
    std::string s;
    std::ostringstream os;
    os << invoiceTable;
    s = os.str();
    return s;
}

std::string Hostel::getAllInvoicesByStudentID(int studentID, bool status)
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

    std::sort(invoicesList.begin(), invoicesList.end(), [](Invoice a, Invoice b)
              {
            // First, sort by isPaid (false comes before true)
            if (a.getStatus() != b.getStatus()) {
                return a.getStatus() < b.getStatus();
            }

            // If isPaid is the same, sort by invoiceID
            return a.getInvoiceID() > b.getInvoiceID(); });

    for (auto &invoice : invoicesList)
    {
        if (invoice.getStudentID() == studentID && invoice.getStatus() == status)
        {
            invoiceTable.add(std::to_string(invoice.getInvoiceID()));
            invoiceTable.add(std::to_string(invoice.getStudentID()));

            if (!checkIfStudentExists(studentID))
            {
                invoiceTable.add("Student Deleted");
            }
            else
            {
                for (auto student : studentList)
                {
                    if (student.getStudentID() == invoice.getStudentID())
                    {
                        invoiceTable.add(student.getStudentName());
                        break;
                    }
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
    std::string s;
    std::ostringstream os;
    os << invoiceTable;
    s = os.str();
    return s;
}

std::string Hostel::getAllInvoicesByInvoiceID(unsigned int InvoiceID)
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

    std::sort(invoicesList.begin(), invoicesList.end(), [](Invoice a, Invoice b)
              {
            // First, sort by isPaid (false comes before true)
            if (a.getStatus() != b.getStatus()) {
                return a.getStatus() < b.getStatus();
            }

            // If isPaid is the same, sort by invoiceID
            return a.getInvoiceID() > b.getInvoiceID(); });

    for (auto &invoice : invoicesList)
    {
        if (invoice.getInvoiceID() == InvoiceID)
        {
            invoiceTable.add(std::to_string(invoice.getInvoiceID()));
            invoiceTable.add(std::to_string(invoice.getStudentID()));
            if (!checkIfStudentExists(invoice.getStudentID()))
            {
                invoiceTable.add("Student Deleted");
            }
            else
            {
                for (auto student : studentList)
                {
                    if (student.getStudentID() == invoice.getStudentID())
                    {
                        invoiceTable.add(student.getStudentName());
                        break;
                    }
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
    std::string s;
    std::ostringstream os;
    os << invoiceTable;
    s = os.str();
    return s;
}

std::string Hostel::getAllInvoicesByStatus(bool status)
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

    std::sort(invoicesList.begin(), invoicesList.end(), [](Invoice a, Invoice b)
              {
            // First, sort by isPaid (false comes before true)
            if (a.getStatus() != b.getStatus()) {
                return a.getStatus() < b.getStatus();
            }

            // If isPaid is the same, sort by invoiceID
            return a.getInvoiceID() > b.getInvoiceID(); });

    for (auto &invoice : invoicesList)
    {
        if (invoice.getStatus() == status)
        {
            invoiceTable.add(std::to_string(invoice.getInvoiceID()));
            invoiceTable.add(std::to_string(invoice.getStudentID()));
            if (!checkIfStudentExists(invoice.getStudentID()))
            {
                invoiceTable.add("Student Deleted");
            }
            else
            {
                for (auto student : studentList)
                {
                    if (student.getStudentID() == invoice.getStudentID())
                    {
                        invoiceTable.add(student.getStudentName());
                        break;
                    }
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
    std::string s;
    std::ostringstream os;
    os << invoiceTable;
    s = os.str();
    return s;
}