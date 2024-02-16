#pragma once

#include <chrono>
#include <string>

class Logger {
public:
	static void createLogsFile();
	static void clearLogsFile();

	static void logAction(const std::string& action, const std::string& message, const std::string& status, const std::chrono::milliseconds& parsingTime = std::chrono::milliseconds(0));
};