#include "loggerModule.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <ctime>

void Logger::createLogsFile() {
	try
	{
		std::ofstream logsFile("logs.csv", std::ios::app);

		if (!logsFile) {
			if (!logsFile.is_open()) {
				throw std::runtime_error("Unable to create file!");
			}

			const std::string header = "Action; LogDescription; ParsingTime; Date; Status\n";
			logsFile << header;

			logsFile.close();
			return;
		} 
		throw std::logic_error("Logs file already exist!");
		
	}
	catch (const std::exception& err) {
		std::cerr << "Error occured: " << err.what() << std::endl;
		return;
	}
}

void Logger::clearLogsFile() {
	try
	{
		std::ofstream logsFile("logs.csv", std::ios::trunc);

		if (logsFile) {
			if (!logsFile.is_open()) {
				throw std::runtime_error("Unable to open a file!");
			}

			std::ofstream logsFile("logs.csv", std::ios::app);

			const std::string header = "Action; LogDescription; ParsingTime; Date; Status\n";
			logsFile << header;

			logsFile.close();
			return;
		}
		throw std::logic_error("Logs file doesn't exist!");

	}
	catch (const std::exception& err) {
		std::cerr << "Error occured: " << err.what() << std::endl;
		return;
	}
}

void Logger::logAction(const std::string& action, const std::string& message, const std::string& status, const std::chrono::milliseconds& parsingTime) {
	try
	{
		std::ofstream logsFile("logs.csv", std::ios::app);

		std::time_t currentTime = std::time(nullptr);

		std::tm localTime;

		localtime_s(&localTime, &currentTime);

		std::string currentDate = std::to_string(localTime.tm_year + 1900) + "-" + std::to_string(localTime.tm_mon + 1) + "-" + std::to_string(localTime.tm_mday) + " " + std::to_string(localTime.tm_hour) + ":" + std::to_string(localTime.tm_min);

		if (logsFile) {
			if (!logsFile.is_open()) {
				throw std::runtime_error("Unable to open a file!");
			}

			std::string log = action + "; " + message + "; " + std::to_string(parsingTime.count()) + " msec; " + currentDate + "; " + status + "\n";
			
			logsFile << log;

			logsFile.close();
			return;
		}
		throw std::logic_error("Logs file doesn't exist!");

	}
	catch (const std::exception& err) {
		std::cerr << "Error occured: " << err.what() << std::endl;
		return;
	}
}
