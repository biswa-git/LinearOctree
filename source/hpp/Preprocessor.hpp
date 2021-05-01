#pragma once
#include<iostream>
/**--------power function: calculates x^y------*/
namespace detail
{
    template<class T, int N>
    struct helper
    {
        static constexpr T POW(const T x) {
            return helper<T, N - 1>::pow(x) * x;
        }
    };

    template<class T>
    struct helper<T, 1>
    {
        static constexpr T POW(const T x) {
            return x;
        }
    };

    template<class T>
    struct helper<T, 0>
    {
        static constexpr T POW(const T x) {
            return 1;
        }
    };

}

template<int N, class T>
T constexpr POW(T const x)
{
    return detail::helper<T, N>::POW(x);
}

template <unsigned int x>
constexpr std::enable_if_t<x != 0U, int> LOG2 = 1 + LOG2<x / 2U>;

template <>
constexpr int LOG2<1U> = 0;
/**--------------------------------------------*/

#ifdef AMR_NO_EXCEPTIONS
#define AMR_THROW(msg) return false;
#define AMR_COND_THROW(cond, msg) if(cond) return false;
#else
 /// Throws an std::runtime_error with the given message.
#define AMR_THROW(msg) {std::stringstream ss; ss << msg; throw(std::runtime_error(ss.str()));}

/// Throws an std::runtime_error with the given message, if the given condition evaluates to true.
#define AMR_COND_THROW(cond, msg)  if(cond){std::stringstream ss; ss << msg; throw(std::runtime_error(ss.str()));}
#endif

/**--------------------------------------------*/

#define NEW_MACRO(thisClass)									\
  thisClass* thisClass::New() { STANDARD_NEW_BODY(thisClass); }

#define STANDARD_NEW_BODY(thisClass)							\
  thisClass* result = new thisClass;							\
  return result

/**--------------------------------------------*/

#define SET_MACRO(name,type) \
virtual void Set##name (type _arg) \
{ \
    if (this->name != _arg) \
    { \
        this->name = _arg; \
    } \
}

/**--------------------------------------------*/

#define GetMacro(name,type) \
virtual type Get##name () \
{ \
    return this->name; \
}

/**--------------------------------------------*/

#define FREE_OBJ_MACRO(name) \
if(name!=nullptr){  \
    delete name; \
    name = nullptr; \
}

/**--------------------------------------------*/

#define FREE_ARR_MACRO_1P(name) \
if(name!=nullptr){ \
    delete[] name; \
    name = nullptr; \
}

/**--------------------------------------------*/