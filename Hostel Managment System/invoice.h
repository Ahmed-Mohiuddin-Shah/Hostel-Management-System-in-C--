#include <iostream>

class Invoice
{
private:
    int invoiceID;
    int studentID;
    std::string invoiceDate;
    std::string dueDate;
    bool status;
    unsigned int amountDue;
    unsigned int amountAfterDue;

public:
    enum Status
    {
        PAID = true,
        UNPAID = false
    };

    Invoice(int invoiceID, int studentID, std::string invoiceDate, std::string dueDate, unsigned int amountDue, unsigned int amountAfterDue);

    Invoice(int invoiceID, int studentID, std::string invoiceDate, std::string dueDate, bool status, unsigned int amountDue, unsigned int amountAfterDue);

    void setInvoiceID(int invoiceID);

    void setStudentID(int studentID);

    void setInvoiceDate(std::string invoiceDate);

    void setDueDate(std::string dueDate);

    void setStatus(bool status);

    void setAmountDue(unsigned int amountDue);

    void setAmountAfterDue(unsigned int amountAfterDue);

    int getInvoiceID();

    int getStudentID();

    std::string getInvoiceDate();

    std::string getDueDate();

    bool getStatus();

    unsigned int getAmountDue();

    unsigned int getAmountAfterDue();
};