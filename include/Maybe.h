#ifndef MAYBE_H
#define MAYBE_H

#include <stdexcept>

class null_maybe_exception : public std::runtime_error {
public:
    null_maybe_exception() : runtime_error("Atempt to turn a null Maybe into a value.") {}
};

template <typename T>
class Maybe {
    T* value;

public:
    Maybe<T>(const T val) {
        value = new T;
        *value = val;
    }
    Maybe<T>() {
        value = nullptr;
    }

    ~Maybe<T>() {
        if (value != nullptr) {
            delete value;
        }
    }
    Maybe<T>(const Maybe<T>& other) {
        value = new T;
        *value = *other.value;
    }
    Maybe<T>(Maybe<T>&& other) {
        value = other.value;
        other.value = nullptr;
    }

    Maybe<T>& operator=(const Maybe<T>& other) {
        if (value != nullptr) {
            delete value;
        }
        value = new T;
        *value = *other.value;
    }
    Maybe<T>& operator=(Maybe<T>&& other) {
        if (value != nullptr){
            delete value;
        }
        value = other.value;
        other.value = nullptr;
    }

    Maybe<T>& operator=(const T& val) {
        if (value != nullptr) {
            delete value;
        }
        value = new T;
        *value = val;
    }

    operator bool() const {
        return value != nullptr;
    }

    T operator()() {
        if (*this) return *value;
        else throw null_maybe_exception();
    }
};

#endif
