#include <iostream>
#include <iomanip>
#include <string>

#include "Stats.h"
#include "Maybe.h"
#include "StatisticVal.h"

std::unique_ptr<Stats> Stats::inst = std::unique_ptr<Stats>(new Stats());

Maybe<StatisticVal> Stats::getStat(std::string key) {
    auto testIter = stats.find(key);
    if (testIter != stats.end()) {
        return Maybe<StatisticVal>(testIter->second);
    } else {
        return Maybe<StatisticVal>();
    }
}

void Stats::setStat(std::string key, StatisticVal value) {
    stats[key] = value;
}

Maybe<int> Stats::getInteger(std::string key) {
    Maybe<StatisticVal> stat = getStat(key);

    if (stat && stat().type == StatisticVal::Type::INT) {
        return Maybe<int>(stat().getInt());
    } else {
        return Maybe<int>();
    }
}

Maybe<double> Stats::getDouble(std::string key) {
    Maybe<StatisticVal> stat = getStat(key);

    if (stat && stat().type == StatisticVal::Type::DOUBLE) {
        return Maybe<double>(stat().getDouble());
    } else {
        return Maybe<double>();
    }
}

Maybe<std::string> Stats::getString(std::string key) {
    Maybe<StatisticVal> stat = getStat(key);

    if (stat && stat().type == StatisticVal::Type::STRING) {
        return Maybe<std::string>(stat().getString());
    } else {
        return Maybe<std::string>();
    }
}

Maybe<bool> Stats::getBool(std::string key) {
    Maybe<StatisticVal> stat = getStat(key);

    if (stat && stat().type == StatisticVal::Type::BOOL) {
        return Maybe<bool>(stat().getBool());
    } else {
        return Maybe<bool>();
    }
}

Maybe<time_t> Stats::getTime(std::string key) {
    Maybe<StatisticVal> stat = getStat(key);

    if (stat && stat().type == StatisticVal::Type::TIME) {
        return Maybe<time_t>(stat().getTime());
    } else {
        return Maybe<time_t>();
    }
}

void Stats::setInteger(std::string key, int value) {
    setStat(key, StatisticVal(value));
}

void Stats::setDouble(std::string key, double value) {
    setStat(key, StatisticVal(value));
}

void Stats::setString(std::string key, std::string value) {
    setStat(key, StatisticVal(value));
}

void Stats::setBool(std::string key, bool value) {
    setStat(key, StatisticVal(value));
}

void Stats::setTime(std::string key, time_t value) {
    setStat(key, StatisticVal(value));
}

void Stats::incrementOrCreateInt(std::string key) {
    Maybe<int> val = getInteger(key);
    if (val) setInteger(key, val() + 1);
    else     setInteger(key, 1);
}

void Stats::decrementOrCreateInt(std::string key) {
    Maybe<int> val = getInteger(key);
    if (val) setInteger(key, val() - 1);
    else     setInteger(key, -1);
}

std::ostream& operator<<(std::ostream& os, const Stats& obj) {
    int maxLength = 0;
    for (auto iter = obj.stats.begin(); iter != obj.stats.end(); iter++) {
        int length = iter->first.length();
        if (length > maxLength) maxLength = length;
    }

    os << std::endl << "Stats:" << std::endl;
    for (auto iter = obj.stats.begin(); iter != obj.stats.end(); iter++) {
        os << "    " << std::setw(maxLength) << iter->first << " : ";
        os << iter->second << std::endl;
    }
    return os;
}

Stats& Stats::getInst() {
    return *inst;
}
