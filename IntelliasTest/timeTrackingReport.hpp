#pragma once

#include <string>
#include <vector>

class TimeTrackingReport {
private:

	std::string __fileName;

	std::vector<std::vector<std::string>> __fileDataStorage;
	std::vector<std::string> __outputReport;

	void __readFile(const std::string& fileName);

	void __getReport(std::vector<std::vector<std::string>> data);

	std::string __convertDate(std::string date);

	std::string __getDateString(std::string month);

public:
	TimeTrackingReport(const std::string& fileName);

	void printInitialData();

	void printReport();

	void exportReport(const std::string& fileName);
};