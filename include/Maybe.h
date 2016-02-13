#ifndef MAYBE_H
#define MAYBE_H

#include <exception>

class null_maybe_exception : public std::exception {
    virtual const char* what() const throw() {
        return "Atempt to turn a null Maybe into a value.";
    }
};

template <typename T>
struct Maybe {
    bool isNull;
    T value;

    Maybe<T>(bool _isNull, T val) : isNull(_isNull), value(val) {}
    Maybe<T>(T val) : isNull(false), value(val) {}
    Maybe<T>() : isNull(true) {}

    Maybe<T> operator=(T val) {
        value = val;
        isNull = false;
    }

    operator bool() const {
        return !isNull;
    }

    T& operator()() {
        if (isNull) throw null_maybe_exception();
        else return value;
    }
};

#endif
