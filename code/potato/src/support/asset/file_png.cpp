#include "file_png.h"

#include <png.h>
#include <zlib.h>
#include <cassert>
#include <memory.h>

namespace c4g {
namespace asset {

#define C4G_PNG_COUNT_RGBA  4
#define C4G_PNG_SIZE_BYTE   8

#define PNG_BYTES_TO_CHECK 4
bool check_if_png(const char *file_name)
{
  FILE *fp = NULL;
#if defined(CXX_GNU) || defined(CXX_CLANG)
  if ((fp = fopen(file_name, "rb")) == NULL) return false;
#elif defined(CXX_MSVC)
  if (fopen_s(&fp, file_name, "rb") || fp == NULL) return false;
#endif
  char buf[PNG_BYTES_TO_CHECK];
  bool is_png = false;
  if (fread(buf, 1, PNG_BYTES_TO_CHECK, fp) != PNG_BYTES_TO_CHECK)
  {
    is_png = false;
  }
  else
  {
    is_png = (0 != (!png_sig_cmp((png_bytep)buf, (png_size_t)0, PNG_BYTES_TO_CHECK)));
  }

  if (NULL != fp)
  {
    fclose(fp);
    fp = NULL;
  }
  return is_png;
}

void read_png(const char *file_name, unsigned int& riWidth, unsigned int& riHeight, unsigned char*& rpBuffer)
{
  assert(NULL == rpBuffer);

  rpBuffer = NULL;

  FILE *fp = NULL;
#if defined(CXX_GNU) || defined(CXX_CLANG)
  if ((fp = fopen(file_name, "rb")) == NULL) return;
#elif defined(CXX_MSVC)
  if (fopen_s(&fp, file_name, "rb") || fp == NULL) return;
#endif

  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (NULL != png_ptr)
  {
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (NULL != info_ptr)
    {
      if (!setjmp(png_jmpbuf(png_ptr)))
      {
        png_init_io(png_ptr, fp);
        png_set_sig_bytes(png_ptr, 0);
        png_set_expand(png_ptr);
        png_set_gray_to_rgb(png_ptr);

        png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

        png_bytep* row_pointers = png_get_rows(png_ptr, info_ptr);
        riWidth = png_get_image_width(png_ptr, info_ptr);
        riHeight = png_get_image_height(png_ptr, info_ptr);
        if (PNG_COLOR_TYPE_RGB_ALPHA == png_get_color_type(png_ptr, info_ptr)
            && C4G_PNG_SIZE_BYTE == png_get_bit_depth(png_ptr, info_ptr))
        {
          rpBuffer = new unsigned char[riWidth * riHeight * C4G_PNG_COUNT_RGBA];
          memset(rpBuffer, 0, sizeof(unsigned char) * (riWidth * riHeight * C4G_PNG_COUNT_RGBA));
          for (unsigned int y = 0; y < riHeight; ++y)
          {
            png_bytep row = row_pointers[y];
            memcpy(rpBuffer + y * riWidth * sizeof(unsigned char) * C4G_PNG_COUNT_RGBA, row, riWidth * sizeof(unsigned char) * C4G_PNG_COUNT_RGBA);
          }
        }
      }
    }

    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
  }
  if (NULL != fp)
  {
    fclose(fp);
    fp = NULL;
  }
}

CFilePNG& CFilePNG::Instance()
{
  static CFilePNG s_Instance;
  return s_Instance;
}

CFilePNG::CFilePNG()
  : m_iWidth(0)
  , m_iHeight(0)
  , m_pBuffer(NULL)
{
  ;
}

CFilePNG::~CFilePNG()
{
  Free();
}

void CFilePNG::Load(const std::string& rsFileName)
{
  Free();

  read_png(rsFileName.c_str(), m_iWidth, m_iHeight, m_pBuffer);
  //
}

const unsigned int& CFilePNG::GetWidth() const
{
  return m_iWidth;
}

const unsigned int& CFilePNG::GetHeight() const
{
  return m_iHeight;
}

unsigned char* CFilePNG::GetBuffer() const
{
  return m_pBuffer;
}

void CFilePNG::Free()
{
  if (NULL != m_pBuffer)
  {
    delete[] m_pBuffer;
    m_pBuffer = NULL;
  }
}

}
}
