#ifndef VEC_H
#define VEC_H

template <typename T>
struct vec4 {
    T x, y, z, w;

    vec4(const T x, const T y, const T z, const T w) : x(x), y(y), z(z), w(w) {};
/*
    T operator+(vec4<T> addition)
    {
        x += addition.x;
        y += addition.y;
        z += addition.z;
    }
    
    T operator-(vec4<T> subtraction)
    {
        x -= subtraction.x;
        y -= subtraction.y;
        z -= subtraction.z;
    }*/
};

template <typename T>
vec4<T> operator-(const vec4<T> &v0, const vec4<T> &v1)
{
    return vec4<T>(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z, v0.w - v1.w);
}

template <typename T>
vec4<T> operator+(const vec4<T> &v0, const vec4<T> &v1)
{
    return vec4<T>(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z, v0.w + v1.w);
}

typedef vec4<double> dvec4;

#endif
