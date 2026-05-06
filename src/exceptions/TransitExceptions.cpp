#include "exceptions/TransitExceptions.h"
#include <sstream>
#include <string>

TransitException::TransitException(const CustomString& msg, const CustomString& src, int code)
    : m_message(msg), m_source(src), m_timestamp(CustomDate::today()), m_code(code) {}

const char* TransitException::what() const noexcept {
    static std::string s;
    s = m_message.c_str();
    return s.c_str();
}
CustomString TransitException::getMessage() const { return m_message; }
int TransitException::getCode() const { return m_code; }
