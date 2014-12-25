#pragma once

#include <cstdint>
#include <cmath>

#include <cassert>

#define C4G_MATH_MAX(a, b)          (((a) > (b)) ? (a) : (b))
#define C4G_MATH_MIN(a, b)          (((a) < (b)) ? (a) : (b))

#define C4G_MATRIX_INDEX(s, u, v)   ((u) * (s) + (v))

#define C4G_GET_MID_RATIO(a1, b1, a2, b2, x1) ((((b1) - (a1)) == 0) ? (x1) : ((x1) * ((b2) - (a2)) / ((b1) - (a1))))

namespace c4g { namespace math {

  template<typename TType>
  class TVect2
  {
  public:
    TType x;
    TType y;

  public:
    TVect2()
      : x(0), y(0)
    {
      ;
    }
    TVect2(const TType& rtV)
      : x(rtV), y(rtV)
    {
      ;
    }
    TVect2(const TType& rtX, const TType& rtY)
      : x(rtX), y(rtY)
    {
      ;
    }
    TVect2(const TVect2& rOther)
    {
      for (uint8_t i = 0; i < 2; i++) (*this)[i] = rOther[i];
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
    const TType& operator[](int iIndex) const
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
    TVect3()
      : x(0), y(0), z(0)
    {
      ;
    }
    TVect3(const TType& rtV)
      : x(rtV), y(rtV), z(rtV)
    {
      ;
    }
    TVect3(const TType& rtX, const TType& rtY, const TType& rtZ)
      : x(rtX), y(rtY), z(rtZ)
    {
      ;
    }
    TVect3(const TVect3& rOther)
    {
      for (uint8_t i = 0; i < 3; i++) (*this)[i] = rOther[i];
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
    const TType& operator[](int iIndex) const
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
      assert(!(rtD == 0));
      if (rtD == 0) return *this;
      x /= rtD;
      y /= rtD;
      z /= rtD;
      return *this;
    }
    TVect3& operator*=(const TVect3& rOther)
    {
      (*this) = ((*this) * rOther);
      return *this;
    }
    TVect3 operator+(const TVect3& rOther) const
    {
      TVect3 res(*this);
      res.x = x + rOther.x;
      res.y = y + rOther.y;
      res.z = z + rOther.z;
      return res;
    }
    TVect3 operator-(const TVect3& rOther) const
    {
      TVect3 res(*this);
      res.x = x - rOther.x;
      res.y = y - rOther.y;
      res.z = z - rOther.z;
      return res;
    }
    TVect3 operator*(const TVect3& rOther) const
    {
      TVect3 res(*this);
      res.x = y * rOther.z - rOther.y * z;
      res.y = z * rOther.x - rOther.z * x;
      res.z = x * rOther.y - rOther.x * y;
      return res;
    }
    TType Dot(const TVect3& rOther)
    {
      return x * rOther.x + y * rOther.y + z * rOther.z;
    }

  public:
    TType Length() const
    {
      return sqrt(x * x + y * y + z * z);
    }
    TVect3& Normalize()
    {
      TType len = Length();
      if (len == 0) return *this;
      return ((*this) /= len);
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
    TVect4()
      : x(0), y(0), z(0), w(0)
    {
      ;
    }
    TVect4(const TType& rtV)
      : x(rtV), y(rtV), z(rtV), w(rtV)
    {
      ;
    }
    TVect4(const TType& rtX, const TType& rtY, const TType& rtZ, const TType& rtW)
      : x(rtX), y(rtY), z(rtZ), w(rtW)
    {
      ;
    }
    TVect4(const TVect4& rOther)
    {
      for (uint8_t i = 0; i < 4; i++) (*this)[i] = rOther[i];
    }

  public:
    TType& operator[](uint8_t iIndex)
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
    const TType& operator[](uint8_t iIndex) const
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
    TVect4& operator=(const TVect4& roOther)
    {
      x = roOther.x;
      y = roOther.y;
      z = roOther.z;
      w = roOther.w;
      return *this;
    }
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
    TMatr4x4()
    {
      ::memset(m_aData, 0, sizeof(TType) * 4 * 4);
    }
    TMatr4x4(const TType& rV)
    {
      ::memset(m_aData, 0, sizeof(TType) * 4 * 4);
      for (uint8_t i = 0; i < 4; i++) m_aData[C4G_MATRIX_INDEX(4, i, i)] = rV;
    }
    TMatr4x4(const TMatr4x4& rOther)
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

    TMatr4x4& T()
    {
      for (uint8_t i = 0; i < 4; i++)
      {
        m_aTData[C4G_MATRIX_INDEX(4, 0, i)] = m_aData[C4G_MATRIX_INDEX(4, i, 0)];
        m_aTData[C4G_MATRIX_INDEX(4, 1, i)] = m_aData[C4G_MATRIX_INDEX(4, i, 1)];
        m_aTData[C4G_MATRIX_INDEX(4, 2, i)] = m_aData[C4G_MATRIX_INDEX(4, i, 2)];
        m_aTData[C4G_MATRIX_INDEX(4, 3, i)] = m_aData[C4G_MATRIX_INDEX(4, i, 3)];
      }
      ::memcpy(m_aData, m_aTData, sizeof(TType) * 4 * 4);
      return (*this);
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
    TMatr4x4 operator*(const TMatr4x4& rOther)
    {
      TMatr4x4 res(*this);
      return (res *= rOther);
    }
    TVect4<TType> operator*(const TVect4<TType>& rOther) const
    {
      TVect4<TType> res;
      for (uint8_t i = 0; i < 4; i++)
      {
        res[i] += m_aData[C4G_MATRIX_INDEX(4, i, 0)] * rOther.x;
        res[i] += m_aData[C4G_MATRIX_INDEX(4, i, 1)] * rOther.y;
        res[i] += m_aData[C4G_MATRIX_INDEX(4, i, 2)] * rOther.z;
        res[i] += m_aData[C4G_MATRIX_INDEX(4, i, 3)] * rOther.w;
      }
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

}}
