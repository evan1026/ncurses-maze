#ifndef STATS_H
#define STATS_H

#include <ctime>
#include <memory>
#include <string>
#include <unordered_map>

#include "Maybe.h"
#include "StatisticVal.h"

class Stats {
    std::unordered_map<std::string, StatisticVal> stats;
    static std::unique_ptr<Stats> inst;

    Maybe<StatisticVal> getStat(std::string key);
    void setStat(std::string key, StatisticVal value);

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
