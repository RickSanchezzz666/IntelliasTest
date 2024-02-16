#include "timeTrackingReport.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

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

		std::string line;
		bool skipHeader = true;
		while (std::getline(file, line)) {
			if (skipHeader) {
				skipHeader = false;
				continue;
			}
			std::vector<std::string> row;
			std::stringstream ss(line);
			std::string token;
			while (std::getline(ss, token, ';')) {
				row.push_back(token);
			}
			__fileDataStorage.push_back(row);
		}


		file.close();

		__getReport(__fileDataStorage);
	}
	catch (const std::exception& err) {
		std::cerr << "Error occured: " << err.what() << std::endl;
		throw err;
	}
}

void TimeTrackingReport::__getReport(std::vector<std::vector<std::string>> data) {
	try
	{
		if (data.empty()) {
			throw std::runtime_error("Report is empty!");
		}

		for (auto& elem : data) {
			std::string outputLine;
			std::string date = __convertDate(elem[6]);

			bool foundStatus = false;

			if (__outputReport.empty()) {
				outputLine = elem[0] + ";" + date + ";" + elem[7];
				__outputReport.push_back(outputLine);
			}
			else {
				for (auto& line : __outputReport) {
					if (line.find(elem[0]) != std::string::npos && line.find(date) != std::string::npos) {
						std::vector<std::string> row;
						std::stringstream ss(line);
						std::string token;
						while (std::getline(ss, token, ';')) {
							row.push_back(token);
						}
						int hoursSpent = std::stoi(row[2]) + std::stoi(elem[7]);
						line = row[0] + ";" + row[1] + ";" + std::to_string(hoursSpent);
						foundStatus = true;
						break;
					}
				}

				if(!foundStatus) {
					outputLine = elem[0] + ";" + date + ";" + elem[7];
					__outputReport.push_back(outputLine);
				}
			}
		}

	}
	catch (const std::exception& err)
	{
		std::cerr << "Error occured: " << err.what() << std::endl;
		return;
	}
}

std::string TimeTrackingReport::__convertDate(std::string date) {
	std::string finalDate;
	std::string year = date.substr(0, 4);
	std::string month = __getDateString(date.substr(5, 2));
	finalDate = month + " " + year;
	return finalDate;
}

std::string TimeTrackingReport::__getDateString(std::string month) {
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
	}
	catch (const std::exception& err)
	{
		std::cerr << "Error occured: " << err.what() << std::endl;
		return;
	}
}

void TimeTrackingReport::printReport() {
	std::cout << "Your final report is: \n\n";
	std::string header = "Name;Month;Total hours";
	std::cout << header << std::endl;
	for (auto& record : __outputReport) {
		std::cout << record << std::endl;
	}
}

void TimeTrackingReport::exportReport(const std::string& fileName) {
	try
	{
		std::ofstream outputFile(fileName + ".csv");
		if (!outputFile.is_open()) {
			throw std::runtime_error("Unable to open file for writing!");
		}

		std::string header = "Name;Month;Total hours";

		outputFile << header << "\n";

		for (auto& record : __outputReport) {
			outputFile << record << "\n";
		}

		outputFile.close();

		std::cout << "\nSuccessfully created Time Tracking Report!\n";

	}
	catch (const std::exception& err)
	{
		std::cerr << "Error occured: " << err.what() << std::endl;
		return;
	}
}