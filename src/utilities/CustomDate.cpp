#include "utilities/CustomDate.h"
#include "exceptions/TransitExceptions.h"
#include <ctime>
#include <sstream>
#include <iomanip>

static bool valid_date(int d, int m, int y) {
    if (y < 1 || m < 1 || m > 12 || d < 1) return false;
    static const int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int maxd = days[m-1];
    bool leap = (y%4==0 && y%100!=0) || (y%400==0);
    if (m==2 && leap) maxd = 29;
    return d <= maxd;
}
CustomDate::CustomDate() : m_day(1), m_month(1), m_year(2000) {}
CustomDate::CustomDate(int day,int month,int year):m_day(day),m_month(month),m_year(year){
    if(!valid_date(day,month,year)) throw InvalidDateException("Invalid date","CustomDate",2001);
}
CustomDate CustomDate::today() {
    std::time_t t = std::time(nullptr);
    std::tm* tm = std::localtime(&t);
    return CustomDate(tm->tm_mday, tm->tm_mon+1, tm->tm_year+1900);
}
bool CustomDate::isLeapYear() const { return (m_year%4==0 && m_year%100!=0) || (m_year%400==0); }
int CustomDate::operator-(const CustomDate& rhs) const {
    std::tm a{}; a.tm_mday=m_day; a.tm_mon=m_month-1; a.tm_year=m_year-1900;
    std::tm b{}; b.tm_mday=rhs.m_day; b.tm_mon=rhs.m_month-1; b.tm_year=rhs.m_year-1900;
    std::time_t ta = std::mktime(&a), tb = std::mktime(&b);
    return static_cast<int>((ta-tb)/(60*60*24));
}
CustomDate CustomDate::operator+(int days) const {
    std::tm a{}; a.tm_mday=m_day+days; a.tm_mon=m_month-1; a.tm_year=m_year-1900;
    std::mktime(&a);
    return CustomDate(a.tm_mday, a.tm_mon+1, a.tm_year+1900);
}
CustomDate& CustomDate::operator++() { *this = *this + 1; return *this; }
bool CustomDate::operator==(const CustomDate& rhs) const { return m_day==rhs.m_day&&m_month==rhs.m_month&&m_year==rhs.m_year; }
bool CustomDate::operator<(const CustomDate& rhs) const { return (*this - rhs) < 0; }
bool CustomDate::operator<=(const CustomDate& rhs) const { return *this < rhs || *this == rhs; }
bool CustomDate::operator>(const CustomDate& rhs) const { return rhs < *this; }
bool CustomDate::operator>=(const CustomDate& rhs) const { return !(*this < rhs); }
CustomString CustomDate::toString() const {
    std::ostringstream os; os<<std::setfill('0')<<std::setw(2)<<m_day<<"-"<<std::setw(2)<<m_month<<"-"<<m_year;
    return CustomString(os.str().c_str());
}
CustomDate CustomDate::fromString(const CustomString& s) {
    int d,m,y; char a,b; std::stringstream ss(s.c_str()); ss>>d>>a>>m>>b>>y; return CustomDate(d,m,y);
}
bool CustomDate::isWeekend() const { int dow = getDayOfWeek(); return dow==0 || dow==6; }
int CustomDate::getDayOfWeek() const {
    std::tm a{}; a.tm_mday=m_day; a.tm_mon=m_month-1; a.tm_year=m_year-1900;
    std::mktime(&a); return a.tm_wday;
}
void CustomDate::addMonths(int months) {
    int total = (m_month-1)+months;
    m_year += total/12;
    m_month = total%12 + 1;
    if (m_month <= 0) { m_month += 12; --m_year; }
    if (!valid_date(m_day,m_month,m_year)) m_day = 28;
}
std::ostream& operator<<(std::ostream& os, const CustomDate& d){ return os << d.toString(); }
std::istream& operator>>(std::istream& is, CustomDate& d){ std::string s; is>>s; d = CustomDate::fromString(CustomString(s.c_str())); return is; }
