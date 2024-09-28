#ifndef __LIBHEXPLORE_LIBHEXPLORE_HPP__
#define __LIBHEXPLORE_LIBHEXPLORE_HPP__

#if defined(_MSC_VER)
    #if defined(LIBHEXPLORE_EXPORTS)
        #define LIBHEXPLORE_EXPORT __declspec(dllexport)
    #else
        #define LIBHEXPLORE_EXPORT __declspec(dllimport)
    #endif
#elif defined(__GNUC__)
    #if defined(LIBHEXPLORE_EXPORTS)
        #define LIBHEXPLORE_EXPORT __attribute__((visibility("default")))
    #else
        #define LIBHEXPLORE_EXPORT
    #endif
#endif
#endif