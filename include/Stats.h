#ifndef STATS_H
#define STATS_H

#include <ctime>
#include <memory>
#include <string>
#include <unordered_map>

#include "Maybe.h"

struct Statistic {
    enum class Type {INT, DOUBLE, STRING, BOOL, TIME, NONE} type;
    struct Value {int i; double d; bool b;
        time_t t; std::string s;} value; //was going to be union, but I can't do that with strings

    Statistic() : type(Type::NONE), value() {} // to make it compatible with Maybe
    Statistic(int i) : type(Type::INT) { value.i = i; }
    Statistic(double d) : type(Type::DOUBLE) { value.d = d; }
    Statistic(std::string s) : type(Type::STRING) { value.s = s; }
    Statistic(bool b) : type(Type::BOOL) { value.b = b; }
    Statistic(time_t t) : type(Type::TIME) { value.t = t; }
};

class Stats {
    std::unordered_map<std::string, Statistic> stats;
    static std::unique_ptr<Stats> inst;

    Maybe<Statistic> getStat(std::string key);
    void setStat(std::string key, Statistic value);

    Stats() : stats() {}

public:

    Maybe<int> getInteger(std::string key);
    Maybe<double> getDouble(std::string key);
    Maybe<std::string> getString(std::string key);
    Maybe<bool> getBool(std::string key);
    Maybe<time_t> getTime(std::string key);

    void setInteger(std::string, int value);
    void setDouble(std::string key, double value);
    void setString(std::string key, std::string value);
    void setBool(std::string key, bool value);
    void setTime(std::string key, time_t value);

    void incrementOrCreateInt(std::string key);
    void decrementOrCreateInt(std::string key);

    friend std::ostream& operator<<(std::ostream& os, const Stats& obj);

    static Stats& getInst();
};

#endif
