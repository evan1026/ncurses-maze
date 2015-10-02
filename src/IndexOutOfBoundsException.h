#ifndef INDEX_OUT_OF_BOUNDS_EXCEPTION_H
#define INDEX_OUT_OF_BOUNDS_EXCEPTION_H

#include <exception>
#include <string>

class IndexOutOfBoundsException: public std::exception {
    
    std::string d;

public:
    IndexOutOfBoundsException() : d("") {}
    IndexOutOfBoundsException(std::string details) {
        d = "Index was out of bounds. " + details;
    }

    void setDetails(std::string details) {
        d = details;
    }

    virtual const char* what() const throw() {
        return d.c_str();
    }
};

#endif
