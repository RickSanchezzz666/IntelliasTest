#include "timeTrackingReport.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

TimeTrackingReport::TimeTrackingReport(const std::string& fileName) { __readFile(fileName); }

void TimeTrackingReport::__readFile(const std::string& fileName) {
	try
	{
		std::ifstream file(fileName);

		if (!file.is_open()) {
			throw ("Unable to open file!");
			return;
		}

		std::vector<std::string> tempDataStorage;

		std::string line;
		bool skipHeader = true;
		while (std::getline(file, line)) {
			if (skipHeader) {
				skipHeader = false;
				continue;
			}
			tempDataStorage.push_back(line);
		}

		for (auto& elem : tempDataStorage) {
			std::vector<std::string> row;
			std::stringstream ss(elem);
			std::string token;
			while (std::getline(ss, token, ';')) {
				row.push_back(token);
			}
			__fileDataStorage.push_back(row);
		}

		file.close();
	}
	catch (const std::string& e) {
		std::cerr << "Error: " << e << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error occured: " << e.what() << std::endl;
	}
}

void TimeTrackingReport::getReport() {
	std::cout << "success!" << std::endl;
}
