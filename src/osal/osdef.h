#ifndef _OSDEF_H
#define _OSDEF_H


#ifdef __linux
#define OS_LINUX 1
#elif defined WIN32
#define OS_WINDOWS 1
#else
#error Unknown OS
#endif


#if defined OS_LINUX
#define WINDOW_SYSTEM x11
//linux - preprocessor macro :(
#define SYSTEM gnulinux
#elif defined OS_WINDOWS
#define WINDOW_SYSTEM windows
#define SYSTEM windows
#else
#error Unknown platform
#endif



#define STRING(s) #s
#define CONCAT(a, b) a ## b
#define PLATFORM_FILE3(platform, prefix, file) STRING(platform/prefix ## _ ## file)
#define PLATFORM_FILE(platform, file) PLATFORM_FILE3(platform, platform, file)


#endif  /* _OSDEF_H */
