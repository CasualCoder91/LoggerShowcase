#include "Logger.h"

Logger::Logger(const std::string& filename) : logFilePath(filename) {

    // Try to open file in read (create it if it doesn't exist)
    std::ifstream reader(logFilePath, std::ios::in);

    if (!reader.is_open()) {
        // If file doesn't exist, we open in write mode to create it.
        logFile.open(logFilePath, std::ios::app | std::ios::binary);

        if (logFile.is_open()) {
            // If file creation is successful, write the header for CSV.
            logFile << "TimeStamp;Type;Title;Details" << std::endl;
        }
        else {
            std::cerr << "Failed to create the log file!" << std::endl;
            return;
        }
    }
    else {
        // If file exists, we can read its entries
        readLogEntries();

        // Reopen the file in append mode to write new entries
        logFile.open(logFilePath, std::ios::app | std::ios::binary);
    }

    // Keep logFile open for writing throughout the program
    // We don't close it here, so it remains open for logging operations
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::log(const std::string& type, const std::string& title, const std::string& details) {
    LogEntry newEntry(type, title, details);
    log(newEntry);
}

// Add a new log entry and write it to the file
void Logger::log(const LogEntry& newEntry) {
    logEntries.push_back(newEntry);

    logFile << newEntry.toCsv() << "\n"; // Append new log entry
    logFile.flush(); // Ensure data is written immediately
}

void Logger::readLogEntries() {
    std::ifstream inputFile(logFilePath, std::ios::in);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open log file for reading!" << std::endl;
        return;
    }

    // Clear previous entries from memory before reading
    logEntries.clear();

    std::string line;

    // Skip the first line (header)
    std::getline(inputFile, line);

    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string timeStamp, type, title, details;

        if (std::getline(ss, timeStamp, ';') &&
            std::getline(ss, type, ';') &&
            std::getline(ss, title, ';') &&
            std::getline(ss, details)) {
            logEntries.push_back(LogEntry(timeStamp, type, title, details));
        }
    }

    inputFile.close();
}

// Method to print log entries
void Logger::print(bool groupBy, const std::string& groupKey, const std::string& filterValue)
{
    if (groupBy) {
        // Aggregate logs
        std::unordered_map<std::string, int> countMap;

        for (const auto& log : logEntries) {
            std::string key = (groupKey == "Title") ? log.title : log.type;

            // Apply optional filter
            if (filterValue.empty() || key == filterValue) {
                countMap[key]++;
            }
        }

        // Print grouped data
        std::cout << "\nAggregated Log Data (Grouped by " << groupKey << ")\n";
        std::cout << "--------------------------------------\n";
        for (const auto& pair : countMap) {
            std::cout << pair.first << ": " << pair.second << " occurrences\n";
        }
        std::cout << "--------------------------------------\n";
    }
    else {
        // Print logs individually
        std::cout << "\nLog Entries:\n";
        std::cout << "--------------------------------------\n";
        for (const auto& log : logEntries) {
            // Apply optional filter
            if (filterValue.empty() || log.type == filterValue || log.title == filterValue) {
                std::cout << log.timeStamp << " [" << log.type << "] "
                    << log.title << ": " << log.details << "\n";
            }
        }
        std::cout << "--------------------------------------\n";
    }
}

void Logger::deleteLogs()
{
    // Clear the log entries in memory
    logEntries.clear();
    // delete the Logfile
    remove(logFilePath.c_str());
}
