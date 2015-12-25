#ifndef TYPES_H
#define TYPES_H

#ifdef __GNUC__
    #define GCC_COMPILER 1
    #define GCC_VERSION (__GNUC__ * 10000 \
                        + __GNUC_MINOR__ * 100 \
                        + __GNUC_PATCHLEVEL__)

#else
    #define GCC_COMPILER 0
#endif

namespace ai {

}

#endif // TYPES_H
