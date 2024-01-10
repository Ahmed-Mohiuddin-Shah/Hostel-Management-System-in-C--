#include <iostream>

class Staff
{
private:
    int staffID;
    std::string staffName;
    std::string staffCNIC;
    std::string phoneNumber;
    std::string role;

public:
    Staff(int staffID, std::string staffName, std::string staffCNIC, std::string phoneNumber, std::string role);

    void setStaffID(int staffID);

    void setStaffName(std::string staffName);

    void setStaffCNIC(std::string staffCNIC);

    void setPhoneNumber(std::string phoneNumber);

    void setRole(std::string role);

    int getStaffID();

    std::string getStaffName();

    std::string getStaffCNIC();

    std::string getPhoneNumber();

    std::string getRole();
};