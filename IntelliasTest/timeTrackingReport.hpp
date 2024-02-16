#pragma once

#include <string>
#include <vector>

class TimeTrackingReport {
private:
	std::vector<std::vector<std::string>> __fileDataStorage;
	void __readFile(const std::string& fileName);

public:
	TimeTrackingReport(const std::string& fileName);

	void getReport();

	void printReport();
};