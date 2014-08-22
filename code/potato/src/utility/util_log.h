#pragma once

#include <cstdio>
#include <cassert>

namespace ac{
namespace utility{

// define the style/color code
#define TEXT_STYLE_END                  "\x1b[0m"
#define TEXT_STYLE_BOLD                 "\x1b[1m"
#define TEXT_STYLE_UNDERLINE            "\x1b[4m"
#define TEXT_STYLE_COLOR_BLACK          "\x1b[30m"
#define TEXT_STYLE_COLOR_RED            "\x1b[31m"
#define TEXT_STYLE_COLOR_GREEN          "\x1b[32m"
#define TEXT_STYLE_COLOR_YELLOW         "\x1b[33m"
#define TEXT_STYLE_COLOR_BLUE           "\x1b[34m"
#define TEXT_STYLE_COLOR_MAGENTA        "\x1b[35m"
#define TEXT_STYLE_COLOR_CYAN           "\x1b[36m"
#define TEXT_STYLE_COLOR_WHITE          "\x1b[37m"
#define TEXT_STYLE_BGCOLOR_BLACK        "\x1b[40m"
#define TEXT_STYLE_BGCOLOR_RED          "\x1b[41m"
#define TEXT_STYLE_BGCOLOR_GREEN        "\x1b[42m"
#define TEXT_STYLE_BGCOLOR_YELLOW       "\x1b[43m"
#define TEXT_STYLE_BGCOLOR_BLUE         "\x1b[44m"
#define TEXT_STYLE_BGCOLOR_MAGENTA      "\x1b[45m"
#define TEXT_STYLE_BGCOLOR_CYAN         "\x1b[46m"
#define TEXT_STYLE_BGCOLOR_WHITE        "\x1b[47m"

const static char* TextStyleCode[] = {TEXT_STYLE_END,
    TEXT_STYLE_BOLD, TEXT_STYLE_UNDERLINE,
    TEXT_STYLE_COLOR_BLACK, TEXT_STYLE_COLOR_RED, TEXT_STYLE_COLOR_GREEN, TEXT_STYLE_COLOR_YELLOW,
    TEXT_STYLE_COLOR_BLUE, TEXT_STYLE_COLOR_MAGENTA, TEXT_STYLE_COLOR_CYAN, TEXT_STYLE_COLOR_WHITE,
    TEXT_STYLE_BGCOLOR_BLACK, TEXT_STYLE_BGCOLOR_RED, TEXT_STYLE_BGCOLOR_GREEN, TEXT_STYLE_BGCOLOR_YELLOW,
    TEXT_STYLE_BGCOLOR_BLUE, TEXT_STYLE_BGCOLOR_MAGENTA, TEXT_STYLE_BGCOLOR_CYAN, TEXT_STYLE_BGCOLOR_WHITE
};

class Log
{
public:
  typedef enum enmLogStyle
  {
    EStyle_End = 0,
    EStyle_Bold,
    EStyle_UnderLine,
    EStyle_Color_Black,
    EStyle_Color_Red,
    EStyle_Color_Green,
    EStyle_Color_Yellow,
    EStyle_Color_Blue,
    EStyle_Color_Magenta,
    EStyle_Color_Cyan,
    EStyle_Color_White,
    EStyle_BGColor_Black,
    EStyle_BGColor_Red,
    EStyle_BGColor_Green,
    EStyle_BGColor_Yellow,
    EStyle_BGColor_Blue,
    EStyle_BGColor_Magenta,
    EStyle_BGColor_Cyan,
    EStyle_BGColor_White,
    EStyle_None,
  } LogStyle;

public:
  static const Log& Instance()
  {
    static Log gs_Instance;
    return gs_Instance;
  }

protected:
  Log() { ; }
  virtual ~Log() { ; }

public:
  void Fatal(const char* const& rcText) const
  {
    (*this)(stderr, EStyle_BGColor_Red, "FATA", rcText);
  }

  void Error(const char* const& rcText) const
  {
    (*this)(stderr, EStyle_Color_Red, "ERRO", rcText);
  }

  void Warning(const char* const& rcText) const
  {
    (*this)(stdout, EStyle_Color_Yellow, "WARN", rcText);
  }

  void System(const char* const& rcText) const
  {
    (*this)(stdout, EStyle_Color_Cyan, "SYST", rcText);
  }

  void Info(const char* const& rcText) const
  {
    (*this)(stdout, EStyle_None, "INFO", rcText);
  }

  void Debug(const char* const& rcText) const
  {
    (*this)(stdout, EStyle_Color_Magenta, "DEBU", rcText);
  }

  void User(const char* const& rcText) const
  {
    (*this)(stdout, EStyle_Color_Green, "USER", rcText);
  }

  void operator()(FILE* pFile, const LogStyle& eStyle, const char* const& rcTitle, const char* const& rcText) const
  {
    assert(pFile != NULL);
    assert(rcTitle != NULL);
    assert(rcText != NULL);

    switch (eStyle) {
    case EStyle_None:
      fprintf(pFile, "[%s] %s\n", rcTitle, rcText);
      break;

    case EStyle_Bold:
    case EStyle_Color_Black:
    case EStyle_Color_Red:
    case EStyle_Color_Green:
    case EStyle_Color_Yellow:
    case EStyle_Color_Blue:
    case EStyle_Color_Magenta:
    case EStyle_Color_Cyan:
    case EStyle_Color_White:
    case EStyle_BGColor_Black:
    case EStyle_BGColor_Red:
    case EStyle_BGColor_Green:
    case EStyle_BGColor_Yellow:
    case EStyle_BGColor_Blue:
    case EStyle_BGColor_Magenta:
    case EStyle_BGColor_Cyan:
    case EStyle_BGColor_White:
      fprintf(stdout, "[%s%s"TEXT_STYLE_END"] %s%s"TEXT_STYLE_END"\n", TextStyleCode[eStyle], rcTitle, TextStyleCode[eStyle], rcText);
      break;

    default:
      assert(0);
      break;
    }
    //
  }

public:
  void TestAll() const
  {
    Fatal("TestAll");
    Error("TestAll");
    Warning("TestAll");
    System("TestAll");
    Info("TestAll");
    Debug("TestAll");
    User("TestAll");
  }
};

}
}
