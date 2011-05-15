#ifndef _OSDEF_H
#define	_OSDEF_H

#ifdef __linux
#define OS_LINUX 1
#elif defined WIN32
#define OS_WINDOWS 1
#else
#error Unknown OS
#endif

#endif	/* _OSDEF_H */

