#include <iostream>

template <class T>
class MagicCompare
{
private:
    T m_val;
    bool m_valid;

public:
    MagicCompare(T val, bool valid = true) :
        m_val(val), m_valid(valid)
    {}

    MagicCompare(const MagicCompare& other) :
        m_val(other.m_val)
    {}

    MagicCompare& operator=(const MagicCompare& other)
    {
        m_val = other.m_val;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const MagicCompare& m)
    {
        out << m.m_val;
        return out;
    }

    MagicCompare operator+(const MagicCompare &a) const { return MagicCompare(m_val + a.m_val); }
    MagicCompare operator-(const MagicCompare &a) const { return MagicCompare(m_val - a.m_val); }
    MagicCompare operator*(const MagicCompare &a) const { return MagicCompare(m_val * a.m_val); }
    MagicCompare operator/(const MagicCompare &a) const { return MagicCompare(m_val / a.m_val); }
    MagicCompare operator+(const T &val) const { return MagicCompare(m_val + val); }
    MagicCompare operator-(const T &val) const { return MagicCompare(m_val - val); }
    MagicCompare operator*(const T &val) const { return MagicCompare(m_val * val); }
    MagicCompare operator/(const T &val) const { return MagicCompare(m_val / val); }

    MagicCompare& operator+=(const MagicCompare &other) { m_val += other; return *this; }
    MagicCompare& operator-=(const MagicCompare &other) { m_val -= other; return *this; }
    MagicCompare& operator*=(const MagicCompare &other) { m_val *= other; return *this; }
    MagicCompare& operator/=(const MagicCompare &other) { m_val /= other; return *this; }
    MagicCompare& operator+=(const T &val) { m_val += val; return *this; }
    MagicCompare& operator-=(const T &val) { m_val -= val; return *this; }
    MagicCompare& operator*=(const T &val) { m_val *= val; return *this; }
    MagicCompare& operator/=(const T &val) { m_val /= val; return *this; }

    MagicCompare& operator++() { m_val++; return *this; }
    MagicCompare& operator--() { m_val--; return *this; }

    MagicCompare operator<(const MagicCompare &other) { return MagicCompare(other.m_val, m_valid && other.m_valid && m_val < other.m_val); }
    MagicCompare operator<=(const MagicCompare &other) { return MagicCompare(other.m_val, m_valid && other.m_valid && m_val <= other.m_val); }
    MagicCompare operator>(const MagicCompare &other) { return MagicCompare(other.m_val, m_valid && other.m_valid && m_val > other.m_val); }
    MagicCompare operator>=(const MagicCompare &other) { return MagicCompare(other.m_val, m_valid && other.m_valid && m_val >= other.m_val); }
    

    const T& val() const { return m_val; }
};

template <class T>
const MagicCompare<T> operator+(const T &val, const MagicCompare<T> &m) { return MagicCompare<T>(val + m.val()); }
template <class T>
const MagicCompare<T> operator-(const T &val, const MagicCompare<T> &m) { return MagicCompare<T>(val - m.val()); }
template <class T>
const MagicCompare<T> operator*(const T &val, const MagicCompare<T> &m) { return MagicCompare<T>(val * m.val()); }
template <class T>
const MagicCompare<T> operator/(const T &val, const MagicCompare<T> &m) { return MagicCompare<T>(val / m.val()); }
