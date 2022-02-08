#include "Solve.h"

void Solve::setTimestamp(time_t toSet) {
    if (toSet != 0) {
        timestamp = toSet;
    } else {
        // set timestamp to current time if no argument provided
        timestamp = std::chrono::system_clock::to_time_t(
            std::chrono::system_clock::now());
    }
}

std::string Solve::timeToString(double timeToPrint, unsigned precision) {
    // return string representation of time with specified precision
    unsigned seconds = timeToPrint;
    unsigned num60s = seconds / 60;
    // essentially take a double mod 60 here
    double secsToPrint = timeToPrint - 60 * num60s;
    unsigned hours = seconds / 3600;
    seconds %= 3600;
    unsigned minutes = seconds / 60;

    std::ostringstream formatTime;
    formatTime << std::setfill('0');
    if (hours) {
        formatTime << hours << ":" << std::setw(2);
    }
    if (hours || minutes) {
        formatTime << minutes << ":" << std::setw(precision + 3);
    }
    formatTime << std::fixed << std::setprecision(precision) << secsToPrint;

    return formatTime.str();
}

std::string Solve::toString(bool showDnfTime, unsigned precision) {
    if (getPenalty() == 1) {
        // +2 penalty so print it as number after penalty with a plus sign at
        // the end
        return timeToString(time + 2, precision) + "+";
    } else if (getPenalty() == 2) {
        // just a DNF
        if (showDnfTime) {
            return "DNF (" + timeToString(time, precision) + ")";
        } else {
            return "DNF";
        }
    } else {
        // no penalty
        return timeToString(time, precision);
    }
}

std::string Solve::timestampToString() {
    std::ostringstream formatTimestamp;
    formatTimestamp << std::put_time(std::localtime(&timestamp), "%Y-%m-%d %X");
    return formatTimestamp.str();
}
