#pragma once

#include <string>
#include <vector>

class TimeTrackingReport {
private:

	std::string __fileName;

	std::vector<std::vector<std::string>> __fileDataStorage;
	std::vector<std::string> __outputReport;

	char __delimiter = ';';

	void __readFile(const std::string& fileName);

	char __determineDelimiter(const std::string& header);

	void __getReport(std::vector<std::vector<std::string>>& data);

	std::string __convertDate(const std::string& date);

	std::string __getDateString(const std::string& month);

	bool __checkExistence(const std::string& fileName);
	

public:
	TimeTrackingReport(const std::string& fileName);

	void printInitialData();

	void printReport();

	void exportReport(const std::string& fileName);
};