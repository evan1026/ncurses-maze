#ifndef STATS_H
#define STATS_H

#include <ctime>
#include <memory>
#include <string>
#include <unordered_map>

#include "Maybe.h"
#include "Statistic.h"

/**********************************************************************************
 * ~~~~~~~~~                                                                      *
 * ~ Stats ~                                                                      *
 * ~~~~~~~~~                                                                      *
 *                                                                                *
 * This is the main class of the statistics system. It associates a Statistic     *
 * with a string, and allows for getting the data stored within through the       *
 * template function get<T>(). It handles checking that the type matches and      *
 * uses a Maybe (see Maybe.h) to handle when the data does not exist or the       *
 * type doesn't match. The constructor of this class is private, and only a       *
 * single instance of it can exist at a time, however, copies can be made of      *
 * the state of the system at any time. To get the instance, use Stats::getInst() *
 *                                                                                *
 * Full docs on each (non-template) function can be found in the corresponding    *
 * cpp file.                                                                      *
 **********************************************************************************/

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
