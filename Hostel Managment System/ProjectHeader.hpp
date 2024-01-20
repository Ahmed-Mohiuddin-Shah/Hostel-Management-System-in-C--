#pragma once

#define _CRT_SECURE_NO_WARNINGS

// --------------------------
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <algorithm>

// Includes for MultiThreading
#include <future>
#include <chrono>
#include <thread>

// Includes for File Handling
#include "nlohmann/json.hpp"
#include "FileReader.h"

using JSON = nlohmann::json;

namespace ProjectInfo
{
	// Project Info
	const char* appName = "Hostel Management System";

	// Defaults for file handling
	std::string fileName = "HostelData.json";
}

// Include for Hostel Class
#include "hostel.h"

Hostel hostelInstance;

// Includes For GUI APP
#include "raylib.h"
#include "variabledefinitions.h"
#include "helperfunctions.h"

// Include for GUI elements Classes
#include "GUIElementsClasses.hpp"

// Include for Custom Library
#include "flavortext.h"

// Includes for Screen layers
#include "overlay.h"
#include "loadingScreen.h"
#include "fatalErrorScreen.h"
#include "createNewHostelScreen.h"
#include "homeScreen.h"
#include "hostelDetailsScreen.h"
#include "exitScreen.h"
#include "addStudentScreen.h"
#include "addRoomScreen.h"
#include "studentDetailsScreen.h"
#include "roomDetailsScreen.h"
#include "staffDetailsScreen.h"
#include "displayInvoicesScreen.h"
#include "addStaffScreen.h"
#include "removeStaffScreen.h"
#include "promoteStudentsScreen.h"
#include "generateInvoicesScreen.h"
#include "getSpecificInvoiceScreen.h"
#include "markInvoicePaidScreen.h"