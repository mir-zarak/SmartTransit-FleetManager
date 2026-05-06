#pragma once
#include "utilities/CustomString.h"
#include <ostream>
#include <istream>
#include <cmath>

class GeoCoordinate {
    double m_latitude{}, m_longitude{};
public:
    GeoCoordinate();
    GeoCoordinate(double latitude, double longitude);
    bool isValid() const;
    double distanceTo(const GeoCoordinate& other) const;
    double bearingTo(const GeoCoordinate& other) const;
    double operator-(const GeoCoordinate& other) const;
    bool operator==(const GeoCoordinate& other) const;
    bool operator!=(const GeoCoordinate& other) const;
    CustomString toString() const;
    friend std::ostream& operator<<(std::ostream& os, const GeoCoordinate& g);
    friend std::istream& operator>>(std::istream& is, GeoCoordinate& g);
};
