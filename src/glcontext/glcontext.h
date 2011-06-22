#ifndef GLCONTEXT_H
#define	GLCONTEXT_H

#include "glcontext_types.h"

class Window;

class GLContext {
public:

    struct Version{
        Version(int major_, int minor_){
            major = major_; minor = minor_;
        }
        int major;
        int minor;
    };

    glcontext_t id() const;

    static GLContext* create(const Window* window_, const Version& version_);
    static GLContext* create(const Window* window_, const Version& version_,
                             const GLContext* glcxt_);//not copy - share!
    static GLContext* current();
    static void destroy(GLContext* glcxt_);
    
    static void (*getProcAddress(const char* procname_))();

protected:
    GLContext();
    ~GLContext();

    bool _not_destroy; //GLContext* current();
    glcontext_t _id;
};

#endif	/* GLCONTEXT_H */

