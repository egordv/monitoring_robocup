#pragma once

#include <vector>
#include <string>

class Log
{
    public:
        struct Entry
        {
            uint32_t time;
            std::string message;
        };

        Log();
        void load(std::string log);

        std::vector<Entry> entriesBetween(uint8_t hour1, uint8_t min1, uint8_t sec1,
                uint8_t hour2, uint8_t min2, uint8_t sec2);

        int getEntries();

    protected:
        std::vector<Entry> entries;
};

