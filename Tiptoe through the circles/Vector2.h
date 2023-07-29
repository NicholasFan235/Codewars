
#include <math.h>
namespace geo
{

class Vector2{
    public:
        double x, y;
    private:
    public:
        Vector2() : x(0), y(0) {}
        Vector2(double _x, double _y) : x(_x), y(_y) {}
        Vector2(const Vector2 &v) : x(v.x), y(v.y) {}
        ~Vector2() = default;
    public:
        double mag() const { return sqrt(x*x+y*y); }
        double mag2() const { return x*x + y*y; }
        double angle() const { return std::fmod(atan2(y, x) + 2.0f * M_PI, 2.0f * M_PI); }
        Vector2& normalize() { *this/=mag(); return *this;};
        Vector2 normalized() const { return *this/mag(); };
 
        Vector2 rotated(double angle) { return Vector2(cos(angle)*x-sin(angle)*y, sin(angle)*x+cos(angle)*y); }

        Vector2 operator+(const Vector2 &v) const{ return Vector2(x+v.x, y+v.y); }
        Vector2 operator-(const Vector2 &v) const{ return Vector2(x-v.x, y-v.y); }
        Vector2 operator+(const double &i) const{ return Vector2(x+i, y+i); }
        Vector2 operator-(const double &i) const { return Vector2(x-i, y-i); }
        Vector2 operator*(const double &i) const { return Vector2(x*i, y*i); }
        Vector2 operator/(const double &i) const { return Vector2(x/i, y/i); }

        Vector2& operator+=(const Vector2 &v) { x+=v.x; y+=v.y; return *this; }
        Vector2& operator-=(const Vector2 &v) { x-=v.x; y-=v.y; return *this; }
        Vector2& operator+=(const double &i) { x+=i; y+=i; return *this; }
        Vector2& operator-=(const double &i) { x-=i; y-=i; return *this; }
        Vector2& operator*=(const double &i) { x*=i; y*=i; return *this; }
        Vector2& operator/=(const double &i) { x/=i; y/=i; return *this; }

        double dot(const Vector2 &v) const{ return x*v.x + y*v.y; }
        double cross(const Vector2 &v) const{ return x*v.x - y*v.y; }

        friend bool operator==(const Vector2 &l, const Vector2 &r) { return l.x==r.x && l.y==r.y; }
        friend bool operator!=(const Vector2 &l, const Vector2 &r) { return l.x!=r.x || l.y!=r.y; }

    private:
        void initialise();
};

double dot(const Vector2& u, const Vector2& v){ return u.dot(v); };
double cross(const Vector2& u, const Vector2& v){ return u.cross(v); };
double mag(const Vector2& v){ return v.mag(); }
double mag2(const Vector2& v){ return v.mag2(); }

const Vector2 operator+(const double &i, const Vector2 &v) { return v+i; }
const Vector2 operator-(const double &i, const Vector2 &v) { return Vector2(i-v.x, i-v.y); }
const Vector2 operator*(const double &i, const Vector2 &v) { return v*i; }

}