#include "Solve.h"

std::string Solve::timeToString(double timeToPrint, unsigned precision) {
    // return string representation of time with specified precision
    std::ostringstream formatTime;
    formatTime << std::fixed << std::setprecision(precision) << timeToPrint;

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
