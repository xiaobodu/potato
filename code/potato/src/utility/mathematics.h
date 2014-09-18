#pragma once

#define C4G_MATH_MAX(a, b)          (((a) > (b)) ? (a) : (b))
#define C4G_MATH_MIN(a, b)          (((a) < (b)) ? (a) : (b))

#define C4G_GET_MID_RATIO(a1, b1, a2, b2, x1) ((((b1) - (a1)) == 0) ? (x1) : ((x1) * ((b2) - (a2)) / ((b1) - (a1))))

namespace c4g {
namespace scene {


template<typename TType>
class Vect2
{
public:
  TType x;
  TType y;

public:
  explicit Vect2(const TType& rtX, const TType& rtY)
    : x(rtX), y(rtY)
  {
    ;
  }
  explicit Vect2(const Vect2& roOther)
  {
    x = roOther.x;
    y = roOther.y;
  }
};

typedef Vect2<int>       Vect2I;
typedef Vect2<float>     Vect2F;
typedef Vect2<double>    Vect2D;

template<typename TType>
class Rect
{
public:
  TType l;
  TType r;
  TType w;
  TType h;
  TType t;
  TType b;

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
  Rect& operator()(const TType& rtWidth, const TType& rtHeight)
  {
    r = l + rtWidth;
    b = t + rtHeight;
    return (*this)();
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
  // size test
  bool operator!() const
  {
    return (0 >= w || 0 >= h);
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
  bool operator^(const Vect2<TType>& roVect)
  {
    if (roVect.x < l || roVect.x > r) return false;
    if (roVect.y < t || roVect.y > b) return false;
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
};

typedef Rect<int>       RectI;
typedef Rect<float>     RectF;
typedef Rect<double>    RectD;

}
}
