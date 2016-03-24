#include <iostream>
#include <iomanip>
#include <string>

#include "Stats.h"

std::unique_ptr<Stats> Stats::inst = std::unique_ptr<Stats>(new Stats());

Maybe<Statistic> Stats::getStat(std::string key) {
    auto testIter = stats.find(key);
    if (testIter != stats.end()) {
        return Maybe<Statistic>(testIter->second);
    } else {
        return Maybe<Statistic>();
    }
}

void Stats::setStat(std::string key, Statistic value) {
    stats[key] = value;
}

Maybe<int> Stats::getInteger(std::string key) {
    Maybe<Statistic> stat = getStat(key);

    if (stat && stat().type == Statistic::Type::INT) {
        return Maybe<int>(stat().value.i);
    } else {
        return Maybe<int>();
    }
}

Maybe<double> Stats::getDouble(std::string key) {
    Maybe<Statistic> stat = getStat(key);

    if (stat && stat().type == Statistic::Type::DOUBLE) {
        return Maybe<double>(stat().value.d);
    } else {
        return Maybe<double>();
    }
}

Maybe<std::string> Stats::getString(std::string key) {
    Maybe<Statistic> stat = getStat(key);

    if (stat && stat().type == Statistic::Type::STRING) {
        return Maybe<std::string>(stat().value.s);
    } else {
        return Maybe<std::string>();
    }
}

Maybe<bool> Stats::getBool(std::string key) {
    Maybe<Statistic> stat = getStat(key);

    if (stat && stat().type == Statistic::Type::BOOL) {
        return Maybe<bool>(stat().value.b);
    } else {
        return Maybe<bool>();
    }
}

Maybe<time_t> Stats::getTime(std::string key) {
    Maybe<Statistic> stat = getStat(key);

    if (stat && stat().type == Statistic::Type::TIME) {
        return Maybe<time_t>(stat().value.t);
    } else {
        return Maybe<time_t>();
    }
}

void Stats::setInteger(std::string key, int value) {
    setStat(key, Statistic(value));
}

void Stats::setDouble(std::string key, double value) {
    setStat(key, Statistic(value));
}

void Stats::setString(std::string key, std::string value) {
    setStat(key, Statistic(value));
}

void Stats::setBool(std::string key, bool value) {
    setStat(key, Statistic(value));
}

void Stats::setTime(std::string key, time_t value) {
    setStat(key, Statistic(value));
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
namespace {
    void printTime(time_t t, std::ostream& os) {
        auto timeinfo = *localtime(&t);
        char buf[80];

        strftime(buf,80,"%m-%d-%Y %I:%M:%S",&timeinfo);
        os << buf;
    }
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

        switch (iter->second.type) {
            case Statistic::Type::INT:
                os << iter->second.value.i;
                break;
            case Statistic::Type::DOUBLE:
                os << iter->second.value.d;
                break;
            case Statistic::Type::STRING:
                os << iter->second.value.s;
                break;
            case Statistic::Type::BOOL:
                os << (iter->second.value.b ? "true" : "false");
                break;
            case Statistic::Type::TIME:
                printTime(iter->second.value.t, os);
                break;
            case Statistic::Type::NONE:
                os << "NONE_TYPE";
                break;
            default:
                os << "UNKNOWN_TYPE";
        }
        os << std::endl;
    }
    return os;
}

Stats& Stats::getInst() {
    return *inst;
}
