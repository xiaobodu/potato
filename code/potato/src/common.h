#pragma once


#define TOSTRING1(num)             #num
#define TOSTRING(num)              TOSTRING1(num)
#define SLINE                      TOSTRING(__LINE__)

#if !defined(NULL)
# define NULL 0
#endif

/// declare the function of library
#define FUNC_API_TYPE(function_name)          function_name##Func
#define FUNC_API_DECLARE(function_name, class_name)\
    extern "C" bool function_name(class_name*& rpClass);
#define FUNC_API_TYPEDEF(function_name, class_name)\
    typedef bool (*FUNC_API_TYPE(function_name))(class_name*& rpClass);
