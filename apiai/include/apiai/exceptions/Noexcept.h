#ifndef NOEXCEPT_H
#define NOEXCEPT_H

#include <exception>

#ifdef _NOEXCEPT
    #define AI_NOEXCEPT _NOEXCEPT
#else
    #define AI_NOEXCEPT
#endif

#endif // NOEXCEPT_H
