#pragma once

#include <iostream>
#include <folly/json.h>
#include <folly/dynamic.h>
#include "FileReader.h"

namespace ProjectInfo
{
	std::string fileName = "HostelData.txt";
	std::string DefaulHostelInfo = R"({"hostel_name":"Hostelo","hostel_email":"example@gmail.com","hostel_address":"Islamabad","students":[null],"rooms":[null],"staffs":[null],"invoices":[null]})";
}