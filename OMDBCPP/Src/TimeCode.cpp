#include "TimeCode.h"

#include <sstream>
#include <iomanip>
#include <limits>

namespace omdb {
    // sets the internal representation of this timecode

    void TimeCode::setTime(long long day, long long month, long long year,
            long long hour, long long minute, long long second) {
        this->time += (long long) second;
        this->time += ((long long) minute * MINUTE_TO_SECONDS);
        this->time += ((long long) hour * HOUR_TO_SECONDS);
        this->time += ((long long) day * DAY_TO_SECONDS);
        this->time += ((long long) month * MONTH_TO_SECONDS);
        this->time += (year * YEAR_TO_SECONDS);
    }

    // sets the internal representation of this timecode by parsing a formatted
    // string

    void TimeCode::setTime(std::string& timeCode) {
        std::stringstream ss(timeCode);

        ss >> *this;
    }

    // default constructor

    TimeCode::TimeCode() {
        this->setTime(1, 1, 0, 0, 0, 0);
    }

    // value constructor

    TimeCode::TimeCode(long long day, long long month, long long year,
            long long hour, long long minute, long long second) {
        this->setTime(day, month, year, hour, minute, second);
    }

    // create a timecode from a formatted string

    TimeCode::TimeCode(std::string& timeCode) {
        this->setTime(timeCode);
    }

    // create a timecode by giving an explicit internal representation

    TimeCode::TimeCode(uint64_t timeCode) {
        this->time = timeCode;
    }

    // copy constructor

    TimeCode::TimeCode(const TimeCode & other) {
        this->time = other.time;
    }

    // get the formatted timecode string

    std::string TimeCode::getTime() const {
        unsigned numYears, numMonths, numDays, numHours, numMinutes, numSeconds;
        numYears = numMonths = numDays = numHours = numMinutes = numSeconds = 0;

        long long time = this->time;
        numYears = time > 0 ? (time / YEAR_TO_SECONDS) : 0;
        time -= (long long) numYears * YEAR_TO_SECONDS;

        numMonths = time > 0 ? (time / MONTH_TO_SECONDS) : 0;
        time -= (long long) numMonths * MONTH_TO_SECONDS;

        numDays = time > 0 ? (time / DAY_TO_SECONDS) : 0;
        time -= (long long) numDays * DAY_TO_SECONDS;

        numHours = time > 0 ? (time / HOUR_TO_SECONDS) : 0;
        time -= (long long) numHours * HOUR_TO_SECONDS;

        numMinutes = time > 0 ? (time / MINUTE_TO_SECONDS) : 0;
        time -= (long long) numMinutes * MINUTE_TO_SECONDS;

        numSeconds = time > 0 ? time : 0;

        std::stringstream fmt;
        fmt << std::setfill('0') << std::setw(2);
        fmt << numDays << '/';
        fmt << std::setw(2);
        fmt << numMonths << '/';
        fmt << std::setw(4);
        fmt << numYears << 'T';
        fmt << std::setw(2);
        fmt << numHours << ":";
        fmt << std::setw(2);
        fmt << numMinutes << ":";
        fmt << std::setw(2);
        fmt << numSeconds << "Z";
        return fmt.str();
    }

    // convert to uint64_t, basically just gives the internal representation

    TimeCode::operator uint64_t() {
        return this->time;
    }

    // copy assignment operator

    TimeCode & TimeCode::operator=(const TimeCode & other) {
        if (this != &other) {
            this->time = other.time;
        }
        return *this;
    }

    TimeCode TimeCode::operator+(const TimeCode & other) const {
        return TimeCode(this->time + other.time);
    }

    TimeCode TimeCode::operator-(const TimeCode & other) const {
        return TimeCode(this->time - other.time);
    }

    bool TimeCode::operator>(const TimeCode & other) const {
        return this->time > other.time;
    }

    bool TimeCode::operator<(const TimeCode & other) const {
        return this->time < other.time;
    }

    bool TimeCode::operator>=(const TimeCode & other) const {
        return this->time >= other.time;
    }

    bool TimeCode::operator<=(const TimeCode & other) const {
        return this->time <= other.time;
    }

    bool TimeCode::operator==(const TimeCode & other) const {
        return this->time == other.time;
    }

    // put a timecode into an output stream

    std::ostream & operator<<(std::ostream & os, const TimeCode & other) {
        os << other.getTime();
        return os;
    }

    // extract a timecode from an inputstream

    std::istream & operator>>(std::istream & is, TimeCode & other) {
        int day, month, year, hour, minute, second;

        is >> std::ws;
        is >> day;
        is.ignore(std::numeric_limits<std::streamsize>::max(), '/');
        is >> month;
        is.ignore(std::numeric_limits<std::streamsize>::max(), '/');
        is >> year;
        is.ignore(std::numeric_limits<std::streamsize>::max(), 'T');
        is >> hour;
        is.ignore(std::numeric_limits<std::streamsize>::max(), ':');
        is >> minute;
        is.ignore(std::numeric_limits<std::streamsize>::max(), ':');
        is >> second;
        is.ignore(std::numeric_limits<std::streamsize>::max(), 'Z');

        other.setTime(day, month, year, hour, minute, second);

        return is;
    }
}