#ifndef STATISTIC_H
#define STATISTIC_H

#include <string>
#include <ctime>
#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <boost/spirit/home/support/detail/hold_any.hpp>

#include "TypeMismatchException.h"

//To be used with the stats class
//This struct represents a statistic value, but
//does not keep track of the key
class Statistic {

    boost::spirit::hold_any value;

public:
    template <typename T>
    Statistic(const T& val) : value(val) {}
    Statistic() : value() {}

    template <typename T>
    bool checkType() const {
        return value.type() == typeid(T);
    }

    template <typename T>
    T get() const {
        if (checkType<T>()) {
            return boost::spirit::any_cast<T>(value);
        } else {
            throw TypeMismatchException(value.type(), typeid(T), __LINE__ - 3, "Statistic.h");
        }
    }

    friend std::ostream& operator<<(std::ostream& os, Statistic val);
};


#endif
