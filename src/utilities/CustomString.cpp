#include "utilities/CustomString.h"
#include "exceptions/TransitExceptions.h"
#include <cstring>
#include <cctype>
#include <cstdlib>

// ─── Internal helper: heap-duplicate a C-string ───────────────────────────────
static char* dup_str(const char* s) {
    if (!s) {
        char* p = new char[1];
        p[0] = '\0';
        return p;
    }
    const int n = static_cast<int>(std::strlen(s));
    char* p = new char[n + 1];
    std::memcpy(p, s, n + 1);
    return p;
}

// ─── Internal helper: find first occurrence of needle in haystack ─────────────
static int raw_find(const char* haystack, int hLen,
                    const char* needle,   int nLen,
                    int startPos = 0) {
    if (nLen == 0) return startPos;
    if (nLen > hLen) return -1;
    for (int i = startPos; i <= hLen - nLen; ++i) {
        if (std::memcmp(haystack + i, needle, nLen) == 0)
            return i;
    }
    return -1;
}

// ─── Constructors / Destructor ────────────────────────────────────────────────
void CustomString::allocate_and_copy(const char* s) {
    delete[] m_data;
    m_data   = dup_str(s);
    m_length = static_cast<int>(std::strlen(m_data));
}

CustomString::CustomString()
    : m_data(dup_str("")), m_length(0) {}

CustomString::CustomString(const char* s)
    : m_data(nullptr), m_length(0) {
    allocate_and_copy(s ? s : "");
}

CustomString::CustomString(const CustomString& other)
    : m_data(dup_str(other.m_data)), m_length(other.m_length) {}

CustomString::CustomString(CustomString&& other) noexcept
    : m_data(other.m_data), m_length(other.m_length) {
    other.m_data   = dup_str("");
    other.m_length = 0;
}

CustomString::~CustomString() { delete[] m_data; }

// ─── Assignment operators ─────────────────────────────────────────────────────
CustomString& CustomString::operator=(const CustomString& other) {
    if (this != &other) {
        allocate_and_copy(other.m_data);
        m_length = other.m_length;
    }
    return *this;
}

CustomString& CustomString::operator=(CustomString&& other) noexcept {
    if (this != &other) {
        delete[] m_data;
        m_data         = other.m_data;
        m_length       = other.m_length;
        other.m_data   = dup_str("");
        other.m_length = 0;
    }
    return *this;
}

// ─── Basic accessors ──────────────────────────────────────────────────────────
int         CustomString::length()  const { return m_length; }
bool        CustomString::isEmpty() const { return m_length == 0; }
const char* CustomString::c_str()   const { return m_data; }

// ─── Concatenation ────────────────────────────────────────────────────────────
CustomString CustomString::operator+(const CustomString& rhs) const {
    int newLen = m_length + rhs.m_length;
    char* buf  = new char[newLen + 1];
    std::memcpy(buf,            m_data,     m_length);
    std::memcpy(buf + m_length, rhs.m_data, rhs.m_length + 1); // +1 copies '\0'
    CustomString result(buf);
    delete[] buf;
    return result;
}

CustomString& CustomString::operator+=(const CustomString& rhs) {
    *this = *this + rhs;
    return *this;
}

// ─── Comparison operators ─────────────────────────────────────────────────────
bool CustomString::operator==(const CustomString& rhs) const {
    return std::strcmp(m_data, rhs.m_data) == 0;
}
bool CustomString::operator!=(const CustomString& rhs) const {
    return !(*this == rhs);
}
bool CustomString::operator<(const CustomString& rhs) const {
    return std::strcmp(m_data, rhs.m_data) < 0;
}
bool CustomString::operator>(const CustomString& rhs) const {
    return std::strcmp(m_data, rhs.m_data) > 0;
}

// ─── Index operator ───────────────────────────────────────────────────────────
char& CustomString::operator[](int index) {
    if (index < 0 || index >= m_length)
        throw IndexOutOfBoundsException(
            "CustomString index out of bounds", "CustomString", 1001);
    return m_data[index];
}
const char& CustomString::operator[](int index) const {
    if (index < 0 || index >= m_length)
        throw IndexOutOfBoundsException(
            "CustomString index out of bounds", "CustomString", 1001);
    return m_data[index];
}

// ─── Case conversion ──────────────────────────────────────────────────────────
void CustomString::toUpperCase() {
    for (int i = 0; i < m_length; ++i)
        m_data[i] = static_cast<char>(
            std::toupper(static_cast<unsigned char>(m_data[i])));
}
void CustomString::toLowerCase() {
    for (int i = 0; i < m_length; ++i)
        m_data[i] = static_cast<char>(
            std::tolower(static_cast<unsigned char>(m_data[i])));
}

