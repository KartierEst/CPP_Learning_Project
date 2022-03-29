#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>
#include <utility>

template<const int Size,typename t>
//template<typename...
struct Point
{
    using self_type = Point<Size,t>;
    std::array<t,Size> values {};
    Point() {}
    template <typename... Args>
    Point(Args&&... args) : values { std::forward<Args>(args)... }
    {
        //static_assert(Size == values.size(),"Don't have 2 parameters for 2D Point");
    }
    /*Point(t x, t y) : values { x, y }
    {
        static_assert(Size == 2,"Try to use a Point2D but this is not a Point2D");
    }
    Point(t x, t y, t z) : values { x, y, z }
    {
        static_assert(Size == 3,"Try to use a Point3D but this is not a Point3D");
    }

    friend void test_generic_points()
    {
        Point<3,int> p1;
        Point<3,int> p2;
        auto p3 = p1 + p2;
        p1 += p2;
        p1 *= 3; // ou 3.f, ou 3.0 en fonction du type de Point
    }*/

    float& x() { return values[0]; }
    float x() const { return values[0]; }

    float& y()
    {
        static_assert(Size >=2);
        return values[1];
    }
    float y() const
    {
        static_assert(Size >=2);
        return values[1];
    }

    float& z()
    {
        static_assert(Size >= 3);
        return values[2];
    }
    float z() const
    {
        static_assert(Size >= 3);
        return values[2];
    }

    self_type& operator+=(const self_type& other)
    {
        std::transform(values.begin(),values.end(),other.values.begin(),values.begin(),std::plus<float> {});
        return *this;
    }

    self_type& operator-=(const self_type& other)
    {
        std::transform(values.begin(),values.end(),other.values.begin(),values.begin(),std::minus<float> {});
        return *this;
    }

    self_type& operator*=(const float scalar)
    {
        std::transform(values.begin(),values.end(),values.begin(),[scalar](float c) { return c*scalar; });
        return *this;
    }

    self_type operator+(const self_type& other) const
    {
        self_type result = *this;
        result += other;
        return result;
    }

    self_type operator-(const self_type& other) const
    {
        self_type result = *this;
        result -= other;
        return result;
    }

    self_type operator*(const t scalar) const
    {
        self_type result = *this;
        result *= scalar;
        return result;
    }

    self_type operator-() const { return self_type { -x(), -y(), -z() }; }

    float length() const {
        return std::sqrt(std::accumulate(values.begin(),values.end(),0.0,[](float count,float a){ return count+(a*a);}));
    }

    float distance_to(const self_type& other) const { return (*this - other).length(); }

    self_type& normalize(const float target_len = 1.0f)
    {
        const float current_len = length();
        if (current_len == 0)
        {
            throw std::logic_error("cannot normalize vector of length 0");
        }

        *this *= (target_len / current_len);
        return *this;
    }

    self_type& cap_length(const float max_len)
    {
        assert(max_len > 0);

        const float current_len = length();
        if (current_len > max_len)
        {
            *this *= (max_len / current_len);
        }

        return *this;
    }

    self_type operator*(const self_type& other) const
    {
        self_type result = *this;
        result *= other;
        return result;
    }

    self_type& operator*=(const self_type& other)
    {
        x() *= other.x();
        y() *= other.y();
        return *this;
    }

    t* toArray() const
    {
        return (t*) values.data();
    }
};

/*template<size_t n>
struct Point3D_assert {
    static_assert(n == 3,"don't have 3 param");
    using type = Point<n,float>;
};

template<size_t n>
struct Point2D_assert {
    static_assert(n == 2,"don't have 2 param");
    using type = Point<n,float>;
};*/

using Point3D = Point<3,float>;
using Point2D = Point<2,float>;


// our 3D-coordinate system will be tied to the airport: the runway is parallel to the x-axis, the z-axis
// points towards the sky, and y is perpendicular to both thus,
// {1,0,0} --> {.5,.5}   {0,1,0} --> {-.5,.5}   {0,0,1} --> {0,1}
inline Point2D project_2D(const Point3D& p)
{
    return { .5f * p.x() - .5f * p.y(), .5f * p.x() + .5f * p.y() + p.z() };
}
