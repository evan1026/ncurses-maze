#include "StatisticVal.h"
#include "TypeMismatchException.h"

#include <string>
#include <sstream>
#include <ctime>

StatisticVal::StatisticVal(int i) : type(Type::INT){
    int *ip = new int;
    *ip = i;
    value = (void *)ip;
}

StatisticVal::StatisticVal(double d) : type(Type::DOUBLE){
    double *dp = new double;
    *dp = d;
    value = (void *)dp;
}

StatisticVal::StatisticVal(std::string s) : type(Type::STRING){
    std::string *sp = new std::string;
    *sp = s;
    value = (void *)sp;
}

StatisticVal::StatisticVal(bool b) : type(Type::BOOL){
    bool *bp = new bool;
    *bp = b;
    value = (void *)bp;
}

StatisticVal::StatisticVal(time_t t) : type(Type::TIME){
    time_t *tp = new time_t;
    *tp = t;
    value = (void *)tp;
}

StatisticVal::~StatisticVal() {
    freeValue();
}

StatisticVal::StatisticVal(const StatisticVal& other) {
    setFromOther(other);
}

StatisticVal::StatisticVal(StatisticVal&& other) {
    setFromOther(other);
}

StatisticVal& StatisticVal::operator=(const StatisticVal& other) {
    freeValue();
    setFromOther(other);
    return *this;
}

StatisticVal& StatisticVal::operator=(StatisticVal&& other) {
    freeValue();
    setFromOther(other);
    return *this;
}

void StatisticVal::freeValue() {
    //You can technically delete a void *, but this is safer
    switch (type) {
        case Type::INT:
            {
                int *i = (int *)value;
                delete i;
                break;
            }
        case Type::DOUBLE:
            {
                double *d = (double *)value;
                delete d;
                break;
            }
        case Type::STRING:
            {
                std::string *s = (std::string *)value;
                delete s;
                break;
            }
        case Type::BOOL:
            {
                bool *b = (bool *)value;
                delete b;
                break;
            }
        case Type::TIME:
            {
                time_t *t = (time_t *)value;
                delete t;
                break;
            }
        case Type::NONE:
            break;
    }
}

void StatisticVal::setFromOther(const StatisticVal& other) {
    type = other.type;
    switch (type) {
        case Type::INT:
            {
                int *oi = (int *)other.value;
                int *i = new int;
                *i = *oi;
                value = (void *)i;
                break;
            }
        case Type::DOUBLE:
            {
                double *od = (double *)other.value;
                double *d = new double;
                *d = *od;
                value = (void *)d;
                break;
            }
        case Type::STRING:
            {
                std::string *os = (std::string *)other.value;
                std::string *s = new std::string;
                *s = *os;
                value = (void *)s;
                break;
            }
        case Type::BOOL:
            {
                bool *ob = (bool *)other.value;
                bool *b = new bool;
                *b = *ob;
                value = (void *)b;
                break;
            }
        case Type::TIME:
            {
                time_t *ot = (time_t *)other.value;
                time_t *t = new time_t;
                *t = *ot;
                value = (void *)t;
                break;
            }
        case Type::NONE:
            value = nullptr;
            break;
    }
}

void StatisticVal::setFromOther(StatisticVal&& other) {
    type = other.type;
    value = other.value;
    other.type = Type::NONE;
    other.value = nullptr;
}

int StatisticVal::getInt() {
    if (type == StatisticVal::Type::INT) {
        return *(int *)value;
    } else {
        throwMismatch(StatisticVal::Type::INT, type, __LINE__ - 3);
        return -1; //To silence compiler. We can never get here.
    }
}

double StatisticVal::getDouble() {
    if (type == StatisticVal::Type::DOUBLE) {
        return *(double *)value;
    } else {
        throwMismatch(StatisticVal::Type::DOUBLE, type, __LINE__ - 3);
        return -1; //To silence compiler. We can never get here.
    }
}

std::string StatisticVal::getString() {
    if (type == StatisticVal::Type::STRING) {
        return *(std::string *)value;
    } else {
        throwMismatch(StatisticVal::Type::STRING, type, __LINE__ - 3);
        return ""; //To silence compiler. We can never get here.
    }
}

bool StatisticVal::getBool() {
    if (type == StatisticVal::Type::BOOL) {
        return *(bool *)value;
    } else {
        throwMismatch(StatisticVal::Type::BOOL, type, __LINE__ - 3);
        return false; //To silence compiler. We can never get here.
    }
}

time_t StatisticVal::getTime() {
    if (type == StatisticVal::Type::TIME) {
        return *(time_t *)value;
    } else {
        throwMismatch(StatisticVal::Type::TIME, type, __LINE__ - 3);
        return time_t(-1); //To silence compiler. We can never get here.
    }
}

std::ostream& operator<<(std::ostream& os, StatisticVal::Type type) {
    switch(type) {
        case StatisticVal::Type::INT:
            os << "int";
            break;
        case StatisticVal::Type::DOUBLE:
            os << "double";
            break;
        case StatisticVal::Type::STRING:
            os << "string";
            break;
        case StatisticVal::Type::BOOL:
            os << "bool";
            break;
        case StatisticVal::Type::TIME:
            os << "time_t";
            break;
        case StatisticVal::Type::NONE:
            os << "none_type";
            break;
    }
    return os;
}

namespace {
    void printTime(time_t t, std::ostream& os) {
        auto timeinfo = *localtime(&t);
        char buf[80];

        strftime(buf,80,"%m-%d-%Y %I:%M:%S",&timeinfo);
        os << buf;
    }
}

std::ostream& operator<<(std::ostream& os, StatisticVal val) {
    switch(val.type) {
        case StatisticVal::Type::INT:
            os << val.getInt();
            break;
        case StatisticVal::Type::DOUBLE:
            os << val.getDouble();
            break;
        case StatisticVal::Type::STRING:
            os << val.getString();
            break;
        case StatisticVal::Type::BOOL:
            os << (val.getBool() ? "true" : "false");
            break;
        case StatisticVal::Type::TIME:
            printTime(val.getTime(), os);
            break;
        case StatisticVal::Type::NONE:
            os << "none_type";
            break;
    }
    return os;
}

void StatisticVal::throwMismatch(StatisticVal::Type expected, StatisticVal::Type got, int linenum) {
    std::stringstream ss;
    std::string e, g;

    ss << expected;
    e = ss.str();

    ss.str() = "";

    ss << got;
    g = ss.str();

    throw TypeMismatchException(e, g, linenum, "StatisticVal.cpp");
}
