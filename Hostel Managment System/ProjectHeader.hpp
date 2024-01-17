#pragma once

// -------- Includes for Hostel Test
#include <iostream>
#include <string>
#include <vector>
#include "hostel.h"

namespace ProjectInfo
{
	// Project Info
	const char* appName = "Hostel Management System";

	// Defaults for file handling
	std::string fileName = "HostelData.txt";
	std::string DefaultHostelInfo = R"({"hostel_name":"Hostelo","hostel_email":"example@gmail.com","hostel_phone_number":"1234-1234567","hostel_address":"Islamabad","students":[null],"rooms":[null],"staffs":[null],"invoices":[null]})";
}

// Includes For GUI APP
#include "raylib.h"
#include "variabledefinitions.h"
#include "helperfunctions.h"

// Include for GUI elements Classes
#include "GUIElementsClasses.hpp"

// Includes for MultiThreading
#include <future>
#include <chrono>
#include <thread>

// Include for Custom Library
#include "flavortext.h"

// Includes for File Handling
#include "nlohmann/json.hpp"
#include "FileReader.h"

// -------- Includes for Screen layers
#include "loadingScreen.h"
#include "fatalErrorScreen.h"