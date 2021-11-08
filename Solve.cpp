#include "Solve.h"

std::string Solve::toString(unsigned precision) {
    // return string representation of time with specified precision
    std::ostringstream formatTime;
    formatTime << std::fixed << std::setprecision(precision) << time;
    return formatTime.str();
}
