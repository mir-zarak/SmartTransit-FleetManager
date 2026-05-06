#pragma once
#include "utilities/CustomString.h"
#include <ostream>
#include <istream>

class CustomDate {
    int m_day{}, m_month{}, m_year{};
public:
    CustomDate();
    CustomDate(int day, int month, int year);

    static CustomDate today();
    bool isLeapYear() const;
    int operator-(const CustomDate& rhs) const;
    CustomDate operator+(int days) const;
    CustomDate& operator++();
    bool operator==(const CustomDate& rhs) const;
    bool operator<(const CustomDate& rhs) const;
    bool operator<=(const CustomDate& rhs) const;
    bool operator>(const CustomDate& rhs) const;
    bool operator>=(const CustomDate& rhs) const;
    CustomString toString() const;
    static CustomDate fromString(const CustomString& s);
    bool isWeekend() const;
    int getDayOfWeek() const;
    void addMonths(int months);
    friend std::ostream& operator<<(std::ostream& os, const CustomDate& d);
    friend std::istream& operator>>(std::istream& is, CustomDate& d);
};
