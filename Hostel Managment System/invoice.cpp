#include "invoice.h"

Invoice::Invoice(int invoiceID, int studentID, std::string invoiceDate, std::string dueDate, double amountDue, double amountAfterDue)
{
    this->invoiceID = invoiceID;
    this->studentID = studentID;
    this->invoiceDate = invoiceDate;
    this->dueDate = dueDate;
    this->status = UNPAID;
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

void Invoice::setAmountDue(double amountDue)
{
    this->amountDue = amountDue;
}

void Invoice::setAmountAfterDue(double amountAfterDue)
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

double Invoice::getAmountDue()
{
    return amountDue;
}

double Invoice::getAmountAfterDue()
{
    return amountAfterDue;
}