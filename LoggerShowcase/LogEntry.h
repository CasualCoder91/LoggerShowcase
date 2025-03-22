#ifndef LOG_ENTRY_H
#define LOG_ENTRY_H

#include <string>
#include <sstream>  // Include for std::ostringstream
#include <iomanip>  // Include for std::put_time

class LogEntry {
public:
    std::string timeStamp;
    std::string type;
    std::string title;
    std::string details;

    // Constructor to initialize the LogEntry
    LogEntry(const std::string& timeStamp, const std::string& type, const std::string& title, const std::string& details);

    // Constructor to initialize the LogEntry
    LogEntry(const std::string& type, const std::string& title, const std::string& details);

    /// <summary>
    /// Convert the LogEntry to a CSV formatted string.
    /// </summary>
    std::string toCsv() const;

    /// <summary>
    /// Print the LogEntry to the console.
    /// </summary>
    void print() const;

private:
    std::string getCurrentTimestamp();
};

#endif // LOG_ENTRY_H