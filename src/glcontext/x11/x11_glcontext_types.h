#ifndef _X11_GLCONTEXT_TYPES_H
#define _X11_GLCONTEXT_TYPES_H

#define Window XWindow
#define Display XDisplay
#include <GL/glx.h>
#undef Window
#undef Display


typedef GLXContext glcontext_t;


#endif  //_X11_GLCONTEXT_TYPES_H 
 
