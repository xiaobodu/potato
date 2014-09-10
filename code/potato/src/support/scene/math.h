#pragma once

#define C4G_MATH_MAX(a, b)          ((a) > (b) ? (a) : (b))
#define C4G_MATH_MIN(a, b)          ((a) < (b) ? (a) : (b))

namespace c4g {
namespace scene {

template<typename TType>
class Rect
{
public:
  explicit Rect(const TType& rtValue)
    : l(rtValue)
    , r(rtValue)
    , w(rtValue)
    , h(rtValue)
    , t(rtValue)
    , b(rtValue)
  {
    ;
  }
  explicit Rect(const Rect& roOther)
    : l(roOther.l)
    , r(roOther.r)
    , w(roOther.w)
    , h(roOther.h)
    , t(roOther.t)
    , b(roOther.b)
  {
    ;
  }
  virtual ~Rect()
  {
    ;
  }

public:
  // normalize
  Rect& operator()()
  {
    w = r - l;
    h = b - t;
    return (*this);
  }
  // assign
  Rect& operator=(const TType& rtValue)
  {
    l = rtValue;
    r = rtValue;
    t = rtValue;
    b = rtValue;
    return (*this)();
  }
  Rect& operator=(const Rect& roOther)
  {
    l = roOther.l;
    r = roOther.r;
    t = roOther.t;
    b = roOther.b;
    return (*this)();
  }
  // union
  Rect& operator&=(const Rect& roOther)
  {
    l = C4G_MATH_MIN(l, roOther.l);
    r = C4G_MATH_MAX(r, roOther.r);
    t = C4G_MATH_MIN(t, roOther.t);
    b = C4G_MATH_MAX(b, roOther.b);
    return (*this)();
  }
  // intersect test
  bool operator^(const Rect& roOther)
  {
    float left_max = C4G_MATH_MAX(l, roOther.l);
    float top_max = C4G_MATH_MAX(t, roOther.t);
    float right_min = C4G_MATH_MIN(r, roOther.r);
    float bottom_min = C4G_MATH_MIN(b, roOther.b);
    if (left_max >= right_min || top_max >= bottom_min)
    {
        return false;
    }
    return true;
  }
  // intersect
  Rect& operator^=(const Rect& roOther)
  {
    float left_max = C4G_MATH_MAX(l, roOther.l);
    float top_max = C4G_MATH_MAX(t, roOther.t);
    float right_min = C4G_MATH_MIN(r, roOther.r);
    float bottom_min = C4G_MATH_MIN(b, roOther.b);
    if (left_max >= right_min || top_max >= bottom_min)
    {
        return (*this);
    }
    l = left_max;
    t = top_max;
    r = right_min;
    b = bottom_min;
    return (*this)();
  }
  // compare
  bool operator==(const Rect& roOther)
  {
    if (l != roOther.l) return false;
    if (r != roOther.r) return false;
    if (w != roOther.w) return false;
    if (h != roOther.h) return false;
    if (t != roOther.t) return false;
    if (b != roOther.b) return false;
    return true;
  }

public:
  TType l;
  TType r;
  TType w;
  TType h;
  TType t;
  TType b;
};

typedef Rect<int>       RectI;
typedef Rect<float>     RectF;
typedef Rect<double>    RectD;

}
}
