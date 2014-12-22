#pragma once

#include <memory.h>

#include <cstdint>
#include <cmath>

#include <cassert>

#define C4G_MATH_MAX(a, b)          (((a) > (b)) ? (a) : (b))
#define C4G_MATH_MIN(a, b)          (((a) < (b)) ? (a) : (b))

#define C4G_MATRIX_INDEX(s, u, v)   ((u) * (s) + (v))

#define C4G_GET_MID_RATIO(a1, b1, a2, b2, x1) ((((b1) - (a1)) == 0) ? (x1) : ((x1) * ((b2) - (a2)) / ((b1) - (a1))))

namespace c4g {
namespace math {

  template<typename TType>
  class TVect2
  {
  public:
    TType x;
    TType y;

  public:
    explicit TVect2(const TType& rtX, const TType& rtY)
      : x(rtX), y(rtY)
    {
      ;
    }
    explicit TVect2(const TVect2& roOther)
    {
      x = roOther.x;
      y = roOther.y;
    }

  public:
    TType& operator[](int iIndex)
    {
      switch (iIndex)
      {
      case 0: return x;
      case 1: return y;
      }
      assert(0);
      return x;
    }
  };

  typedef TVect2<int>       Vect2I;
  typedef TVect2<float>     Vect2F;
  typedef TVect2<double>    Vect2D;

  template<typename TType>
  class TVect3
  {
  public:
    TType x;
    TType y;
    TType z;

  public:
    explicit TVect3(const TType& rtX, const TType& rtY, const TType& rtZ)
      : x(rtX), y(rtY), z(rtZ)
    {
      ;
    }
    explicit TVect3(const TVect3& roOther)
    {
      x = roOther.x;
      y = roOther.y;
      z = roOther.z;
    }

  public:
    TType& operator[](int iIndex)
    {
      switch (iIndex)
      {
      case 0: return x;
      case 1: return y;
      case 2: return z;
      }
      assert(0);
      return x;
    }

  public:
    TVect3& operator/=(const TType& rtD)
    {
      assert(rtD != 0);
      if (rtD != 0) return *this;
      x /= rtD;
      y /= rtD;
      z /= rtD;
      return *this;
    }

  public:
    TType Length() const
    {
      return sqrt(x * x + y * y + z * z);
    }
  };

  typedef TVect3<int32_t>        Vect3I;
  typedef TVect3<float>          Vect3F;
  typedef TVect3<double>         Vect3D;

  template<typename TType>
  class TVect4
  {
  public:
    TType x;
    TType y;
    TType z;
    TType w;

  public:
    explicit TVect4(const TType& rtX, const TType& rtY, const TType& rtZ, const TType& rtW)
      : x(rtX), y(rtY), z(rtZ), w(rtW)
    {
      ;
    }
    explicit TVect4(const TVect4& roOther)
    {
      x = roOther.x;
      y = roOther.y;
      z = roOther.z;
      w = roOther.w;
    }

  public:
    TType& operator[](int iIndex)
    {
      switch (iIndex)
      {
      case 0: return x;
      case 1: return y;
      case 2: return z;
      case 3: return w;
      }
      assert(0);
      return x;
    }

  public:
    TVect4& operator/=(const TType& rtD)
    {
      assert(rtD != 0);
      if (rtD != 0) return *this;
      x /= rtD;
      y /= rtD;
      z /= rtD;
      w /= rtD;
      return *this;
    }

  public:
    TType Length() const
    {
      return sqrt(x * x + y * y + z * z + w * w);
    }
  };

  typedef TVect4<int32_t>        Vect4I;
  typedef TVect4<float>          Vect4F;
  typedef TVect4<double>         Vect4D;

  template<typename TType>
  class TMatr4x4
  {
  public:
    explicit TMatr4x4()
    {
      ::memset(m_aData, 0, sizeof(TType) * 4 * 4);
      ::memset(m_aTData, 0, sizeof(TType) * 4 * 4);
    }
    explicit TMatr4x4(const TMatr4x4& rOther)
    {
      ::memcpy(m_aData, rOther.m_aData, sizeof(TType) * 4 * 4);
    }

  public:
    const TType* const D()
    {
      return m_aData;
    }

