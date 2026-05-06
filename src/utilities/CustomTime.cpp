#include "utilities/CustomTime.h"
#include "exceptions/TransitExceptions.h"
#include <ctime>
#include <sstream>
#include <iomanip>

static bool valid_time(int h, int m, int s) { return h>=0&&h<24&&m>=0&&m<60&&s>=0&&s<60; }
CustomTime::CustomTime():m_hour(0),m_minute(0),m_second(0){}
CustomTime::CustomTime(int h,int m,int s):m_hour(h),m_minute(m),m_second(s){
    if(!valid_time(h,m,s)) throw InvalidTimeException("Invalid time","CustomTime",3001);
}
CustomTime CustomTime::now() { std::time_t t = std::time(nullptr); std::tm* tm = std::localtime(&t); return CustomTime(tm->tm_hour, tm->tm_min, tm->tm_sec); }
int CustomTime::operator-(const CustomTime& rhs) const { return (m_hour*3600+m_minute*60+m_second) - (rhs.m_hour*3600+rhs.m_minute*60+rhs.m_second); }
CustomTime CustomTime::operator+(int seconds) const {
    int t = m_hour*3600+m_minute*60+m_second+seconds;
    t = (t%(24*3600)+24*3600)%(24*3600);
    return CustomTime(t/3600,(t%3600)/60,t%60);
}
CustomTime& CustomTime::operator++(){ *this = *this + 1; return *this; }
bool CustomTime::operator==(const CustomTime& rhs) const { return m_hour==rhs.m_hour&&m_minute==rhs.m_minute&&m_second==rhs.m_second; }
bool CustomTime::operator<(const CustomTime& rhs) const { return (*this - rhs) < 0; }
bool CustomTime::operator>(const CustomTime& rhs) const { return rhs < *this; }
CustomString CustomTime::toString24h() const { std::ostringstream os; os<<std::setfill('0')<<std::setw(2)<<m_hour<<":"<<std::setw(2)<<m_minute<<":"<<std::setw(2)<<m_second; return CustomString(os.str().c_str()); }
CustomString CustomTime::toString12h() const { int h = m_hour % 12; if (h == 0) h = 12; std::ostringstream os; os<<std::setfill('0')<<std::setw(2)<<h<<":"<<std::setw(2)<<m_minute<<":"<<std::setw(2)<<m_second<<(m_hour<12?" AM":" PM"); return CustomString(os.str().c_str()); }
CustomTime CustomTime::fromString(const CustomString& s){ int h,m,sec; char a,b; std::stringstream ss(s.c_str()); ss>>h>>a>>m>>b>>sec; return CustomTime(h,m,sec); }
void CustomTime::addMinutes(int minutes){ *this = *this + minutes*60; }
std::ostream& operator<<(std::ostream& os, const CustomTime& t){ return os << t.toString24h(); }
