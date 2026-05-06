#pragma once
#include "utilities/CustomString.h"
#include <ostream>
#include <istream>

class CustomTime {
    int m_hour{}, m_minute{}, m_second{};
public:
    CustomTime();
    CustomTime(int h, int m, int s);

    static CustomTime now();
    int operator-(const CustomTime& rhs) const;
    CustomTime operator+(int seconds) const;
    CustomTime& operator++();
    bool operator==(const CustomTime& rhs) const;
    bool operator<(const CustomTime& rhs) const;
    bool operator>(const CustomTime& rhs) const;
    CustomString toString12h() const;
    CustomString toString24h() const;
    static CustomTime fromString(const CustomString& s);
    void addMinutes(int minutes);
    friend std::ostream& operator<<(std::ostream& os, const CustomTime& t);
};
