#pragma once
#include <ostream>
#include <istream>
#include <vector>
#include <string_view>

class CustomString {
    char* m_data;
    int m_length;

    void allocate_and_copy(const char* s);

public:
    CustomString();
    CustomString(const char* s);
    CustomString(const CustomString& other);
    CustomString(CustomString&& other) noexcept;
    ~CustomString();

    CustomString& operator=(const CustomString& other);
    CustomString& operator=(CustomString&& other) noexcept;

    int length() const;
    bool isEmpty() const;
    const char* c_str() const;

    CustomString operator+(const CustomString& rhs) const;
    CustomString& operator+=(const CustomString& rhs);
    bool operator==(const CustomString& rhs) const;
    bool operator!=(const CustomString& rhs) const;
    bool operator<(const CustomString& rhs) const;
    bool operator>(const CustomString& rhs) const;
    char& operator[](int index);
    const char& operator[](int index) const;

    void toUpperCase();
    void toLowerCase();
    void trim();
    CustomString substring(int start, int len) const;
    int find(const CustomString& needle) const;
    void replace(const CustomString& from, const CustomString& to);
    bool contains(const CustomString& s) const;
    bool startsWith(const CustomString& prefix) const;
    bool endsWith(const CustomString& suffix) const;
    int toInt() const;
    double toDouble() const;

    std::vector<CustomString> split(char delimiter) const;

    friend std::ostream& operator<<(std::ostream& os, const CustomString& s);
    friend std::istream& operator>>(std::istream& is, CustomString& s);
};

