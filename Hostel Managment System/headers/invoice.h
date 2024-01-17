#include <iostream>

class Invoice
{
private:
    int invoiceID;
    int studentID;
    std::string invoiceDate;
    std::string dueDate;
    bool status;
    double amountDue;
    double amountAfterDue;

public:
    enum Status
    {
        PAID = true,
        UNPAID = false
    };

    Invoice(int invoiceID, int studentID, std::string invoiceDate, std::string dueDate, double amountDue, double amountAfterDue);

    void setInvoiceID(int invoiceID);

    void setStudentID(int studentID);

    void setInvoiceDate(std::string invoiceDate);

    void setDueDate(std::string dueDate);

    void setStatus(bool status);

    void setAmountDue(double amountDue);

    void setAmountAfterDue(double amountAfterDue);

    int getInvoiceID();

    int getStudentID();

    std::string getInvoiceDate();

    std::string getDueDate();

    bool getStatus();

    double getAmountDue();

    double getAmountAfterDue();
};