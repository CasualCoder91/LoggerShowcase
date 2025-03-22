#include "LogEntry.h"
#include <iostream>

// Constructor to initialize the LogEntry
LogEntry::LogEntry(const std::string& timeStamp, const std::string& type, const std::string& title, const std::string& details)
    : timeStamp(timeStamp), type(type), title(title), details(details) {
}

LogEntry::LogEntry(const std::string& type, const std::string& title, const std::string& details)
    : timeStamp(getCurrentTimestamp()), type(type), title(title), details(details) {
}

std::string LogEntry::toCsv() const {
    return timeStamp + ";" + type + ";" + title + ";" + details;
}

// Method to print the log entry
void LogEntry::print() const {
    std::cout << "TimeStamp: " << timeStamp << "\n";
    std::cout << "Type: " << type << "\n";
    std::cout << "Title: " << title << "\n";
    std::cout << "Details: " << details << "\n\n";
}

std::string LogEntry::getCurrentTimestamp() {
    std::time_t now = std::time(nullptr);
    std::tm localTime;
    localtime_s(&localTime, &now);
    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}
