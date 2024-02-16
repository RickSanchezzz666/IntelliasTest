#include "timeTrackingReport.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <limits>

int main() {
	std::cout << "Welcome to Time Tracking Report application!\nActions available:\n1. Load input Data.\n2. Exit the program!\nChoose: ";
	while (true) {
		int action;
		std::cin >> action;
		switch (action)
		{
		case 1: {
			std::cout << "\nEnter name of the file you want to load (CSV) format!\nIf file is in the same folder as the app is!\nExample: 'example'\nIf the file is not in the same folder, use '../' to navigate to the parent directory.\nExample: '../../IntelliasTest/example'\nEnter: ";
			std::string fileName;
			while (true) {
				std::cin >> fileName;
				if (fileName.empty()) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cerr << "\nFilename can't be empty!\n";
					continue;
				}
				else { break; }

			}
			try
			{
				TimeTrackingReport report(fileName);
				std::cout << "\nSuccessfully loaded file: " + fileName + ".csv";

				while (true) {
					std::cout << "\nChoose next action: \n1. Print initial data\n2. Print Report to console.\n3. Export Report to CSV file.\n4. Exit the program!\nChoose: ";
					int actionReport;
					std::cin >> actionReport;
					switch (actionReport) {
					case 1:
						report.printInitialData();
						break;
					case 2:
						report.printReport();
						break;
					case 3:
					{
						std::cout << "\nEnter the name of file you want to be exported!\nExample: 'filename'\nEnter: ";
						std::string name;
						while (true) {
							std::cin >> name;
							if (name.empty()) {
								std::cin.clear();
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								std::cerr << "\nFile Name can't be empty!\n";
								continue;
							}
							else { break; }
						}
						report.exportReport(name);
						break;
					}
					case 4:
						std::cout << "\nClosing application...";
						return 0;
					default:
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						std::cerr << "\nWrong action! Try again!\n";
						continue;
					}
				}
			}
			catch (const std::exception& err)
			{
				std::cerr << "File doesn't exist or wasn't found!" << std::endl;
				std::cerr << "Error: " << err.what() << std::endl;
				std::cout << "\nClosing application...";
				return 0;
			}
		}
		case 2:
			std::cout << "\nClosing application...";
			return 0;
		default:
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "\nWrong action! Try again!\n";
			continue;
		}
	}

	std::cin.get();

	return 0;
}