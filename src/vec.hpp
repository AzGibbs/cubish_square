#ifndef VEC_HPP
#define VEC_HPP

template <typename T>
struct tvec4 {
    T x, y, z, w;

    tvec4() : x{}, y{}, z{}, w{} {};
    tvec4(const T x, const T y, const T z, const T w) : x{x}, y{y}, z{z}, w{w} {};

    tvec4<T> operator+=(const tvec4<T> &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;
        return *this;
    }
    
    tvec4<T> & operator-=(const tvec4<T> &v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;
        return *this;
    }

    tvec4<T> & operator*=(const double s)
    {
        x *= s;
        y *= s;
        z *= s;
        w *= s;
        return *this;
    }
};

template <typename T>
tvec4<T> operator-(const tvec4<T> &v0, const tvec4<T> &v1)
{
    return {v0.x - v1.x, v0.y - v1.y, v0.z - v1.z, v0.w - v1.w};
}

template <typename T>
tvec4<T> operator+(const tvec4<T> &v0, const tvec4<T> &v1)
{
    return {v0.x + v1.x, v0.y + v1.y, v0.z + v1.z, v0.w + v1.w};
}

template <typename T>
tvec4<T> operator*(const T s, const tvec4<T> &v)
{
    return {s * v.x, s * v.y, s * v.z, s * v.w};
}

using vec4 = tvec4<float>;
using dvec4 = tvec4<double>;

#endif
