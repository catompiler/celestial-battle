#ifndef GLCONTEXT_H
#define	GLCONTEXT_H

#include <unordered_map>
#include "glcontext_types.h"
#include "utils/utils.h"

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
    
    GLContext();
    ~GLContext();

    glcontext_t id() const;
    
    bool valid() const;

    bool create(const Window* window_, const Version& version_);
    bool create(const Window* window_, const Version& version_,
                             const GLContext* glcxt_);//not copy - share!
    static GLContext current();
    void destroy();
    
    static void (*getProcAddress(const char* procname_))();

protected:

    typedef SharedData<glcontext_t> SharedId;
    SharedId* _shared_id;
    typedef std::unordered_map<glcontext_t, GLContext*> Contexts;
    static Contexts _contexts;
};

#endif	/* GLCONTEXT_H */

