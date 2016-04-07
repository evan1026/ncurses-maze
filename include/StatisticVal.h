#ifndef STATISTIC_VAL_H
#define STATISTIC_VAL_H

#include <string>
#include <ctime>
#include <iostream>

//To be used with the stats class
//This struct represents a statistic value, but
//does not keep track of the key
struct StatisticVal {
    enum class Type {
        INT,
        DOUBLE,
        STRING,
        BOOL,
        TIME,
        NONE
    };

    Type type;
    void *value;

    StatisticVal() : type(Type::NONE), value(nullptr) {}
    StatisticVal(int i);
    StatisticVal(double d);
    StatisticVal(std::string s);
    StatisticVal(bool b);
    StatisticVal(time_t t);

    ~StatisticVal();
    StatisticVal(const StatisticVal& other);
    StatisticVal(StatisticVal&& other);
    StatisticVal& operator=(const StatisticVal& other);
    StatisticVal& operator=(StatisticVal&& other);

    int getInt();
    double getDouble();
    std::string getString();
    bool getBool();
    time_t getTime();

private:
    void freeValue();
    void setFromOther(const StatisticVal& other);
    void setFromOther(StatisticVal&& other);
    void throwMismatch(StatisticVal::Type expected, StatisticVal::Type got, int linenum);
};

std::ostream& operator<<(std::ostream& os, StatisticVal::Type type);
std::ostream& operator<<(std::ostream& os, StatisticVal val);

#endif
