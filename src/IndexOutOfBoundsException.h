#ifndef INDEX_OUT_OF_BOUNDS_EXCEPTION_H
#define INDEX_OUT_OF_BOUNDS_EXCEPTION_H

#include <exception>
#include <string>

class IndexOutOfBoundsException: public std::exception {
    
    std::string d;

    IndexOutOfBoundsException();

public:
    IndexOutOfBoundsException(std::string details) : d(details) {}

    virtual const char* what() const throw() {
        return "Index was out of bounds.";
    }

    std::string details() {
        return d;
    }
};

#endif
