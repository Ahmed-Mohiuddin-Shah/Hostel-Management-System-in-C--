#pragma once

// Includes For GUI APP
#include "raylib.h"
#include "variabledefinitions.h"
#include "helperfunctions.h"

// Includes for File Handling
#include "FileReader.h"

// -------- Includes for Hostel Test
#include <iostream>
#include <string>
#include <vector>
#include "hostel.h"

namespace ProjectInfo
{
	// Defaults for file handling
	std::string fileName = "HostelData.txt";
	std::string DefaultHostelInfo = R"({"hostel_name":"Hostelo","hostel_email":"example@gmail.com","hostel_phone_number":"1234-1234567","hostel_address":"Islamabad","students":[null],"rooms":[null],"staffs":[null],"invoices":[null]})";
}