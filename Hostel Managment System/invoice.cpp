#include "invoice.h"

Invoice::Invoice(int invoiceID, int studentID, std::string invoiceDate, std::string dueDate, unsigned int amountDue, unsigned int amountAfterDue)
{
    this->invoiceID = invoiceID;
    this->studentID = studentID;
    this->invoiceDate = invoiceDate;
    this->dueDate = dueDate;
    this->status = UNPAID;
    this->amountDue = amountDue;
    this->amountAfterDue = amountAfterDue;
}

Invoice::Invoice(int invoiceID, int studentID, std::string invoiceDate, std::string dueDate, bool status, unsigned int amountDue, unsigned int amountAfterDue)
{
    this->invoiceID = invoiceID;
    this->studentID = studentID;
    this->invoiceDate = invoiceDate;
    this->dueDate = dueDate;
    this->status = status;
    this->amountDue = amountDue;
    this->amountAfterDue = amountAfterDue;
}

void Invoice::setInvoiceID(int invoiceID)
{
    this->invoiceID = invoiceID;
}

void Invoice::setStudentID(int studentID)
{
    this->studentID = studentID;
}

void Invoice::setInvoiceDate(std::string invoiceDate)
{
    this->invoiceDate = invoiceDate;
}

void Invoice::setDueDate(std::string dueDate)
{
    this->dueDate = dueDate;
}

void Invoice::setStatus(bool status)
{
    this->status = status;
}

void Invoice::setAmountDue(unsigned int amountDue)
{
    this->amountDue = amountDue;
}

void Invoice::setAmountAfterDue(unsigned int amountAfterDue)
{
    this->amountAfterDue = amountAfterDue;
}

int Invoice::getInvoiceID()
{
    return invoiceID;
}

int Invoice::getStudentID()
{
    return studentID;
}

std::string Invoice::getInvoiceDate()
{
    return invoiceDate;
}

std::string Invoice::getDueDate()
{
    return dueDate;
}

bool Invoice::getStatus()
{
    return status;
}

unsigned int Invoice::getAmountDue()
{
    return amountDue;
}

unsigned int Invoice::getAmountAfterDue()
{
    return amountAfterDue;
}