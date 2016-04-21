#ifndef STATISTIC_H
#define STATISTIC_H

#include <boost/spirit/home/support/detail/hold_any.hpp>
#include <ctime>
#include <iostream>
#include <string>
#include <typeindex>
#include <typeinfo>

#include "TypeMismatchException.h"

/******************************************************************************
 * ~~~~~~~~~~~~~                                                              *
 * ~ Statistic ~                                                              *
 * ~~~~~~~~~~~~~                                                              *
 *                                                                            *
 * Holds a value that corresponds to a statistic. This works in conjunction   *
 * with the Stats class to allow for storing any type of value and accessing  *
 * them with a string key. This class takes care of holding the value and     *
 * doing type checking at runtime to ensure that no type errors occur. This   *
 * class is needed because it allows for the Stats class to hold all types    *
 * of values in a single data structure. Another option would be to create    *
 * a complicated templated system, but since boost has already created        *
 * something that can hold a generic value, it makes more sense to use that.  *
 * The boost file is a simple header, and requires no extra libraries to      *
 * compile or run.                                                            *
 *                                                                            *
 * Example usage:                                                             *
 *     Statistic num(10);                                                     *
 *     Statistic letter('a');                                                 *
 *                                                                            *
 *     if (num.checkType<int>) {                                              *
 *         //Will succeed                                                     *
 *         num.get<int>(); //Safe, as the type matches                        *
 *     }                                                                      *
 *                                                                            *
 *     num.get<char>(); //Will throw exception, as type doesn't match         *
 *                                                                            *
 *     if (letter.checkType<int>) {                                           *
 *         //Will fail                                                        *
 *         char.get<int>(); //Will not be called. However, it would be unsafe *
 *     }                                                                      *
 *                                                                            *
 *     letter.get<char>(); //Types match - safe to use                        *
 *                                                                            *
 * In this example, there are obviously better ways to do this, but it is a   *
 * trivial example for the sake of simplicity. Check out the Stats class and  *
 * its usages to see non-trivial examples of this system working.             *
 ******************************************************************************/

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
