#ifndef TYPE_MISMATCH_EXCEPTION_H
#define TYPE_MISMATCH_EXCEPTION_H

#include <sstream>
#include <stdexcept>
#include <typeinfo>

/****************************************************************************
 * ~~~~~~~~~~~~~~~~~~~~~~~~~                                                *
 * ~ TypeMismatchException ~                                                *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~                                                *
 *                                                                          *
 * This exception is thrown when the type expected does not match the type  *
 * received. It will also print the line number and file name, if supplied. *
 * This is used in the Statstic class (see Statistic.h).                    *
 ****************************************************************************/

class TypeMismatchException : public std::runtime_error {
    std::string expected, got, other;

public:
    TypeMismatchException(const std::type_info& e, const std::type_info& g, const int& l, const std::string& f) : std::runtime_error("Type Mismatch"), expected(e.name()), got(g.name()) {
        std::stringstream ss;
        ss << " at line " << l << " in " << f;
        other = ss.str();
    }
    TypeMismatchException(const std::type_info& e, const std::type_info& g) : std::runtime_error("Type Mismatch"), expected(e.name()), got(g.name()), other("") {}
    const char * what() const _GLIBCXX_USE_NOEXCEPT {
        std::stringstream ss;
        ss << "Type mismatch" << other << ". Expected " << expected << ", got " << got;
        return ss.str().c_str();
    }
};

#endif
