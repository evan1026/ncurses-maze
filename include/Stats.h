#ifndef STATS_H
#define STATS_H

#include <ctime>
#include <memory>
#include <string>
#include <unordered_map>

#include "Maybe.h"
#include "Statistic.h"

class Stats {
    std::unordered_map<std::string, Statistic> stats;
    static std::unique_ptr<Stats> inst;

    Stats() : stats() {}

public:

    template <typename T>
    Maybe<T> get(const std::string& key) const {
        auto testIter = stats.find(key);
        if (testIter != stats.end() && testIter->second.checkType<T>()) {
            return Maybe<T>(testIter->second.get<T>());
        } else {
            return Maybe<T>();
        }
    }

    template <typename T>
    void set(const std::string& key, const T& val) {
        stats[key] = Statistic(val);
    }

    void incrementOrCreateInt(std::string key);
    void decrementOrCreateInt(std::string key);

    friend std::ostream& operator<<(std::ostream& os, const Stats& obj);

    static Stats& getInst();
};

#endif
