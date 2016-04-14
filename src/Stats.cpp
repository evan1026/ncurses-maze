#include <iostream>
#include <iomanip>
#include <string>

#include "Stats.h"
#include "Maybe.h"
#include "Statistic.h"

std::unique_ptr<Stats> Stats::inst = std::unique_ptr<Stats>(new Stats());

void Stats::incrementOrCreateInt(std::string key) {
    Maybe<int> val = get<int>(key);
    if (val) set<int>(key, val() + 1);
    else     set<int>(key, 1);
}

void Stats::decrementOrCreateInt(std::string key) {
    Maybe<int> val = get<int>(key);
    if (val) set<int>(key, val() - 1);
    else     set<int>(key, -1);
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
