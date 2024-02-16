CC = g++
CXXFLAGS = -std=c++14
OBJECTS = main.o timeTrackingReport.o loggerModule.o
TARGET = trackingReport
LIBS = 

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $(TARGET)

main.o: IntelliasTest/main.cpp IntelliasTest/timeTrackingReport.hpp
	$(CC) $(CXXFLAGS) -c IntelliasTest/main.cpp

timeTrackingReport.o: IntelliasTest/timeTrackingReport.cpp IntelliasTest/timeTrackingReport.hpp
	$(CC) $(CXXFLAGS) -c IntelliasTest/timeTrackingReport.cpp

loggerModule.o: IntelliasTest/loggerModule.cpp IntelliasTest/loggerModule.hpp
	$(CC) $(CXXFLAGS) -c IntelliasTest/loggerModule.cpp

clean:
	rm -f $(OBJECTS) $(TARGET)