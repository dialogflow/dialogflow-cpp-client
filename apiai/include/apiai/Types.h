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

#if GCC_COMPILER
    #if GCC_VERSION >= 50000
        #include <memory>
    #else
        #include <boost/shared_ptr.hpp>
        #include <boost/move/unique_ptr.hpp>
    #endif
#else
    #include <memory>
#endif

namespace ai {
    #if GCC_COMPILER
        #if GCC_VERSION >= 50000
            using std::shared_ptr;
            using std::unique_ptr;
        #else
            using boost::shared_ptr;
            using boost::movelib::unique_ptr;
        #endif
    #else
        using std::shared_ptr;
        using std::unique_ptr;
    #endif
}

#endif // TYPES_H
