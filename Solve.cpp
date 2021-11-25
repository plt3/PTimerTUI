#include "Solve.h"

std::string Solve::timeToString(double timeToPrint, unsigned precision) {
    // return string representation of time with specified precision
    std::ostringstream formatTime;
    formatTime << std::fixed << std::setprecision(precision) << timeToPrint;
    return formatTime.str();
}
