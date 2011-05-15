#ifndef GLCONTEXT_H
#define	GLCONTEXT_H

class Window;

class GLContext {
public:
    GLContext(const Window* window_);
    GLContext(const GLContext& orig);
    virtual ~GLContext();
private:

};

#endif	/* GLCONTEXT_H */

