#ifndef GLCONTEXT_H
#define	GLCONTEXT_H

#include "glcontext_types.h"

class Window;

class GLContext {
public:
    virtual ~GLContext();

    glcontext_t id();

    static GLContext* create(const Window* window_, );
    static GLContext* create(const Window* window_, const GLContext* orig);//not copy - share!
    static GLContext* current();
    static void destroy(GLContext* glcxt_);

protected:
    GLContext();

    bool _not_destroy; //GLContext* current();
    glcontext_t _id;
};

#endif	/* GLCONTEXT_H */

