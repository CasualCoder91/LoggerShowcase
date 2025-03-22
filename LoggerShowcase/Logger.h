#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "LogEntry.h"

class Logger {
private:
    std::string logFilePath;

    // Keep open for writing!
    std::ofstream logFile;
    std::vector<LogEntry> logEntries;

    void readLogEntries();

public:
    Logger(const std::string& filename);
    ~Logger();

    /// <summary>
    /// Add a new log entry to the log file.
    /// </summary>
    /// <param name="type">Type.</param>
    /// <param name="title">Title.</param>
    /// <param name="details">Details.</param>
    void log(const std::string& type, const std::string& title, const std::string& details);

    /// <summary>
    /// Add a new log entry to the log file.
    /// </summary>
    /// <param name="newEntry">The new entry.</param>
    void log(const LogEntry& newEntry);

    /// <summary>
    /// Print log entries to console.
    /// </summary>
    /// <param name="groupBy">If the data should be grouped.</param>
    /// <param name="groupKey">The column to group by. Possible values: Type, Title</param>
    /// <param name="filterValue">Filter which can be applied to Type/Title</param>
    void print(bool groupBy = false, const std::string& groupKey = "Type", const std::string& filterValue = "");

    /// <summary>
    /// Deletes the log file and Logs in memory.
    /// </summary>
    void deleteLogs();
};

#endif // LOGGER_H
