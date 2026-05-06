#include "utilities/GeoCoordinate.h"
#include "exceptions/TransitExceptions.h"
#include <sstream>

static constexpr double kEarthRadiusKm = 6371.0;
static double deg2rad(double d){ return d * 3.14159265358979323846 / 180.0; }
GeoCoordinate::GeoCoordinate() = default;
GeoCoordinate::GeoCoordinate(double latitude,double longitude):m_latitude(latitude),m_longitude(longitude){
    if(!isValid()) throw InvalidCoordinateException("Invalid coordinate","GeoCoordinate",4001);
}
bool GeoCoordinate::isValid() const { return m_latitude >= -90.0 && m_latitude <= 90.0 && m_longitude >= -180.0 && m_longitude <= 180.0; }
double GeoCoordinate::distanceTo(const GeoCoordinate& other) const {
    double dLat = deg2rad(other.m_latitude - m_latitude);
    double dLon = deg2rad(other.m_longitude - m_longitude);
    double a = std::sin(dLat/2)*std::sin(dLat/2) + std::cos(deg2rad(m_latitude))*std::cos(deg2rad(other.m_latitude))*std::sin(dLon/2)*std::sin(dLon/2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1-a));
    return kEarthRadiusKm * c;
}
double GeoCoordinate::bearingTo(const GeoCoordinate& other) const {
    double y = std::sin(deg2rad(other.m_longitude - m_longitude)) * std::cos(deg2rad(other.m_latitude));
    double x = std::cos(deg2rad(m_latitude))*std::sin(deg2rad(other.m_latitude)) - std::sin(deg2rad(m_latitude))*std::cos(deg2rad(other.m_latitude))*std::cos(deg2rad(other.m_longitude - m_longitude));
    return std::fmod((std::atan2(y,x)*180.0/3.14159265358979323846 + 360.0), 360.0);
}
double GeoCoordinate::operator-(const GeoCoordinate& other) const { return distanceTo(other); }
bool GeoCoordinate::operator==(const GeoCoordinate& other) const { return std::fabs(m_latitude-other.m_latitude) < 1e-6 && std::fabs(m_longitude-other.m_longitude) < 1e-6; }
bool GeoCoordinate::operator!=(const GeoCoordinate& other) const { return !(*this == other); }
CustomString GeoCoordinate::toString() const { std::ostringstream os; os<<m_latitude<<","<<m_longitude; return CustomString(os.str().c_str()); }
std::ostream& operator<<(std::ostream& os, const GeoCoordinate& g){ return os << g.toString(); }
std::istream& operator>>(std::istream& is, GeoCoordinate& g){ double a,b; char c; is>>a>>c>>b; g = GeoCoordinate(a,b); return is; }
