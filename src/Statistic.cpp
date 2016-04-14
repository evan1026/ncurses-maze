#include "Statistic.h"
#include "TypeMismatchException.h"

#include <string>
#include <sstream>
#include <ctime>

namespace {
    void printTime(time_t t, std::ostream& os) {
        auto timeinfo = *localtime(&t);
        char buf[80];

        strftime(buf,80,"%m-%d-%Y %I:%M:%S",&timeinfo);
        os << buf;
    }
}

std::ostream& operator<<(std::ostream& os, Statistic val) {
    if (val.checkType<bool>()) {
        os << (val.get<bool>() ? "true" : "false");
    } else if (val.checkType<time_t>()) {
        printTime(val.get<time_t>(), os);
    } else if (val.checkType<void>()) {
        os << "void-type";
    } else {
        os << val.value;
    }

    return os;
}
