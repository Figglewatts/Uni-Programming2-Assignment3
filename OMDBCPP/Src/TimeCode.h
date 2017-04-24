#ifndef TIMECODE_H
#define TIMECODE_H
#pragma once

#include <cstdint>
#include <string>

namespace omdb {
    // provides an object to store a timecode
    // in restricted UTC format

    class TimeCode {
    private:
        const static unsigned int MAX_SECONDS = 59;
        const static unsigned int MAX_MINUTES = 60;
        const static unsigned int MAX_HOURS = 24;
        const static unsigned int MAX_MONTHS = 12;
        // this doesn't take into account months with 30 days, February,
        // or leap years, but that's okay as the number generated with it
        // will still be ordered and unique
        const static unsigned int MAX_DAYS = 31;

        // conversion constants for adding to internal time representation
        const static unsigned int MINUTE_TO_SECONDS = MAX_SECONDS;
        const static unsigned int HOUR_TO_SECONDS =
                MAX_MINUTES * MINUTE_TO_SECONDS;
        const static unsigned int DAY_TO_SECONDS =
                MAX_HOURS * HOUR_TO_SECONDS;
        const static unsigned int MONTH_TO_SECONDS =
                MAX_DAYS * DAY_TO_SECONDS;
        const static unsigned int YEAR_TO_SECONDS =
                MAX_MONTHS * MONTH_TO_SECONDS;

        long long time = 0;

        int setRange(int min, int max, int val);
        void setTime(long long day, long long month, long long year,
                long long hour, long long minute, long long second);
        void setTime(std::string& timeCode);
    public:
        TimeCode();
        TimeCode(long long day, long long month, long long year,
                long long hour, long long minute, long long second);
        TimeCode(std::string& timeCode);
        TimeCode(uint64_t timeCode);
        TimeCode(const TimeCode& other);

        std::string getTime() const;

        operator uint64_t();

        TimeCode& operator=(const TimeCode& other);
        TimeCode operator+(const TimeCode& other) const;
        TimeCode operator-(const TimeCode& other) const;
        bool operator>(const TimeCode& other) const;
        bool operator<(const TimeCode& other) const;
        bool operator>=(const TimeCode& other) const;
        bool operator<=(const TimeCode& other) const;
        bool operator==(const TimeCode& other) const;

        friend std::ostream& operator<<(std::ostream& os,
                const TimeCode& other);
        friend std::istream& operator>>(std::istream& is, TimeCode& other);
    };
}

#endif // TIMECODE_H