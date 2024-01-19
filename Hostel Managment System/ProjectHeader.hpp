#pragma once

// -------- Includes for Hostel Test
#include <iostream>
#include <string>
#include <vector>

// Includes for File Handling
#include "nlohmann/json.hpp"
#include "FileReader.h"

using JSON = nlohmann::json;

namespace ProjectInfo
{
	// Project Info
	const char* appName = "Hostel Management System";

	// Defaults for file handling
	std::string fileName = "HostelData.txt";
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

// Include for Hostel Class
#include "hostel.h"

// Includes for Screen layers
#include "overlay.h"
#include "loadingScreen.h"
#include "fatalErrorScreen.h"
#include "createNewHostelScreen.h"