    const TType* const TD()
    {
      for (uint8_t i = 0; i < 4; i++)
      {
        m_aTData[C4G_MATRIX_INDEX(4, 0, i)] = m_aData[C4G_MATRIX_INDEX(4, i, 0)];
        m_aTData[C4G_MATRIX_INDEX(4, 1, i)] = m_aData[C4G_MATRIX_INDEX(4, i, 1)];
        m_aTData[C4G_MATRIX_INDEX(4, 2, i)] = m_aData[C4G_MATRIX_INDEX(4, i, 2)];
        m_aTData[C4G_MATRIX_INDEX(4, 3, i)] = m_aData[C4G_MATRIX_INDEX(4, i, 3)];
      }
      return m_aTData;
    }

  public:
    TType& operator[](int iIndex)
    {
      assert(!(iIndex < 0 || iIndex >= 4 * 4));
      if (iIndex < 0 || iIndex >= 4 * 4) return m_aData[0];
      return m_aData[iIndex];
    }

  public:
    void operator=(const TMatr4x4& rOther)
    {
      for (uint8_t i = 0; i < 4 * 4; i++) m_aData[i] = rOther.m_aData[i];
    }

    TMatr4x4& operator*=(const TMatr4x4& rOther)
    {
      TType temp_data[4 * 4];
      for (uint8_t i = 0; i < 4 * 4; i++) temp_data[i] = m_aData[i];
      for (uint8_t i = 0; i < 4; i++)
      {
        for (uint8_t j = 0; j < 4; j++)
        {
          m_aData[C4G_MATRIX_INDEX(4, i, j)]
            = temp_data[C4G_MATRIX_INDEX(4, i, 0)] * rOther.m_aData[C4G_MATRIX_INDEX(4, 0, j)]
            + temp_data[C4G_MATRIX_INDEX(4, i, 1)] * rOther.m_aData[C4G_MATRIX_INDEX(4, 1, j)]
            + temp_data[C4G_MATRIX_INDEX(4, i, 2)] * rOther.m_aData[C4G_MATRIX_INDEX(4, 2, j)]
            + temp_data[C4G_MATRIX_INDEX(4, i, 3)] * rOther.m_aData[C4G_MATRIX_INDEX(4, 3, j)];
        }
      }
      return *this;
    }

    TVect4<TType> operator*(const TVect4<TType>& rOther)
    {
      TVect4<TType> res(*this);
      res *= rOther;
      return res;
    }

  private:
    TType m_aData[4 * 4];
    TType m_aTData[4 * 4];
  };

  typedef TMatr4x4<int32_t>      Matr4x4I;
  typedef TMatr4x4<float>        Matr4x4F;
  typedef TMatr4x4<double>       Matr4x4D;

  template<typename TType>
  class TRect
  {
  public:
    TType l;
    TType r;
    TType w;
    TType h;
    TType t;
    TType b;

  public:
    explicit TRect(const TType& rtValue)
      : l(rtValue)
      , r(rtValue)
      , w(rtValue)
      , h(rtValue)
      , t(rtValue)
      , b(rtValue)
    {
      ;
    }
    explicit TRect(const TRect& roOther)
      : l(roOther.l)
      , r(roOther.r)
      , w(roOther.w)
      , h(roOther.h)
      , t(roOther.t)
      , b(roOther.b)
    {
      ;
    }
    virtual ~TRect()
    {
      ;
    }

  public:
    // normalize
    TRect& operator()()
    {
      w = r - l;
      h = b - t;
      return (*this);
    }
    TRect& operator()(const TType& rtWidth, const TType& rtHeight)
    {
      r = l + rtWidth;
      b = t + rtHeight;
      return (*this)();
    }
    // assign
    TRect& operator=(const TType& rtValue)
    {
      l = rtValue;
      r = rtValue;
      t = rtValue;
      b = rtValue;
      return (*this)();
    }
    TRect& operator=(const TRect& roOther)
    {
      l = roOther.l;
      r = roOther.r;
      t = roOther.t;
      b = roOther.b;
      return (*this)();
    }
    // union
    TRect& operator&=(const TRect& roOther)
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
    bool operator^(const TRect& roOther)
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
    bool operator^(const TVect2<TType>& roVect)
    {
      if (roVect.x < l || roVect.x > r) return false;
      if (roVect.y < t || roVect.y > b) return false;
      return true;
    }
    // intersect
    TRect& operator^=(const TRect& roOther)
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
    bool operator==(const TRect& roOther)
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

  typedef TRect<int>       RectI;
  typedef TRect<float>     RectF;
  typedef TRect<double>    RectD;

}
}
