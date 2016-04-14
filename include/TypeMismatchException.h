#ifndef TYPE_MISMATCH_EXCEPTION_H
#define TYPE_MISMATCH_EXCEPTION_H

#include <typeinfo>
#include <stdexcept>
#include <sstream>

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