// ─── Trim (no std::string) ────────────────────────────────────────────────────
void CustomString::trim() {
    int l = 0;
    while (l < m_length && (m_data[l] == ' '  || m_data[l] == '\t' ||
                            m_data[l] == '\r' || m_data[l] == '\n'))
        ++l;

    int r = m_length - 1;
    while (r >= l  && (m_data[r] == ' '  || m_data[r] == '\t' ||
                      m_data[r] == '\r' || m_data[r] == '\n'))
        --r;

    int newLen = r - l + 1;
    if (newLen <= 0) {
        allocate_and_copy("");
        return;
    }
    char* buf = new char[newLen + 1];
    std::memcpy(buf, m_data + l, newLen);
    buf[newLen] = '\0';
    allocate_and_copy(buf);
    delete[] buf;
}

// ─── Substring ────────────────────────────────────────────────────────────────
CustomString CustomString::substring(int start, int len) const {
    if (start < 0 || len < 0 || start > m_length)
        throw IndexOutOfBoundsException(
            "substring out of bounds", "CustomString", 1002);
    int actualLen = (start + len > m_length) ? m_length - start : len;
    char* buf = new char[actualLen + 1];
    std::memcpy(buf, m_data + start, actualLen);
    buf[actualLen] = '\0';
    CustomString result(buf);
    delete[] buf;
    return result;
}

// ─── Find ─────────────────────────────────────────────────────────────────────
int CustomString::find(const CustomString& needle) const {
    return raw_find(m_data, m_length, needle.m_data, needle.m_length);
}

// ─── Replace ──────────────────────────────────────────────────────────────────
void CustomString::replace(const CustomString& from, const CustomString& to) {
    if (from.m_length == 0) return;

    // Count occurrences first to allocate exact buffer
    int count = 0;
    int pos   = 0;
    while ((pos = raw_find(m_data, m_length, from.m_data, from.m_length, pos)) != -1) {
        ++count;
        pos += from.m_length;
    }
    if (count == 0) return;

    int newLen = m_length + count * (to.m_length - from.m_length);
    char* buf  = new char[newLen + 1];
    int   src  = 0;
    int   dst  = 0;

    while (src < m_length) {
        int found = raw_find(m_data, m_length, from.m_data, from.m_length, src);
        if (found == -1) {
            std::memcpy(buf + dst, m_data + src, m_length - src);
            dst += m_length - src;
            break;
        }
        std::memcpy(buf + dst, m_data + src, found - src);
        dst += found - src;
        std::memcpy(buf + dst, to.m_data, to.m_length);
        dst += to.m_length;
        src  = found + from.m_length;
    }
    buf[dst] = '\0';
    allocate_and_copy(buf);
    delete[] buf;
}

// ─── Contains / startsWith / endsWith ────────────────────────────────────────
bool CustomString::contains(const CustomString& s) const {
    return find(s) >= 0;
}

bool CustomString::startsWith(const CustomString& prefix) const {
    if (prefix.m_length > m_length) return false;
    return std::memcmp(m_data, prefix.m_data, prefix.m_length) == 0;
}

bool CustomString::endsWith(const CustomString& suffix) const {
    if (suffix.m_length > m_length) return false;
    return std::memcmp(m_data + m_length - suffix.m_length,
                       suffix.m_data, suffix.m_length) == 0;
}

// ─── toInt / toDouble ─────────────────────────────────────────────────────────
int    CustomString::toInt()    const { return static_cast<int>(std::atoi(m_data)); }
double CustomString::toDouble() const { return std::atof(m_data); }

// ─── Split (no std::string — uses raw_find with delimiter char) ───────────────
std::vector<CustomString> CustomString::split(char delimiter) const {
    std::vector<CustomString> out;
    int start = 0;
    for (int i = 0; i <= m_length; ++i) {
        if (i == m_length || m_data[i] == delimiter) {
            int segLen = i - start;
            char* buf  = new char[segLen + 1];
            std::memcpy(buf, m_data + start, segLen);
            buf[segLen] = '\0';
            out.emplace_back(buf);
            delete[] buf;
            start = i + 1;
        }
    }
    return out;
}

// ─── Stream operators ─────────────────────────────────────────────────────────
std::ostream& operator<<(std::ostream& os, const CustomString& s) {
    return os << s.m_data;
}

// operator>> reads one whitespace-delimited token using raw char buffer
std::istream& operator>>(std::istream& is, CustomString& s) {
    char buf[4096];
    if (is >> buf)
        s = CustomString(buf);
    return is;
}