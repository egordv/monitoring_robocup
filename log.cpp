#include <iostream>
#include <regex>
#include "log.h"
#include <rhoban_utils/io_tools.h>
#include <rhoban_utils/util.h>

using namespace rhoban_utils;

static uint32_t hms(uint8_t h, uint8_t m, uint8_t s) {
    return h*3600 + m*60 +s;
}

Log::Log()
{
}

int Log::getEntries()
{
    return entries.size();
}

void Log::load(std::string filename)
{
    entries.clear();
    std::string data = file2string(filename);
    std::vector<std::string> lines;
    split(data, '\n', lines);

    std::regex regex("^(.*)\\[(\\d+):(\\d+):(\\d+):(\\d+)\\] (.+)$");
    for (auto &line : lines) {
        std::cmatch cm;
        if (std::regex_match(line.c_str(), cm, regex)) {
            uint8_t hour = atoi(cm[2].str().c_str());
            uint8_t min = atoi(cm[3].str().c_str());
            uint8_t sec = atoi(cm[4].str().c_str());

            Entry e;
            e.time = hms(hour, min, sec);
            e.message = cm[0];
            entries.push_back(e);
        }
    }
}

std::vector<Log::Entry> Log::entriesBetween(uint8_t hour1, uint8_t min1, uint8_t sec1,
        uint8_t hour2, uint8_t min2, uint8_t sec2)
{
    std::vector<Entry> result;

    if (!entries.size()) {
        return result;
    }

    uint32_t from = hms(hour1, min1, sec1);
    uint32_t to = hms(hour2, min2, sec2);

    size_t A = 0;
    size_t B = entries.size()-1;

    while (A != B) {
        size_t M = (A+B)/2;
        if (entries[M].time > from) {
            B = M;
        } else {
            A = M+1;
        }
    }

    while (A<entries.size() && entries[A].time <= to) {
        if (entries[A].time > from) {
            result.push_back(entries[A]);
        }
        A++;
    }

    return result;
}


