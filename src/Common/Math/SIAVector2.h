//
//File: SIAVector2.h
//Description:
//Author: Ivlev Alexander. Stef
//Created: 17:37 28/1/2016
//Copyright (c) SIA 2016. All Right Reserved.
//

#pragma once
#ifndef _SIA_VECTOR2_H__
#define _SIA_VECTOR2_H__

#include <cmath>

namespace SIA {

template <class T>
class VectorT2 {
 public:
  static VectorT2<T> sincos(double angle) {
    return VectorT2<T>(cos(angle), sin(angle));
  }

  VectorT2()
      : x(0), y(0) {
  }
  VectorT2(T X, T Y)
      : x(X), y(Y) {
  }

  VectorT2<T>& operator+=(const VectorT2<T>& v) {
    x += v.x;
    y += v.y;
    return (*this);
  }

  VectorT2<T>& operator-=(const VectorT2<T>& v) {
    x -= v.x;
    y -= v.y;
    return (*this);
  }

  VectorT2<T> operator+(const VectorT2<T>& v) const {
    return VectorT2<T>(x + v.x, y + v.y);
  }
  VectorT2<T> operator-(const VectorT2<T>& v) const {
    return VectorT2<T>(x - v.x, y - v.y);
  }
  VectorT2<T> operator-() const {
    return VectorT2<T>(-x, -y);
  }

  void set(T x_, T y_) {
    x = x_;
    y = y_;
  }

  void setZero() {
    x = 0;
    y = 0;
  }

  template <class R>
  VectorT2<T> operator*(R s) const {
    VectorT2 r(*this);
    r.x = T(r.x * s);
    r.y = T(r.y * s);
    return r;
  }

  template <class R>
  VectorT2<T> operator/(R s) const {
    VectorT2 r(*this);
    r.x /= s;
    r.y /= s;
    return r;
  }

  template <class R>
  VectorT2<T> operator*=(R s) {
    x *= s;
    y *= s;
    return (*this);
  }

  template <class R>
  VectorT2<T> operator/=(R s) {
    x /= s;
    y /= s;
    return (*this);
  }

  VectorT2<T> mult(const VectorT2<T>& r) const {
    return VectorT2(x * r.x, y * r.y);
  }
  VectorT2<T> div(const VectorT2<T>& r) const {
    return VectorT2(x / r.x, y / r.y);
  }

  bool operator==(const VectorT2<T>& r) const {
    return (x == r.x && y == r.y);
  }
  bool operator!=(const VectorT2<T>& r) const {
    return !(*this == r);
  }

  T length() const {
    return (T)sqrt(x * x + y * y);
  }

  void normalize() {
    T len = length();
    x /= len;
    y /= len;
  }

  VectorT2<T> normalized() const {
    VectorT2<T> t = *this;
    t.normalize();
    return t;
  }

  float distance(const VectorT2<T>& v) const {
    return VectorT2<T>(x - v.x, y - v.y).length();
  }

  VectorT2<T> perdendicular() const {
    return VectorT2<T>(-y, x);
  }

  T dot(const VectorT2<T>& v) const {
    return x * v.x + y * v.y;
  }

  T cross(const VectorT2<T>& v) const {
    return perdendicular().dot(v);
  }

  struct {
    T x;
    T y;
  };
};

template <>
bool VectorT2<double>::operator==(const VectorT2<double>& r) const {
  static const double epsilon = 1.0e-7f;
  return (epsilon < (x - r.x) && (x - r.x) < epsilon && epsilon < (y - r.y) && (y - r.y) < epsilon);
}

typedef VectorT2<double> Vector2;
};

#endif /* _SIA_VECTOR2_H__ */
