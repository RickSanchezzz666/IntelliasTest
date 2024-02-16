#include "timeTrackingReport.hpp"
#include "loggerModule.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <chrono>
#include <ctime>

TimeTrackingReport::TimeTrackingReport(const std::string& fileName) { 
	try
	{
		__readFile(fileName);
	}
	catch (const std::exception& err) {
		throw err;
	}
}

void TimeTrackingReport::__readFile(const std::string& fileName) {
	try
	{
		__fileName = fileName + ".csv";

		std::ifstream file(fileName + ".csv");

		if (!file.is_open()) {
			throw std::runtime_error("Unable to open file!");
		}

		std::string header;
		std::getline(file, header);

		__delimiter  = __determineDelimiter(header);

		auto startParsing = std::chrono::steady_clock::now();

		std::string line;
		while (std::getline(file, line)) {
			std::vector<std::string> row;
			std::stringstream ss(line);
			std::string token;
			while (std::getline(ss, token, __delimiter)) {
				row.push_back(token);
			}
			__fileDataStorage.push_back(row);
		}

		file.close();

		auto endParsing = std::chrono::steady_clock::now();
		auto parsingDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endParsing - startParsing);

		std::string message = "User read file with name: " + fileName + ".csv succesfully!";
		Logger::logAction("File Read", message, "SUCCESS", parsingDuration);

		__getReport(__fileDataStorage);
	}
	catch (const std::exception& err) {
		std::cerr << "Error occured: " << err.what() << std::endl;
		std::string message = "User attempted to read the file named: " + fileName + ".csv, but the Error occured: " + err.what();
		Logger::logAction("File Read", message, "FAILED");
		throw err;
	}
}

char TimeTrackingReport::__determineDelimiter(const std::string& header) {
	char delimiters[] = { ',', ';', ' ', '\t', '.', '|', ':' };
	for (int i = 0; i < (sizeof(delimiters) / sizeof(delimiters[0])); i++) {
		if (header.find(delimiters[i]) != std::string::npos) {
			return delimiters[i];
		}
	}

	return 0;
}

void TimeTrackingReport::__getReport(std::vector<std::vector<std::string>>& data) {
	try
	{
		if (data.empty()) {
			throw std::runtime_error("Report is empty!");
		}

		auto startParsing = std::chrono::steady_clock::now();

		for (auto& elem : data) {
			std::string outputLine;
			std::string date = __convertDate(elem[6]);

			bool foundStatus = false;

			if (__outputReport.empty()) {
				outputLine = elem[0] + __delimiter + date + __delimiter + elem[7];
				__outputReport.push_back(outputLine);
			}
			else {
				for (auto& line : __outputReport) {
					if (line.find(elem[0]) != std::string::npos && line.find(date) != std::string::npos) {
						std::vector<std::string> row;
						std::stringstream ss(line);
						std::string token;
						while (std::getline(ss, token, __delimiter)) {
							row.push_back(token);
						}
						int hoursSpent = std::stoi(row[2]) + std::stoi(elem[7]);
						line = row[0] + __delimiter + row[1] + __delimiter + std::to_string(hoursSpent);
						foundStatus = true;
						break;
					}
				}

				if(!foundStatus) {
					outputLine = elem[0] + __delimiter + date + __delimiter + elem[7];
					__outputReport.push_back(outputLine);
				}
			}
		}

		auto endParsing = std::chrono::steady_clock::now();
		auto parsingDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endParsing - startParsing);

		std::string message = "User got report from file named: " + __fileName + ".csv successfuly!";
		Logger::logAction("Get Report", message, "SUCCESS", parsingDuration);

	}
	catch (const std::exception& err)
	{
		std::cerr << "Error occured: " << err.what() << std::endl;
		std::string message = "User attempted to get report from file named: " + __fileName + ".csv, but the Error occured: " + err.what();
		Logger::logAction("Get Report", message, "FAILED");
		return;
	}
}

std::string TimeTrackingReport::__convertDate(const std::string& date) {
	std::string finalDate;
	std::string year = date.substr(0, 4);
	std::string month = __getDateString(date.substr(5, 2));
	finalDate = month + " " + year;
	return finalDate;
}

std::string TimeTrackingReport::__getDateString(const std::string& month) {
	int monthInt = std::stoi(month);
	switch (monthInt) {
	case 1:
		return "January";
	case 2:
		return "February";
	case 3:
		return "March";
	case 4:
		return "April";
	case 5:
		return "May";
	case 6:
		return "June";
	case 7:
		return "July";
	case 8:
		return "August";
	case 9:
		return "September";
	case 10:
		return "October";
	case 11:
		return "November";
	case 12:
		return "December";
	default:
		return "Unknown month";
	}
}


void TimeTrackingReport::printInitialData() {
	try
	{
		std::cout << "Your initial uploaded report is: \n\n";

		std::ifstream file(__fileName);

		if (!file.is_open()) {
			throw std::runtime_error("Unable to open file!");
		}
		std::string line;
		while (std::getline(file, line)) {
			std::cout << line << std::endl;
		}

		file.close();
	}
	catch (const std::exception& err)
	{
		std::cerr << "Error occured: " << err.what() << std::endl;
		return;
	}
}

void TimeTrackingReport::printReport() {
	std::cout << "Your final report is: \n\n";
	std::string header = "Name" + std::string (1, __delimiter) + "Month" + std::string(1, __delimiter) + "Total hours";
	std::cout << header << std::endl;
	for (auto& record : __outputReport) {
		std::cout << record << std::endl;
	}
}

bool TimeTrackingReport::__checkExistence(const std::string& fileName) {
	std::ifstream outputFile(fileName + ".csv");
	if (outputFile) return true;
	return false;
}

void TimeTrackingReport::exportReport(const std::string& fileName) {
	try
	{
		std::string name = fileName;
		if (__checkExistence(name)) {
			std::cout << "\nFile with this name already exist!\nDo you wanna change it or override existing?\n1. Change name\n2. Override\nEnter: ";
			bool session = true;
			while (session) {
				int action;
				std::cin >> action;
				switch (action)
				{
				case 1:
					std::cout << "\nEnter new name: ";
					std::cin >> name;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					session = false;
					break;
				case 2:
					std::cout << "\nYou choosed to override existing!\n";
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					session = false;
					break;
				default:
					std::cerr << "\nWrong action! Try again!\n1. Change name\n2. Override\nEnter: ";
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					break;
				}
			}
		}

		auto startParsing = std::chrono::steady_clock::now();

		std::ofstream outputFile(name + ".csv");

		if (!outputFile.is_open()) {
			throw std::runtime_error("Unable to open file for writing!");
		}

		std::string header = "Name" + std::string(1, __delimiter) + "Month" + std::string(1, __delimiter) + "Total hours";

		outputFile << header << "\n";

		for (auto& record : __outputReport) {
			outputFile << record << "\n";
		}

		outputFile.close();

		auto endParsing = std::chrono::steady_clock::now();
		auto parsingDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endParsing - startParsing);

		std::cout << "\nSuccessfully created Time Tracking Report! Name of a file: " + name + ".csv\n";

		std::string message = "User successfully exported report to file named: " + name + ".csv";
		Logger::logAction("Get Report", message, "SUCCESS", parsingDuration);

	}
	catch (const std::exception& err)
	{
		std::cerr << "Error occured: " << err.what() << std::endl;
		std::string message = "User attempted to get export report from file named: " + __fileName + ".csv, but the Error occured: " + err.what();
		Logger::logAction("Export Report", message, "FAILED");
		return;
	}
}