#ifndef TYPE_MISMATCH_EXCEPTION_H
#define TYPE_MISMATCH_EXCEPTION_H

#include <stdexcept>
#include <sstream>

#include "StatisticVal.h"

class TypeMismatchException : public std::runtime_error {
    std::string expected, got, other;

public:
    TypeMismatchException(std::string e, std::string g, int l, std::string f) : std::runtime_error("Type Mismatch"), expected(e), got(g) {
        std::stringstream ss;
        ss << " at line " << l << " in " << f;
        other = ss.str();
    }
    TypeMismatchException(std::string e, std::string g) : std::runtime_error("Type Mismatch"), expected(e), got(g), other("") {}
    const char * what() const _GLIBCXX_USE_NOEXCEPT {
        std::stringstream ss;
        ss << "Type mismatch" << other << ". Expected " << expected << ", got " << got;
        return ss.str().c_str();
    }
};

#endif
