#ifndef VEC_HPP
#define VEC_HPP

template <typename T>
struct vec4 {
    T x, y, z, w;

    vec4() : x{}, y{}, z{}, w{} {};
    vec4(const T x, const T y, const T z, const T w) : x{x}, y{y}, z{z}, w{w} {};

    vec4<T> operator+=(const vec4<T> &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }
    
    vec4<T> & operator-=(const vec4<T> &v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    vec4<T> & operator*=(const double s)
    {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }
};

template <typename T>
vec4<T> operator-(const vec4<T> &v0, const vec4<T> &v1)
{
    return {v0.x - v1.x, v0.y - v1.y, v0.z - v1.z, v0.w - v1.w};
}

template <typename T>
vec4<T> operator+(const vec4<T> &v0, const vec4<T> &v1)
{
    return {v0.x + v1.x, v0.y + v1.y, v0.z + v1.z, v0.w + v1.w};
}

template <typename T>
vec4<T> operator*(const double s, const vec4<T> &v)
{
    return {s * v.x, s * v.y, s * v.z, s * v.w};
}

using dvec4 = vec4<double>;

#endif
